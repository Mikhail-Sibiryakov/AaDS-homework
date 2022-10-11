#include <algorithm>
#include <iostream>
#include <string>

const int kINF = 1'000'000'000 + 10;
struct Element {
  int value;
  int min_value;
  int number;
  Element* next;
};
void PrintError() { std::cout << "error\n"; }
void PrintOk() { std::cout << "ok\n"; }
void PushStack(Element** pointer, int k) {
  Element* el;
  el = new Element();
  (*el).value = k;
  (*el).next = *pointer;
  if (*pointer == nullptr) {
    (*el).min_value = k;
    (*el).number = 1;
  } else {
    (*el).min_value = std::min(k, (**pointer).min_value);
    (*el).number = (**pointer).number + 1;
  }
  *pointer = el;
}
void PopStack(Element** pointer) {
  if (*pointer == nullptr) {
    return;
  }
  Element* e = (**pointer).next;
  delete *pointer;
  *pointer = e;
}
int BackStack(Element** pointer) {
  if (*pointer == nullptr) {
    return -1;
  }
  return (**pointer).value;
}
int GetMinStack(Element** pointer) {
  if (*pointer == nullptr) {
    return -1;
  }
  return (**pointer).min_value;
}
int GetSizeStack(Element** pointer) {
  if (*pointer == nullptr) {
    return 0;
  }
  return (**pointer).number;
}
void ClearStack(Element** pointer) {
  while (*pointer != nullptr) {
    PopStack(pointer);
  }
}
void PushQueue(Element** queue, int n) { PushStack(&queue[0], n); }
void Moves(Element** queue) {
  if (queue[0] == nullptr && queue[1] == nullptr) {
    return;
  }
  if (queue[1] == nullptr) {
    while (queue[0] != nullptr) {
      int tmp = BackStack(&queue[0]);
      PopStack(&queue[0]);
      PushStack(&queue[1], tmp);
    }
  }
}
void PopQueue(Element** queue) {
  if (queue[0] == nullptr && queue[1] == nullptr) {
    PrintError();
    return;
  }
  Moves(queue);
  std::cout << BackStack(&queue[1]) << '\n';
  PopStack(&queue[1]);
}
void PrintFrontQueue(Element** queue) {
  Moves(queue);
  int front = BackStack(&queue[1]);
  if (front == -1) {
    PrintError();
  } else {
    std::cout << front << '\n';
  }
}
int GetSizeQueue(Element** queue) {
  return GetSizeStack(&queue[0]) + GetSizeStack(&queue[1]);
}
void ClearQueue(Element** queue) {
  ClearStack(&queue[0]);
  ClearStack(&queue[1]);
}
int GetMinQueue(Element** queue) {
  int min_queue = kINF;
  int min_0 = GetMinStack(&queue[0]);
  int min_1 = GetMinStack(&queue[1]);
  if (min_0 != -1) {
    min_queue = std::min(min_0, min_queue);
  }
  if (min_1 != -1) {
    min_queue = std::min(min_1, min_queue);
  }
  return min_queue;
}
void PrintMinQueue(Element** queue) {
  int m = GetMinQueue(queue);
  if (m < kINF) {
    std::cout << m << '\n';
  } else {
    PrintError();
  }
}
int main() {
  Element* queue[2] = {nullptr, nullptr};
  int q, m;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    std::string s;
    std::cin >> s;
    if (s == "enqueue") {
      std::cin >> m;
      PushQueue(queue, m);
      PrintOk();
    } else if (s == "dequeue") {
      PopQueue(queue);
    } else if (s == "front") {
      PrintFrontQueue(queue);
    } else if (s == "size") {
      std::cout << GetSizeQueue(queue) << '\n';
    } else if (s == "clear") {
      ClearQueue(queue);
      PrintOk();
    } else if (s == "min") {
      PrintMinQueue(queue);
    }
  }
  ClearQueue(queue);
}
