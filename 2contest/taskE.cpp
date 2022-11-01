#include <iostream>
#include <string>
#include <vector>
using std::cin, std::cout, std::vector, std::string, std::swap;

class Heap {
 public:
  Heap(const string& type) {
    type_of_heap_ = type;
    a_.push_back(0);
  }

  void Insert(int x);
  void ExtractTop();
  int GetTop();
  int Size();
  void Clear();

 private:
  string type_of_heap_;
  vector<int> a_;

  void SiftUp(int v);
  void SiftDown(int v);
  bool Cmp(int a, int b);
};

class HeapMinMax {
 public:
  HeapMinMax() { size_ = 0; }

  void Insert(int x);
  void ExtractMin();
  void ExtractMax();
  int GetMin();
  int GetMax();
  int Size();
  void Clear();
  bool Empty();

 private:
  Heap heap_min_ = Heap("min");
  Heap heap_min_rubbish_ = Heap("min");
  Heap heap_max_ = Heap("max");
  Heap heap_max_rubbish_ = Heap("max");
  int size_;

  void DeleteRubbish(Heap& h1, Heap& h2);
};

void PrintError() { cout << "error\n"; }
void PrintOk() { cout << "ok\n"; }

int main() {
  HeapMinMax heap_min_max;
  int m;
  cin >> m;
  for (int k = 0; k < m; ++k) {
    string s;
    cin >> s;
    if (s == "insert") {
      int x;
      cin >> x;
      heap_min_max.Insert(x);
      PrintOk();
    } else if (s == "extract_min") {
      if (heap_min_max.Empty()) {
        PrintError();
      } else {
        cout << heap_min_max.GetMin() << '\n';
        heap_min_max.ExtractMin();
      }
    } else if (s == "extract_max") {
      if (heap_min_max.Empty()) {
        PrintError();
      } else {
        cout << heap_min_max.GetMax() << '\n';
        heap_min_max.ExtractMax();
      }
    } else if (s == "get_min") {
      if (heap_min_max.Empty()) {
        PrintError();
      } else {
        cout << heap_min_max.GetMin() << '\n';
      }
    } else if (s == "get_max") {
      if (heap_min_max.Empty()) {
        PrintError();
      } else {
        cout << heap_min_max.GetMax() << '\n';
      }
    } else if (s == "size") {
      cout << heap_min_max.Size() << '\n';
    } else if (s == "clear") {
      heap_min_max.Clear();
      PrintOk();
    }
  }
}

void Heap::SiftUp(int v) {
  while (v != 1 && Cmp(a_[v], a_[v / 2])) {
    swap(a_[v], a_[v / 2]);
    v /= 2;
  }
}
void Heap::SiftDown(int v) {
  while (v <= Size()) {
    int u = 2 * v;
    if (u + 1 <= Size() && Cmp(a_[u + 1], a_[u])) {
      u += 1;
    }
    if (u <= Size() && Cmp(a_[u], a_[v])) {
      swap(a_[u], a_[v]);
      v = u;
    } else {
      break;
    }
  }
}
bool Heap::Cmp(int a, int b) {
  if (type_of_heap_ == "min") {
    return a < b;
  }
  return a > b;
}
void Heap::Insert(int x) {
  a_.push_back(x);
  SiftUp(Size());
}
void Heap::ExtractTop() {
  swap(a_[1], a_[Size()]);
  a_.pop_back();
  SiftDown(1);
}
int Heap::GetTop() { return a_[1]; }
int Heap::Size() { return static_cast<int>(a_.size()) - 1; }
void Heap::Clear() {
  a_.clear();
  a_.push_back(0);
}

void HeapMinMax::Insert(int x) {
  heap_min_.Insert(x);
  heap_max_.Insert(x);
  ++size_;
}
void HeapMinMax::ExtractMin() {
  int min = heap_min_.GetTop();
  heap_min_rubbish_.Insert(min);
  heap_max_rubbish_.Insert(min);
  --size_;
}
void HeapMinMax::ExtractMax() {
  int max = heap_max_.GetTop();
  heap_max_rubbish_.Insert(max);
  heap_min_rubbish_.Insert(max);
  --size_;
}
int HeapMinMax::GetMin() {
  DeleteRubbish(heap_min_, heap_min_rubbish_);
  return heap_min_.GetTop();
}
int HeapMinMax::GetMax() {
  DeleteRubbish(heap_max_, heap_max_rubbish_);
  return heap_max_.GetTop();
}
int HeapMinMax::Size() { return size_; }
void HeapMinMax::Clear() {
  heap_min_.Clear();
  heap_max_.Clear();
  heap_min_rubbish_.Clear();
  heap_max_rubbish_.Clear();
  size_ = 0;
}
bool HeapMinMax::Empty() { return size_ == 0; }
void HeapMinMax::DeleteRubbish(Heap& h1, Heap& h2) {
  while (h2.Size() > 0 && h2.Size() > 0 && h1.GetTop() == h2.GetTop()) {
    h1.ExtractTop();
    h2.ExtractTop();
  }
}
