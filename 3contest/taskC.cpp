#include <iostream>
#include <vector>
using std::cout, std::cin, std::vector;

const int kInf = -2;

struct Node {
  int value;
  int tl;
  int tr;
};

class SegmentTree {
 public:
  SegmentTree(const vector<int>& a);
  void Set(int x, int i) { Update(i + tree_.size() / 2, x); }
  int GetAns(int i, int x) { return Solve(1, i, tree_.size() / 2 - 1, x); }

 private:
  vector<Node> tree_;

  static unsigned int GetMinDegTwo(int n);
  void Update(int v, int x);
  int Solve(int vertex, int left, int right, int x);
  int FindAns(int vertex, int tl, int tr, int x);
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

SegmentTree::SegmentTree(const vector<int>& a) : tree_(GetMinDegTwo(a.size())) {
  int n = tree_.size() / 2;
  for (size_t i = 0; i + n < tree_.size(); ++i) {
    tree_[i + n].value = (i < a.size() ? a[i] : 0);
    tree_[i + n].tl = tree_[i + n].tr = i;
  }
  for (size_t i = n; i > 1; --i) {
    tree_[i - 1].value =
        std::max(tree_[2 * (i - 1)].value, tree_[2 * (i - 1) + 1].value);
    tree_[i - 1].tl = tree_[2 * (i - 1)].tl;
    tree_[i - 1].tr = tree_[2 * (i - 1) + 1].tr;
  }
}

unsigned int SegmentTree::GetMinDegTwo(int n) {
  unsigned int ans = 1;
  n = 2 * n - 1;
  while (n > 0) {
    n /= 2;
    ans *= 2;
  }
  return ans;
}

void SegmentTree::Update(int v, int x) {
  if (tree_[v].tl == tree_[v].tr) {
    tree_[v].value = x;
  } else {
    tree_[v].value = std::max(tree_[v * 2].value, tree_[v * 2 + 1].value);
  }
  if (v == 1) {
    return;
  }
  Update(v / 2, x);
}

int SegmentTree::Solve(int vertex, int left, int right, int x) {
  if (tree_[vertex].tl == left && tree_[vertex].tr == right) {
    return FindAns(vertex, left, right, x);
  }
  int ans = kInf;
  int tm = (tree_[vertex].tr + tree_[vertex].tl) / 2;
  if (left <= tm) {
    ans = Solve(2 * vertex, left, std::min(tm, right), x);
  }
  if (ans != kInf) {
    return ans;
  }
  return Solve(2 * vertex + 1, std::max(tm + 1, left), right, x);
}

int SegmentTree::FindAns(int vertex, int tl, int tr, int x) {
  if (tree_[vertex].value < x) {
    return kInf;
  }
  if (tl == tr) {
    return vertex - (tree_.size() / 2);
  }
  int tm = (tree_[vertex].tr + tree_[vertex].tl) / 2;
  int tmp = FindAns(vertex * 2, tl, tm, x);
  if (tmp != kInf) {
    return tmp;
  }
  return FindAns(vertex * 2 + 1, tm + 1, tr, x);
}
