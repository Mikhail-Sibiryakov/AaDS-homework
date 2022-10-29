#include <iostream>
#include <vector>
using std::cin, std::cout, std::vector;

const int kBlock = 10000;
const int kMaxLen = 4;

void SortByIndex(vector<vector<int>*>& a, int k) {
  vector<vector<int>*> ans(a.size(), nullptr);
  vector<int> cnt(kBlock, 0);
  for (auto& i : a) {
    ++cnt[(*i)[k]];
  }
  for (int i = 1; i < kBlock; ++i) {
    cnt[i] += cnt[i - 1];
  }
  for (int i = a.size() - 1; i >= 0; --i) {
    ans[cnt[(*a[i])[k]] - 1] = a[i];
    --cnt[(*a[i])[k]];
  }
  for (int i = 0; i < static_cast<int>(a.size()); ++i) {
    a[i] = ans[i];
  }
}

void Split(unsigned long long n, vector<int>*& ans) {
  while (n > 0) {
    (*ans).push_back(static_cast<int>(n % kBlock));
    n /= kBlock;
  }
  while ((*ans).size() < kMaxLen) {
    (*ans).push_back(0);
  }
}

unsigned long long Join(vector<int>*& a) {
  unsigned long long pow = 1;
  unsigned long long ans = (*a)[0];
  for (int i = 1; i < static_cast<int>((*a).size()); ++i) {
    pow *= kBlock;
    ans += (*a)[i] * pow;
  }
  return ans;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  cin >> n;
  vector<vector<int>*> a(n, nullptr);
  for (int k = 0; k < n; ++k) {
    unsigned long long tmp;
    cin >> tmp;
    a[k] = new vector<int>;
    Split(tmp, a[k]);
  }
  for (int i = 0; i < kMaxLen; ++i) {
    SortByIndex(a, i);
  }
  for (auto i : a) {
    cout << Join(i) << '\n';
    delete i;
  }
}
