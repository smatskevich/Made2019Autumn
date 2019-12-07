#include <iostream>
#include <map>
#include <memory>

struct Node {
  std::map<char, std::shared_ptr<Node>> go;
  bool is_terminal = false;
};

class Trie {
 public:
  Trie();
  Trie(const Trie&) = delete;
  Trie(Trie&&) = delete;
  Trie& operator=(const Trie&) = delete;
  Trie& operator=(Trie&&) = delete;
  ~Trie() = default;

  bool Has(const std::string& key) const;
  bool Add(const std::string& key);
  bool Remove(const std::string& key);
  void Print() const;

 private:
  std::shared_ptr<Node> root;

  static void print(const std::shared_ptr<Node>& node, const std::string& current);
  // Возвращает пару bool: первый - о наличии строки
  // второй - о единственности узла и необходимости его удалить.
  static std::pair<bool, bool> remove(
      std::shared_ptr<Node>& node, const std::string& key, int current_index);
};

Trie::Trie() {
  root = std::make_shared<Node>();
}

bool Trie::Has(const std::string& key) const {
  std::shared_ptr<Node> current = root;
  for (char symbol : key) {
    auto next = current->go.find(symbol);
    if (next == current->go.end()) return false;
    current = next->second;
  }
  return current->is_terminal;
}

bool Trie::Add(const std::string& key) {
  std::shared_ptr<Node> current = root;
  for (char symbol : key) {
    auto next = current->go.find(symbol);
    if (next == current->go.end()) {
      current = current->go[symbol] = std::make_shared<Node>();
    } else {
      current = next->second;
    }
  }
  // Если терминальная, значит, строка уже есть.
  if (current->is_terminal) return false;
  current->is_terminal = true;
  return true;
}

bool Trie::Remove(const std::string& key) {
  return remove(root, key, 0).first;
}

std::pair<bool, bool> Trie::remove(
    std::shared_ptr<Node>& node, const std::string& key, int current_index) {
  if (current_index == key.length()) {
    if (!node->is_terminal) return std::make_pair(false, false);
    node->is_terminal = false;
    return std::make_pair(true, node->go.empty());
  }

  auto next = node->go.find(key[current_index]);
  if (next == node->go.end()) {
    return std::make_pair(false, false);
  }

  auto result = remove(next->second, key, current_index + 1);

  if (!result.first) { // Не нашли
    return result;
  }
  if (!result.second) { // Не нужно удалить ссылку на дочерний
    return result;
  }
  node->go.erase(key[current_index]);
  return std::make_pair(true, !node->is_terminal && node->go.empty());
}

void Trie::Print() const {
  print(root, "");
}

void Trie::print(const std::shared_ptr<Node>& node, const std::string& current) {
  if (node->is_terminal) {
    std::cout << current << std::endl;
  }
  for (const auto go : node->go) {
    print(go.second, current + go.first);
  }
}

//int main() {
//  Trie trie;
//  trie.Add("aaa");
//  trie.Add("aa");
//  trie.Remove("aaa");
//  trie.Print();
//  return 0;
//}

int main() {
  Trie trie;
  char command = 0;
  std::string key;
  while (std::cin >> command >> key) {
    switch (command) {
      case '+':
        std::cout << (trie.Add(key) ? "OK" : "FAIL") << std::endl;
        break;
      case '-':
        std::cout << (trie.Remove(key) ? "OK" : "FAIL") << std::endl;
        break;
      case '?':
        std::cout << (trie.Has(key) ? "OK" : "FAIL") << std::endl;
        break;
    }
  }
  return 0;
}
