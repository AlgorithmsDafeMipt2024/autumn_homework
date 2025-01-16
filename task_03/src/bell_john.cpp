#include "bell_john.hpp"

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