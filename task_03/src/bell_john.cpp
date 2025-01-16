#include "bell_john.hpp"

std::vector<double> bellman(OrientedWeightedGraph graph, int from_key, int iterations = std::numeric_limits<int>::infinity()) { 
    if (iterations == std::numeric_limits<int>::infinity())
        iterations = graph.size();
    std::vector<double> distances(graph.size(), std::numeric_limits<double>::infinity()),
                        infinite_row = distances;
    std::vector<std::vector<double>> paths = {};
    int V = graph.size();
    distances[from_key] = 0;
    paths.push_back(distances);
    
    for(int step=1; step<iterations; ++step) {
        paths.push_back(infinite_row);

        for(int from=0; from<V; ++from) {
            double current_weight = paths[step-1][from];
            if (current_weight == std::numeric_limits<double>::infinity())
                continue;

            for(int to=0; to<graph[from].size(); ++to) {
                if (current_weight + graph[from][to] < paths[step][to])
                    paths[step][to] = current_weight + graph[from][to];
                if (current_weight + graph[from][to] < distances[to])
                    distances[to] = current_weight + graph[from][to];
            }
        }
    }
    return distances;
}

std::vector<double> johnson(OrientedWeightedGraph graph, int from_key) {
    graph._zero_vertex();
    std::vector<double> bel_dist = bellman(graph, graph.size()-1);
    graph._delete_vertex();
    int V = graph.size();

    for(int i=0; i<V; ++i)
        for(int j=0; j<V; ++j)
            graph[i][j] += bel_dist[i] - bel_dist[j];
    
    std::vector<double> res_dist = dijkstra(graph, from_key);
    for(int i=0; i<V; ++i)
        res_dist[i] -= bel_dist[from_key] - bel_dist[i];
    return res_dist;
}