#include <assert.h>
#include <iostream>

// Узел односвязного списка
struct QueueNode {
  int value;
  QueueNode* next;
};

class Queue {
 public:
  ~Queue();

  // Проверка очереди на пустоту
  bool empty() const;
  // Добавление элемента
  void push(int value);
  // Извлечение
  int pop();

 private:
  QueueNode* head = nullptr;
  QueueNode* tail = nullptr;
};

Queue::~Queue() {
  while(head) {
    QueueNode* to_delete = head;
    head = head->next;
    delete to_delete;
  }
}

bool Queue::empty() const {
  // Оба указателя равны нулю одновреммено
  assert(((head == nullptr) && (tail == nullptr)) ||
             ((head != nullptr) && (tail != nullptr)));

  return head == nullptr;
}

void Queue::push(int value) {
  if (empty()) {
    head = tail = new QueueNode{value, nullptr};
  } else {
    tail->next = new QueueNode{value, nullptr};
    tail = tail->next;
  }
}

int Queue::pop() {
  assert(!empty());
  if (head == tail) {
    // Остался один
    int result = head->value;
    delete head;
    head = tail = nullptr;
    return result;
  }
  int result = head->value;
  QueueNode* next = head->next;
  delete head;
  head = next;
  return result;
}

int main() {
  int commands_count = 0;
  std::cin >> commands_count;

  Queue queue;
  for (int i = 0; i < commands_count; ++i) {
    int command = 0;
    int value = 0;
    std::cin >> command >> value;
    if (command == 3) {
      queue.push(value);
    } else if (command == 2) {
      if (queue.empty()) {
        if (value != -1) {
          std::cout << "NO";
          return 0;
        }
      } else if (queue.pop() != value) {
        std::cout << "NO";
        return 0;
      }
    }
  }
  std::cout << "YES";
  return 0;
}


// Очередь с приоритетом для задач 2
class PriorityQueue {
 public:
  bool empty() const;
  int top() const;
  int pop();
  void push(int value);
};
