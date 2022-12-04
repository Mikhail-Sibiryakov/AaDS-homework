#include <iostream>
#include <vector>
using std::cin, std::cout, std::vector;

const int kM = 1'000'100;

class Set {
 private:
  vector<vector<int>> arr_;

 public:
  Set() : arr_(kM, vector<int>()) {}
  void Push(int x);
  bool Find(int x);
  void Erase(int x);
};

int main() {
  Set set;
  int m;
  cin >> m;
  for (int i = 0; i < m; ++i) {
    char type;
    int n;
    cin >> type >> n;
    if (type == '+') {
      set.Push(n);
    } else if (type == '-') {
      set.Erase(n);
    } else if (type == '?') {
      if (set.Find(n)) {
        cout << "YES" << '\n';
      } else {
        cout << "NO" << '\n';
      }
    }
  }
}

void Set::Push(int x) {
  if (!Find(x)) {
    size_t hash = std::hash<int>{}(x) % kM;
    arr_[hash].push_back(x);
  }
}
bool Set::Find(int x) {
  size_t hash = std::hash<int>{}(x) % kM;
  for (auto i : arr_[hash]) {
    if (i == x) {
      return true;
    }
  }
  return false;
}
void Set::Erase(int x) {
  size_t hash = std::hash<int>{}(x) % kM;
  for (size_t i = 0; i < arr_[hash].size(); ++i) {
    if (arr_[hash][i] == x) {
      std::swap(arr_[hash][i], arr_[hash][arr_[hash].size() - 1]);
      arr_[hash].pop_back();
      break;
    }
  }
}
