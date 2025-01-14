#include <climits>
#include <iostream>

#include "graph.hpp"
#include "util.hpp"

using namespace algo;
using namespace std;

int main() {
  int vertexes_num, edges_num;
  cin >> vertexes_num >> edges_num;

  algo::Graph graph(vertexes_num, edges_num, true);

  for (int i = 0; i < edges_num; i++) {
    int a, b, w;

    cin >> a >> b >> w;

    graph.AddEdge(a, b, w);
  }

  int start;
  cin >> start;

  start--;
  auto ways = FindWays(graph, start);

  for (int i = 0; i < ways.size(); i++) {
    cout << i + 1 << ": " << ways[i] << endl;
  }
}
