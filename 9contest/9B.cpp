#include <iostream>
#include <vector>
#include <set>
using std::cout, std::cin, std::vector, std::set, std::pair;

const int INF = 1e9 + 7;

void getMinSpanningTreePrima(vector<vector<pair<int, int>>>& graph,
                             vector<vector<pair<int, int>>>& spanning_tree) {
  vector<int> min_edge(graph.size(), INF);
  vector<int> select_edge(graph.size(), -1);
  vector<bool> used(graph.size(), false);
  min_edge[0] = 0;
  set<pair<int, int>> queue_vertices;
  queue_vertices.insert({0, 0});
  for (int i = 0; i < graph.size(); ++i) {
    int vertex = queue_vertices.begin()->second;
    int weight = queue_vertices.begin()->first;
    queue_vertices.erase(queue_vertices.begin());

    if (select_edge[vertex] != -1) {
      used[vertex] = true;
      used[select_edge[vertex]] = true;
      spanning_tree[vertex].push_back({select_edge[vertex], weight});
      spanning_tree[select_edge[vertex]].push_back({vertex, weight});
    }
    for (auto el : graph[vertex]) {
      int to = el.first;
      int cost = el.second;
      if (cost < min_edge[to] && !used[to]) {
        queue_vertices.erase({min_edge[to], to});
        min_edge[to] = cost;
        select_edge[to] = vertex;
        queue_vertices.insert({min_edge[to], to});
      }
    }
  }
}

int getSumAllEdges(vector<vector<pair<int, int>>>& graph) {
  int sum = 0;
  for (auto& list : graph) {
    for (auto& edges : list) {
      sum += edges.second;
    }
  }
  return sum;
}

int main() {
  int number_vertices;
  int number_edges;
  cin >> number_vertices >> number_edges;
  vector<vector<pair<int, int>>> graph(number_vertices);
  for (int i = 0; i < number_edges; ++i) {
    int begin, end, weight;
    cin >> begin >> end >> weight;
    graph[begin - 1].push_back({end - 1, weight});
    graph[end - 1].push_back({begin - 1, weight});
  }
  vector<vector<pair<int, int>>> spanning_tree(number_vertices);
  getMinSpanningTreePrima(graph, spanning_tree);
  cout << getSumAllEdges(spanning_tree) / 2 << '\n';
}
