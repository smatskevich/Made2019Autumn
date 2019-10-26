#include <iostream>
#include <random>

// Узел бинарного дерева
struct TreeNode {
  explicit TreeNode(int _value) : value(_value) {}

  int value = 0;
  TreeNode* left = nullptr;
  TreeNode* right = nullptr;
};

class Tree {
 public:
  ~Tree();

  void Print() const;

  void Add(int value);

 private:
  TreeNode* root = nullptr;

  void print_subtree(TreeNode* node) const;

  void delete_subtree(TreeNode* node);
};

Tree::~Tree() {
  delete_subtree(root);
}

void Tree::delete_subtree(TreeNode* node) {
  if (!node) return;
  delete_subtree(node->left);
  delete_subtree(node->right);
  delete node;
}

void Tree::Print() const {
  print_subtree(root);
}

void Tree::print_subtree(TreeNode* node) const {
  if (!node) return;
  print_subtree(node->left);
  std::cout << node->value << " ";
  print_subtree(node->right);
}

void Tree::Add(int value) {
  if (!root) {
    root = new TreeNode(value);
  }
}

// Поворот. Возвращает указатель на новый корень.
TreeNode* RotateRight(TreeNode* root) {
  if (!root) {
    // Сигнализировать ошибку?
    return nullptr;
  }
  if (!root->left) {
    // Сигнализировать ошибку?
    return root;
  }
  TreeNode* new_root = root->left;
  root->left = new_root->right;
  new_root->right = root;
  return new_root;
}

// Узел декартова дерева.
struct TreapNode {
  explicit TreapNode(int _value) :
      value(_value), priority(rand()) {}

  int value = 0;
  int priority = 0;
  TreapNode* left = nullptr;
  TreapNode* right = nullptr;
};

class Treap {
 public:
  ~Treap();

 private:
  TreapNode* root = nullptr;

  void delete_subtree(TreapNode* node);

  std::pair<TreapNode*, TreapNode*> split(TreapNode* node, int x);
};

std::pair<TreapNode*, TreapNode*> split(TreapNode* node, int x) {
  if (!node) {
    return std::make_pair(nullptr, nullptr);
  }
  if (node->value < x) {
    const auto right_pair = split(node->right, x);
    node->right = right_pair.first;
    return std::make_pair(node, right_pair.second);
  } else {
    const auto left_pair = split(node->left, x);
    node->left = left_pair.second;
    return std::make_pair(left_pair.first, node);
  }
}

Treap::~Treap() {
  delete_subtree(root);
}

void Treap::delete_subtree(TreapNode* node) {
  if (!node) return;
  delete_subtree(node->left);
  delete_subtree(node->right);
  delete node;
}

int main() {
  srand(42);

  Tree tree;
  tree.Add(5);
  tree.Print();
  return 0;
}