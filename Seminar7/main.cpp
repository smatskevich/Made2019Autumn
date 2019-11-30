#include <assert.h>
#include <iostream>
#include <vector>

class DSU {
 public:
  explicit DSU(size_t size);

  int find(int element);
  void merge(int left, int right);
  void print() const;

 private:
  std::vector<int> parent;
  std::vector<int> rank;
};

DSU::DSU(size_t size) :
    parent(size, -1),
    rank(size, 1) {}

int DSU::find(int element) {
  if (parent[element] == -1) {
    return element;
  }
  return parent[element] = find(parent[element]);
}

void DSU::merge(int left, int right) {
  const int deputat_left = find(left);
  const int deputat_right = find(right);
  assert(deputat_left != deputat_right);
  if (rank[deputat_left] == rank[deputat_right]) {
    parent[deputat_right] = deputat_left;
    ++rank[deputat_left];
  } else if(rank[deputat_left] > rank[deputat_right]) {
    parent[deputat_right] = deputat_left;
  } else {
    parent[deputat_left] = deputat_right;
  }
}

void DSU::print() const {
  for (const auto parent_element : parent) {
    std::cout << parent_element << " ";
  }
  std::cout << std::endl;
}

int main() {
  DSU dsu(7);
  dsu.print();

  dsu.merge(0, 1);
  dsu.print();
  dsu.merge(1, 2);
  dsu.print();
  dsu.merge(3, 4);
  dsu.merge(0, 3);
  dsu.print();
  std::cout << dsu.find(4) << std::endl;
  dsu.print();
  dsu.merge(5, 6);
  dsu.print();
  dsu.merge(4, 5);
  dsu.print();

  std::cout << "Hello, World!" << std::endl;
  return 0;
}