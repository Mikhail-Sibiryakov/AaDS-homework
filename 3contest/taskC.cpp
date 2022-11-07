#include <iostream>
#include <vector>
using std::cout, std::cin, std::vector;

const int kInf = -2;

class SegmentTree {
 public:
  SegmentTree(const vector<int>& a);
  void Set(int x, int i) { Update(i, x); }
  void Update(int i, int x) { Update(i + t_.size() / 2, i, i, x); }
  int GetAns(int i, int x) {
    return Solve(1, 0, t_.size() / 2 - 1, {i, t_.size() / 2 - 1}, x);
  }

 private:
  vector<int> t_;

  unsigned int GetMinDegTwo(int n);
  void Update(int v, int tl, int tr, int x);
  int Solve(int v, int tl, int tr, std::pair<int, int> p, int x);
  int FindAns(int v, int tl, int tr, int x);
};

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  SegmentTree st(a);
  for (int k = 0; k < m; ++k) {
    int type, i, x;
    cin >> type >> i >> x;
    if (type == 0) {
      st.Set(x, i - 1);
    } else {
      cout << st.GetAns(i - 1, x) + 1 << '\n';
    }
  }
}

SegmentTree::SegmentTree(const vector<int>& a) : t_(GetMinDegTwo(a.size()), 0) {
  int n = t_.size() / 2;
  for (size_t i = 0; i < a.size(); ++i) {
    t_[i + n] = a[i];
  }
  for (size_t i = n; i > 1; --i) {
    t_[i - 1] = std::max(t_[2 * (i - 1)], t_[2 * (i - 1) + 1]);
  }
}
unsigned int SegmentTree::GetMinDegTwo(int n) {
  unsigned int ans = 1;
  n = 2 * n - 1;
  while (n > 0) {
    n /= 2;
    ans = ans << 1;
  }
  return ans;
}
void SegmentTree::Update(int v, int tl, int tr, int x) {
  if (tl == tr) {
    t_[v] = x;
  } else {
    t_[v] = std::max(t_[v * 2], t_[v * 2 + 1]);
  }
  if (v == 1) {
    return;
  }
  if (v % 2 == 1) {
    Update(v / 2, tl - (tr - tl + 1), tr, x);
  } else {
    Update(v / 2, tl, tr + (tr - tl + 1), x);
  }
}
int SegmentTree::Solve(int v, int tl, int tr, std::pair<int, int> p, int x) {
  int l = p.first;
  int r = p.second;
  if (tl == l && tr == r) {
    return FindAns(v, l, r, x);
  }
  int tm = (tl + tr) >> 1;
  int ans = kInf;
  if (l <= tm) {
    ans = Solve(2 * v, tl, tm, {l, std::min(tm, r)}, x);
  }
  if (ans != kInf) {
    return ans;
  }
  return Solve(2 * v + 1, tm + 1, tr, {std::max(tm + 1, l), r}, x);
}
int SegmentTree::FindAns(int v, int tl, int tr, int x) {
  if (t_[v] < x) {
    return kInf;
  }
  if (tl == tr) {
    return v - (t_.size() / 2);
  }
  int tm = (tl + tr) >> 1;
  int tmp = FindAns(v * 2, tl, tm, x);
  if (tmp != kInf) {
    return tmp;
  }
  return FindAns(v * 2 + 1, tm + 1, tr, x);
}
