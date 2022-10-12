#include <algorithm>
#include <iostream>
#include <string>

const int kINF = 1'000'000'000 + 10;

struct Node {
  int value;
  int min_value;
  int number;
  Node* next;
};

class Stack {
 public:
  Stack() { head_ = nullptr; }
  ~Stack() { Clear(); }

  void Push(int k);

  int GetSize();

  bool Empty() { return GetSize() == 0; }

  int GetBack();

  void Pop();

  int GetMin();

  void Clear() {
    while (!Empty()) {
      Pop();
    }
  }

 private:
  Node* head_;
};

class Queue {
 public:
  Queue() {
    st1_ = Stack();
    st2_ = Stack();
  }

  ~Queue() { Clear(); }

  void Push(int k) { st1_.Push(k); }

  int GetSize() { return st1_.GetSize() + st2_.GetSize(); }

  bool Empty() { return GetSize() == 0; }

  void PrintFront();

  void Pop();

  int GetMin();

  void PrintMin();

  void Clear() {
    st1_.Clear();
    st2_.Clear();
  }

 private:
  Stack st1_;
  Stack st2_;
  void Moves();
  void PrintError() { std::cout << "error\n"; }
};

int main() {
  Queue queue = Queue();
  int q, m;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    std::string s;
    std::cin >> s;
    if (s == "enqueue") {
      std::cin >> m;
      queue.Push(m);
      std::cout << "ok" << '\n';
    } else if (s == "dequeue") {
      queue.Pop();
    } else if (s == "front") {
      queue.PrintFront();
    } else if (s == "size") {
      std::cout << queue.GetSize() << '\n';
    } else if (s == "clear") {
      queue.Clear();
      std::cout << "ok" << '\n';
    } else if (s == "min") {
      queue.PrintMin();
    }
  }
}
void Stack::Push(int k) {
  Node* new_node;
  new_node = new Node();
  new_node->value = k;
  new_node->next = head_;
  if (Empty()) {
    new_node->min_value = k;
    new_node->number = 1;
  } else {
    new_node->min_value = std::min(k, head_->min_value);
    new_node->number = head_->number + 1;
  }
  head_ = new_node;
}
int Stack::GetSize() {
  if (head_ == nullptr) {
    return 0;
  }
  return head_->number;
}
int Stack::GetBack() {
  if (Empty()) {
    return -kINF;
  }
  return head_->value;
}
void Stack::Pop() {
  if (Empty()) {
    return;
  }
  Node* next = head_->next;
  delete head_;
  head_ = next;
}
int Stack::GetMin() {
  if (Empty()) {
    return -kINF;
  }
  return head_->min_value;
}
void Queue::PrintFront() {
  Moves();
  if (st2_.GetBack() == -kINF) {
    PrintError();
  } else {
    std::cout << st2_.GetBack() << '\n';
  }
}
void Queue::Pop() {
  if (Empty()) {
    PrintError();
    return;
  }
  Moves();
  PrintFront();
  st2_.Pop();
}
int Queue::GetMin() {
  int min_queue = kINF;
  int min_1 = st1_.GetMin();
  int min_2 = st2_.GetMin();
  if (min_1 != -kINF) {
    min_queue = std::min(min_1, min_queue);
  }
  if (min_2 != -kINF) {
    min_queue = std::min(min_2, min_queue);
  }
  return min_queue;
}
void Queue::PrintMin() {
  if (GetMin() < kINF) {
    std::cout << GetMin() << '\n';
  } else {
    PrintError();
  }
}
void Queue::Moves() {
  if (!Empty() && st2_.Empty()) {
    while (!st1_.Empty()) {
      int tmp = st1_.GetBack();
      st1_.Pop();
      st2_.Push(tmp);
    }
  }
}
