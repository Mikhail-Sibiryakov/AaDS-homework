#include <algorithm>
#include <iostream>
#include <vector>
using std::cout, std::cin, std::vector, std::pair;

template <typename T>
void Print(vector<T>& v) {
  for (size_t i = v.size(); i >= 1; --i) {
    cout << v[i - 1] << '\n';
  }
  cout << '\n';
}

int main() {
  int n, w;
  cin >> n >> w;
  vector<int> weight(n);
  for (int i = 0; i < n; ++i) {
    cin >> weight[i];
  }
  vector<int> cost(n);
  for (int i = 0; i < n; ++i) {
    cin >> cost[i];
  }

  vector<vector<int>> dp(n + 1, vector<int>(w + 1, 0));
  vector<vector<bool>> p(n + 1, vector<bool>(w + 1, false));
  dp[0][0] = 0;
  for (int i = 1; i < n + 1; ++i) {
    for (int x = 1; x < w + 1; ++x) {
      dp[i][x] = dp[i - 1][x];
      if (x - weight[i - 1] < 0) {
        continue;
      }
      if (dp[i - 1][x - weight[i - 1]] + cost[i - 1] > dp[i][x]) {
        dp[i][x] = dp[i - 1][x - weight[i - 1]] + cost[i - 1];
        p[i][x] = true;
      }
    }
  }

  vector<int> arr;
  int i = n, x = w;
  while (dp[i][x] > 0) {
    if (p[i][x]) {
      arr.push_back(i);
      x -= weight[i - 1];
    }
    --i;
  }
  Print(arr);
}
