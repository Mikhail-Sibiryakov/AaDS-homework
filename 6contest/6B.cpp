#include <algorithm>
#include <iostream>
#include <vector>
using std::cout, std::cin, std::vector, std::pair;

const int kINF = 2147483646 + 1;

void Print(vector<int>& v) {
  for (auto i : v) {
    cout << i << ' ';
  }
  cout << '\n';
}

bool Cmp(int a, int b) { return b <= a; }

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  vector<int> dp(n, -kINF), pos(n, -1), prev(n, -1);
  int k = -1;
  for (int i = 0; i < n; ++i) {
    int j = std::lower_bound(dp.begin(), dp.end(), a[i], Cmp) - dp.begin();
    pos[j] = i;
    dp[j] = a[i];
    if (j >= 1) {
      prev[i] = pos[j - 1];
    }
    k = std::max(k, j);
  }
  int p = pos[k];
  vector<int> ans(k + 1);
  for (int i = 0; i <= k; ++i) {
    ans[k - i] = p + 1;
    p = prev[p];
  }
  cout << ans.size() << '\n';
  Print(ans);
}
