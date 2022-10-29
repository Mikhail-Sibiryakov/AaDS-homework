#include <iostream>
#include <string>
#include <vector>
using std::cin, std::cout, std::vector, std::string, std::swap;

class Heap {
 public:
  Heap() : num_(1'000'000, 0), pointer_(1'000'000, 0) {
    a_.push_back(0);
    number_ = 0;
  }

  void Insert(long long x);
  long long GetMin();
  void ExtractMin();
  void DecreaseKey(long long i, long long delta);

 private:
  long long number_;
  vector<long long> a_;
  vector<long long> num_;
  vector<long long> pointer_;

  void Exchange(long long v, long long u);
  void SiftUp(long long v);
  void SiftDown(long long v);
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Heap heap = Heap();
  long long q;
  cin >> q;
  for (long long k = 0; k < q; ++k) {
    string s;
    cin >> s;
    if (s == "insert") {
      long long x;
      cin >> x;
      heap.Insert(x);
    } else if (s == "getMin") {
      cout << heap.GetMin() << '\n';
    } else if (s == "extractMin") {
      heap.ExtractMin();
    } else if (s == "decreaseKey") {
      long long i;
      long long delta;
      cin >> i >> delta;
      heap.DecreaseKey(i, delta);
    }
  }
}

void Heap::Insert(long long x) {
  a_.push_back(x);
  long long v = static_cast<long long>(a_.size()) - 1;
  ++number_;
  num_[v] = number_;
  pointer_[number_] = v;
  SiftUp(v);
}
void Heap::Exchange(long long v, long long u) {
  long long k = num_[v];
  long long m = num_[u];
  swap(a_[v], a_[u]);
  swap(num_[v], num_[u]);
  swap(pointer_[k], pointer_[m]);
}
void Heap::SiftUp(long long v) {
  while (v != 1 && a_[v / 2] > a_[v]) {
    Exchange(v / 2, v);
    v /= 2;
  }
}
void Heap::SiftDown(long long v) {
  while (v < static_cast<long long>(a_.size())) {
    long long u = 2 * v;
    if (2 * v + 1 < static_cast<long long>(a_.size()) &&
        a_[2 * v + 1] < a_[u]) {
      u = 2 * v + 1;
    }
    if (u < static_cast<long long>(a_.size()) && a_[u] < a_[v]) {
      Exchange(v, u);
      v = u;
    } else {
      break;
    }
  }
}
long long Heap::GetMin() {
  ++number_;
  return a_[1];
}
void Heap::ExtractMin() {
  Exchange(1, static_cast<long long>(a_.size()) - 1);
  a_.pop_back();
  SiftDown(1);
  ++number_;
}
void Heap::DecreaseKey(long long i, long long delta) {
  long long v = pointer_[i];
  a_[v] -= delta;
  SiftUp(v);
  ++number_;
}
