#include <assert.h>
#include <iostream>
#include <vector>
#include <memory>

struct Point {
  double lon;
  double lat;
};

struct Bbox {
  double left;
  double bottom;
  double right;
  double top;

  bool Contains(const Point& point) const {
    return left <= point.lon && bottom <= point.lat &&
      point.lon < right && point.lat < top;
  }
};

class KDTree {
 public:
  explicit KDTree(std::vector<Point>& points);

  int CountPointsInBbox(const Bbox& bbox);

 private:
  struct KDNode {
    Point median;
    std::unique_ptr<KDNode> left;
    std::unique_ptr<KDNode> right;

    explicit KDNode(const Point& median_) : median(median_) {}
  };

  std::unique_ptr<KDNode> root;

  static std::unique_ptr<KDNode> BuildTree(
      std::vector<Point>& points, size_t left, size_t right, int depth);
  static int CountPointsInBbox(
      const Bbox& bbox, const std::unique_ptr<KDNode>& node, int depth);
};

KDTree::KDTree(std::vector<Point>& points) {
  root = BuildTree(points, 0, points.size(), 0);
}

namespace {
template<typename comparator>
size_t Partition(
    std::vector<Point>& points, size_t left, size_t right, comparator cmp) {
  int pivot_pos = static_cast<int>(right) - 1;
  int i = static_cast<int>(left), j = pivot_pos - 1;
  while (i <= j) {
    for (; cmp(points[i], points[pivot_pos]); ++i) {}
    for (; j >= i && !cmp(points[j], points[pivot_pos]); --j) {}
    if (i < j) std::swap(points[i], points[j]);
  }
  std::swap(points[i], points[pivot_pos]);
  return static_cast<size_t>(i);
}

void LocateMedian(
    std::vector<Point>& points, size_t left, size_t right, int depth) {
  const size_t med = (left + right) / 2;

  while (true) {
    size_t pivot_pos = Partition(points, left, right,
        [depth](const Point& first, const Point& second){
      if(depth % 2 == 0) {
        return first.lon < second.lon;
      } else {
        return first.lat < second.lat;
      }
    });
    if (pivot_pos == med) return;
    if (pivot_pos < med) left = pivot_pos + 1;
    else right = pivot_pos;
  }
}
} // unnamed namespace

std::unique_ptr<KDTree::KDNode> KDTree::BuildTree(
    std::vector<Point>& points, size_t left, size_t right, int depth) {
  assert(left < right);
  const size_t med = (left + right) / 2;
  LocateMedian(points, left, right, depth);
  auto node = std::make_unique<KDNode>(points[med]);

  if (med > left) {
    node->left = BuildTree(points, left, med, depth + 1);
  }
  if (med + 1 < right) {
    node->right = BuildTree(points, med + 1, right, depth + 1);
  }
  return node;
}

int KDTree::CountPointsInBbox(
    const Bbox& bbox, const std::unique_ptr<KDNode>& node, int depth) {
  int count = 0;
  if (bbox.Contains(node->median)) {
    ++count;
  }
  if (depth % 2 == 0) {
    if (node->left && bbox.left <= node->median.lon) {
      count += CountPointsInBbox(bbox, node->left, depth + 1);
    }
    if (node->right && node->median.lon < bbox.right) {
      count += CountPointsInBbox(bbox, node->right, depth + 1);
    }
  } else {
    if (node->left && bbox.bottom <= node->median.lat) {
      count += CountPointsInBbox(bbox, node->left, depth + 1);
    }
    if (node->right && node->median.lat < bbox.top) {
      count += CountPointsInBbox(bbox, node->right, depth + 1);
    }
  }
  return count;
}

int KDTree::CountPointsInBbox(const Bbox& bbox) {
  if (!root) return 0;
  return CountPointsInBbox(bbox, root, 0);
}

int main() {
  std::vector<Point> points{{1., 3.}, {4., 1.}, {0., 3.},
                            {1., 1.}, {2., 2.}, {1., 5.},
                            {4., 5.}, {3., 4.}, {3., 0.}};
  KDTree tree(points);

  std::cout << tree.CountPointsInBbox({0.0, 0.0, 0.0, 0.0}) << std::endl;
  std::cout << tree.CountPointsInBbox({0.0, 0.0, 2.0, 2.0}) << std::endl;
  std::cout << tree.CountPointsInBbox({-.5, .5, 2.5, 3.5}) << std::endl;
  std::cout << tree.CountPointsInBbox({0.0, 1.0, 3.0, 4.0}) << std::endl;
  return 0;
}