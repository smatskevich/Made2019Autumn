#include <iostream>
#include <vector>
#include <deque>


// Узел односвязного списка
struct QueueNode {
  int data;
  QueueNode* next;
};

class Queue {
 public:
  ~Queue();

  // Проверка очереди на пустоту
  bool empty() const;
  // Добавление элемента
  void push(int value);
  QueueNode* head = nullptr;
 private:
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


class Graph {
 private:
  std::vector<Queue*> nodes = {new Queue()};

 public:
  void add_edge(int start, int end);
  int count_routes(int start, int end);
};


void Graph::add_edge(int start, int end) {
  while (nodes.size() < start + 1) {
    Queue *new_list = new Queue();
    nodes.push_back(new_list);
  }

  while (nodes.size() < end + 1) {
    Queue *new_list = new Queue();
    nodes.push_back(new_list);
  }
  nodes[start]->push(end);
  nodes[end]->push(start);
}

int Graph::count_routes(int start, int end) {
  std::deque<int> queue;
  std::vector<std::pair<int, int>> routes;
  int element;
  for (int i=0; i<nodes.size(); i++) {
    routes.push_back(std::make_pair(0, nodes.size() + 1));
  }
  routes[start] = std::make_pair(1, 0);
  queue.push_back(start);
  while(!queue.empty()) {
    element = queue.front();
    queue.pop_front();
    if (element == end) return routes[end].first;
    QueueNode* edge = nodes[element]->head;
    while (edge) {
      if (routes[edge->data].second == nodes.size() + 1) {
        queue.push_back(edge->data);
      }
      if (!(routes[edge->data].second <= routes[element].second)) {
        routes[edge->data].first += routes[element].first;
        routes[edge->data].second = routes[element].second + 1;
      }
      edge = edge->next;
    }
  }
  return 0;
}