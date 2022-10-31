#include <iostream>
#include <vector>
using std::cin, std::cout, std::vector;

const int kBlock = 256;
const int kMaxLen = 8;

int GetByte(unsigned long long n, int i) {
  unsigned long long k = 255;
  n = n >> (8 * i);
  return static_cast<int>(n & k);
}

void SortByByte(vector<unsigned long long>& a, int k) {
  vector<int> cnt(kBlock, 0);
  vector<unsigned long long> ans(a.size());
  for (auto i : a) {
    ++cnt[GetByte(i, k)];
  }
  for (size_t i = 1; i < kBlock; ++i) {
    cnt[i] += cnt[i - 1];
  }
  for (size_t i = a.size(); i > 0; --i) {
    ans[cnt[GetByte(a[i - 1], k)] - 1] = a[i - 1];
    --cnt[GetByte(a[i - 1], k)];
  }
  for (size_t i = 0; i < a.size(); ++i) {
    a[i] = ans[i];
  }
}

void LSD(vector<unsigned long long>& a) {
  for (int i = 0; i < kMaxLen; ++i) {
    SortByByte(a, i);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  cin >> n;
  vector<unsigned long long> a(n);
  for (int k = 0; k < n; ++k) {
    cin >> a[k];
  }
  LSD(a);
  for (auto i : a) {
    cout << i << '\n';
  }
}
