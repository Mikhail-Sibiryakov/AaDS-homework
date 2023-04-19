#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using std::cout, std::cin, std::vector, std::pair;

enum class Color { WHITE, GRAY, BLACK };

class FindBridges {
 public:
  FindBridges(int n, int m)
      : n_(n),
        m_(m),
        graph_(n, vector<int>()),
        used_(n, false),
        tin_(n, 0),
        ret_(n, 0) {
    for (int i = 0; i < m; ++i) {
      int u, v;
      cin >> u >> v;
      --u;
      --v;
      graph_[u].push_back(v);
      graph_[v].push_back(u);
      edges_.emplace_back(u, v);
      set_edges_.insert({u, v});
      set_edges_.insert({v, u});
    }

    for (int i = 0; i < n; ++i) {
      if (!used_[i]) {
        Dfs(i);
      }
    }

    cout << bridges_.size() << '\n';
    for (int i = 0; i < m; ++i) {
      if (bridges_.count(edges_[i]) || bridges_.count({edges_[i].second, edges_[i].first})) {
        cout << i + 1 << ' ';
      }
    }
  }

 private:
  int n_;
  int m_;
  vector<vector<int>> graph_;
  vector<bool> used_;
  vector<int> tin_;
  vector<int> ret_;
  int timer_ = 0;
  std::set<pair<int, int>> bridges_;
  std::multiset<pair<int, int>> set_edges_;
  vector<pair<int, int>> edges_;

  void Dfs(int v, int parent = -1) {
    used_[v] = true;
    ret_[v] = tin_[v] = timer_++;
    for (int to : graph_[v]) {
      if (to == parent) {
        continue;
      }
      if (used_[to]) {
        ret_[v] = std::min(ret_[v], tin_[to]);
      } else {
        Dfs(to, v);
        ret_[v] = std::min(ret_[v], ret_[to]);
        if (ret_[to] > tin_[v] && set_edges_.count({to, v}) == 1) {
          bridges_.insert({v, to});
        }
      }
    }
  }
};

int main() {
  int n, m;
  cin >> n >> m;
  FindBridges(n, m);
}
