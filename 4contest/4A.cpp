#include <iostream>
#include <list>
#include <random>
#include <vector>
using std::cin, std::cout, std::vector, std::list;

class HashTable {
 private:
  static const long long kM = 1e6 + 1;
  static const long long kP = 1e6 + 3;
  vector<list<int>> arr_;
  long long a_;
  long long b_;

  static long long Randint(long long a, long long b);
  int Hash(int x);

 public:
  HashTable() : arr_(kM), a_(Randint(1, kP - 1)), b_(Randint(0, kP - 1)) {}
  void Push(int x);
  bool Find(int x);
  void Erase(int x);
};

int main() {
  HashTable set;
  int m;
  cin >> m;
  for (int i = 0; i < m; ++i) {
    char type;
    int n;
    cin >> type >> n;
    switch (type) {
      case '+':
        set.Push(n);
        break;
      case '-':
        set.Erase(n);
        break;
      case '?':
        cout << (set.Find(n) ? "YES" : "NO") << '\n';
    }
  }
}

void HashTable::Push(int x) {
  if (!Find(x)) {
    size_t hash = Hash(x);
    arr_[hash].push_back(x);
  }
}
bool HashTable::Find(int x) {
  size_t hash = Hash(x);
  for (auto i : arr_[hash]) {
    if (i == x) {
      return true;
    }
  }
  return false;
}
void HashTable::Erase(int x) {
  size_t hash = Hash(x);
  for (auto i = arr_[hash].begin(); i != arr_[hash].end(); ++i) {
    if (*i == x) {
      arr_[hash].erase(i);
      break;
    }
  }
}
int HashTable::Hash(int x) { return ((a_ * x + b_) % kP) % kM; }

long long HashTable::Randint(long long a, long long b) {
  std::mt19937 engine{std::random_device()()};
  std::uniform_int_distribution<int> range(a, b);
  return range(engine);
}
