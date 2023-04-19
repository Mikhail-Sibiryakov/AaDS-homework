#include <algorithm>
#include <iostream>
#include <vector>
using std::cout, std::cin, std::vector, std::pair;

enum class Color { WHITE, GRAY, BLACK };

class ComponentsStrongConnect {
 public:
  ComponentsStrongConnect(int n, int m)
      : n_(n),
        m_(m),
        graph_(n, vector<int>()),
        graph_r_(n, vector<int>()),
        colors_(n, Color::WHITE),
        components_(n, 0) {
    for (int i = 0; i < m; ++i) {
      int u, v;
      cin >> u >> v;
      graph_[u - 1].push_back(v - 1);
      graph_r_[v - 1].push_back(u - 1);
    }

    for (int i = 0; i < n; ++i) {
      if (colors_[i] == Color::WHITE) {
        Dfs(i);
      }
    }

    std::reverse(order_.begin(), order_.end());
    for (int u : order_) {
      if (components_[u] == 0) {
        ++cnt_comp_;
        FindComponents(u);
      }
    }

    cout << cnt_comp_ << '\n';
    for (int i : components_) {
      cout << i << ' ';
    }
    cout << '\n';
  }

 private:
  int n_;
  int m_;
  vector<vector<int>> graph_;
  vector<vector<int>> graph_r_;
  vector<Color> colors_;
  vector<int> components_;
  vector<int> order_;
  int cnt_comp_ = 0;

  void Dfs(int v) {
    colors_[v] = Color::GRAY;
    for (int to : graph_[v]) {
      if (colors_[to] == Color::WHITE) {
        Dfs(to);
      }
    }
    order_.push_back(v);
  }

  void FindComponents(int v) {
    components_[v] = cnt_comp_;
    for (int to : graph_r_[v]) {
      if (components_[to] == 0) {
        FindComponents(to);
      }
    }
  }
};

int main() {
  int n, m;
  cin >> n >> m;
  ComponentsStrongConnect(n, m);
}
