#include <algorithm>
#include <iostream>
#include <vector>
using std::cin, std::cout, std::pair, std::vector;

struct Edge {
  int from;
  int to;
  int cost;
};

const int kINF = INT32_MAX;
const int kNotEdge = 100'000;
const int kEmpty = -1;

void FordBellman(int n_v, int m_e, int start, vector<Edge>& edges) {
  vector<int> dist(n_v, 0);
  vector<int> parent(n_v, -1);
  int vertex = kEmpty;
  dist[start] = 0;
  for (int i = 0; i < n_v; ++i) {
    vertex = kEmpty;
    for (int j = 0; j < m_e; ++j) {
      if (dist[edges[j].from] < kINF) {
        if (dist[edges[j].to] > dist[edges[j].from] + edges[j].cost) {
          dist[edges[j].to] =
              std::max(-kINF, dist[edges[j].from] + edges[j].cost);
          parent[edges[j].to] = edges[j].from;
          vertex = edges[j].to;
        }
      }
    }
  }
  cout << (vertex == kEmpty ? "NO\n" : "YES\n");
  if (vertex == kEmpty) {
    return;
  }
  int vertex_cycle = vertex;
  for (int i = 0; i < n_v; ++i) {
    vertex_cycle = parent[vertex_cycle];
  }
  vector<int> path;
  for (int prev = vertex_cycle;; prev = parent[prev]) {
    path.push_back(prev);
    if (prev == vertex_cycle && path.size() > 1) {
      break;
    }
  }
  std::reverse(path.begin(), path.end());
  cout << path.size() << '\n';
  for (int el : path) {
    cout << el + 1 << ' ';
  }
}

int main() {
  int n_v;
  cin >> n_v;
  vector<Edge> edges;
  for (int i = 0; i < n_v; ++i) {
    for (int j = 0; j < n_v; ++j) {
      int cost;
      cin >> cost;
      if (cost == kNotEdge) {
        continue;
      }
      edges.push_back(Edge{i, j, cost});
    }
  }
  FordBellman(n_v, edges.size(), 0, edges);
}
