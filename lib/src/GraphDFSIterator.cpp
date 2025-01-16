#include <GraphDFSIterator.h>

GraphDFSIterator::GraphDFSIterator(const WeightedGraph* const graph,
                                   int start_id) {
  this->start_id = start_id;
  this->graph = graph;
  this->is_end = false;
  this_id = start_id;
  visited.resize(graph->GetVerts());
  visited[start_id] = true;
  parent.resize(graph->GetVerts(), -1);
}

int GraphDFSIterator::Next() {
  for (int i = 0; i < graph->GetVerts(); ++i) {
    if ((*graph)[this_id][i] != 0 && !visited[i]) {
      visited[i] = true;
      parent[i] = this_id;
      this_id = i;
      return i;
    }
  }
  if (parent[this_id] == -1) {
    is_end = true;
    return this_id;
  }
  this_id = parent[this_id];
  return Next();
}

bool GraphDFSIterator::IsEnd() { return is_end; }
