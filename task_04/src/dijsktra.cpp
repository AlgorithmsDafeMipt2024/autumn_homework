#include "dijkstra.hpp"

bool FirstGreater::operator()(std::pair<double, int> const& lhs,
                    std::pair<double, int> const& rhs) const 
        { return lhs.first > rhs.first; }


std::vector<double> dijkstra(OrientedWeightedGraph graph, int from_key)
{
    double infinity = std::numeric_limits<double>::infinity();
    // 0 -- haven't visited this vertex yet 
    // 1 -- have already visited this vertex
    std::vector<double> visited(graph.size(), 0);
    std::vector<double> distances(graph.size(), infinity);
    std::priority_queue<std::pair<double, int>,
                        std::vector<std::pair<double, int>>,
                        FirstGreater> queue;
    int N = graph.size(), current;
    distances[from_key] = 0;
    queue.push(std::make_pair(distances[from_key], from_key));
    
    while (!queue.empty()) {
        current = queue.top().second;
        queue = {};
        for(int i=0; i<N; ++i) {
            if (visited[i] == 1 || i == current) 
                continue;
            if (distances[current] + graph[current][i] < distances[i])
                distances[i] = distances[current] + graph[current][i];
        }
        visited[current] = 1;
        for(int i=0; i<N; ++i)
            if (!visited[i])
                queue.push(std::make_pair(distances[i], i));
    }

    return distances;
}