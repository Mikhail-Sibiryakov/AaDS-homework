#include <iostream>
#include <set>
#include <vector>
using std::cin, std::cout, std::set, std::pair, std::vector;

const int kINF = 2009000999;

void Solve(int number, vector<vector<pair<int, int>>>& graph, int start) {
  vector<int> dist(number, kINF);
  dist[start] = 0;
  set<pair<int, int>> queue;
  queue.insert({dist[start], start});
  while (!queue.empty()) {
    int vertex = queue.begin()->second;
    queue.erase(queue.begin());
    for (auto& pair : graph[vertex]) {
      int to = pair.second;
      int len = pair.first;
      if (dist[vertex] + len < dist[to]) {
        queue.erase({dist[to], to});
        dist[to] = dist[vertex] + len;
        queue.insert({dist[to], to});
      }
    }
  }
  for (int el : dist) {
    cout << el << ' ';
  }
  cout << '\n';
}

void Init(vector<int>& v_m, vector<int>& v_n, vector<int>& starts,
          vector<vector<vector<pair<int, int>>>>& all_graphs, int k_iter) {
  for (int i = 0; i < k_iter; ++i) {
    cin >> v_n[i] >> v_m[i];
    all_graphs[i] = vector<vector<pair<int, int>>>(v_n[i]);
    for (int j = 0; j < v_m[i]; ++j) {
      int v1;
      int v2;
      int len;
      cin >> v1 >> v2 >> len;
      all_graphs[i][v1].push_back({len, v2});
      all_graphs[i][v2].push_back({len, v1});
    }
    cin >> starts[i];
  }
}

int main() {
  int k_iter;
  cin >> k_iter;
  vector<vector<vector<pair<int, int>>>> all_graphs(k_iter);
  vector<int> v_m(k_iter);
  vector<int> v_n(k_iter);
  vector<int> starts(k_iter);
  Init(v_m, v_n, starts, all_graphs, k_iter);
  for (int i = 0; i < k_iter; ++i) {
    Solve(v_n[i], all_graphs[i], starts[i]);
  }
}
