#include <iostream>
#include <vector>
using std::cout, std::cin, std::vector, std::pair;

class SparseTable {
 public:
  SparseTable(const vector<int>& a);
  int GetSecondStatistic(int l, int r);

 private:
  vector<vector<pair<pair<int, int>, int>>> sparse_;

  int LogN(int n);
  int GetSecondSelect(const pair<pair<int, int>, int>& p1,
                      const pair<pair<int, int>, int>& p2);
  int GetMaxDegreeOfTwo(int n);
};

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  SparseTable st(a);
  for (int i = 0; i < m; ++i) {
    int l, r;
    cin >> l >> r;
    cout << st.GetSecondStatistic(l - 1, r - 1) << '\n';
  }
}

SparseTable::SparseTable(const vector<int>& a)
    : sparse_(LogN(a.size()), vector<pair<pair<int, int>, int>>()) {
  for (size_t i = 0; i < a.size() - 1; ++i) {
    if (a[i] <= a[i + 1]) {
      sparse_[1].push_back({{a[i], i}, std::max(a[i], a[i + 1])});
    } else {
      sparse_[1].push_back({{a[i + 1], i + 1}, std::max(a[i], a[i + 1])});
    }
  }
  for (size_t k = 2; k < sparse_.size(); ++k) {
    for (size_t i = 0; i + (1 << (k - 1)) < sparse_[k - 1].size(); ++i) {
      pair<pair<int, int>, int>& pl = sparse_[k - 1][i];
      pair<pair<int, int>, int>& pr = sparse_[k - 1][i + (1 << (k - 1))];
      sparse_[k].push_back(
          {std::min(pl.first, pr.first), GetSecondSelect(pl, pr)});
    }
  }
}
int SparseTable::GetSecondStatistic(int l, int r) {
  if (r - l + 1 == 2) {
    return sparse_[1][l].second;
  }
  int k = GetMaxDegreeOfTwo(r - l + 1);
  pair<pair<int, int>, int>& pl = sparse_[k][l];
  pair<pair<int, int>, int>& pr = sparse_[k][r - (1 << k) + 1];
  return GetSecondSelect(pl, pr);
}
int SparseTable::GetSecondSelect(const pair<pair<int, int>, int>& p1,
                                 const pair<pair<int, int>, int>& p2) {
  if (p1.first.second == p2.first.second) {
    return std::min(p1.second, p2.second);
  }
  vector<int> a{p1.first.first, p1.second};
  vector<int> b{p2.first.first, p2.second};
  int i = 0;
  int j = 0;
  if (a[i] <= b[j]) {
    ++i;
  } else {
    ++j;
  }
  if (a[i] <= b[j]) {
    return a[i];
  }
  return b[j];
}
int SparseTable::LogN(int n) {
  int ans = 0;
  --n;
  while (n > 0) {
    n /= 2;
    ++ans;
  }
  return ans;
}
int SparseTable::GetMaxDegreeOfTwo(int n) {
  int k = 0;
  --n;
  while (n > 0) {
    n /= 2;
    ++k;
  }
  return std::max(0, k - 1);
}
