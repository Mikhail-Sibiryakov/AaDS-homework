#include <iostream>
#include <vector>
using std::cout, std::cin, std::vector, std::pair;

class SparseTable {
 public:
  SparseTable(const vector<int>& a);
  int GetSecondStatistic(int l, int r);

 private:
  struct Node {
    int first_select;
    size_t index_of_first_select;
    int second_select;
  };
  vector<vector<Node>> sparse_;

  static int LogN(int n);
  static int GetSecondSelect(const Node& segment_1, const Node& segment_2);
  static int GetMaxDegreeOfTwo(int n);
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

SparseTable::SparseTable(const vector<int>& a) : sparse_(LogN(a.size())) {
  for (size_t i = 0; i < a.size() - 1; ++i) {
    if (a[i] <= a[i + 1]) {
      sparse_[1].push_back({a[i], i, std::max(a[i], a[i + 1])});
    } else {
      sparse_[1].push_back({a[i + 1], i + 1, std::max(a[i], a[i + 1])});
    }
  }
  for (size_t k = 2; k < sparse_.size(); ++k) {
    for (size_t i = 0; i + (1 << (k - 1)) < sparse_[k - 1].size(); ++i) {
      Node left = sparse_[k - 1][i];
      Node right = sparse_[k - 1][i + (1 << (k - 1))];
      Node min = (left.first_select < right.first_select ? left : right);
      sparse_[k].push_back({min.first_select,
                            (left.first_select == right.first_select
                                 ? std::min(left.index_of_first_select,
                                            right.index_of_first_select)
                                 : min.index_of_first_select),
                            GetSecondSelect(left, right)});
    }
  }
}
int SparseTable::GetSecondStatistic(int l, int r) {
  if (r - l + 1 == 2) {
    return sparse_[1][l].second_select;
  }
  int k = GetMaxDegreeOfTwo(r - l + 1);
  return GetSecondSelect(sparse_[k][l], sparse_[k][r - (1 << k) + 1]);
}
int SparseTable::GetSecondSelect(const Node& segment_1, const Node& segment_2) {
  if (segment_1.index_of_first_select == segment_2.index_of_first_select) {
    return std::min(segment_1.second_select, segment_2.second_select);
  }
  vector<int> a{segment_1.first_select, segment_1.second_select};
  vector<int> b{segment_2.first_select, segment_2.second_select};
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
