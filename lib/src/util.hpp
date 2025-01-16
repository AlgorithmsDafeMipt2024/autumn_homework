#include <vector>
#include <limits>

class EdgeOrientedGraph {
    // Contains directions for each corresponding vertex key;
    // Key is the order in which vector<int> are stored.
    // Keys start from zero.
    std::vector<std::vector<int>> _ways;

public:
    // int V : the amount of vertices;
    // Vector<vector<int>> : edges of the graph {..., (start_i, end_i), ...}.
    EdgeOrientedGraph(int V, std::vector<std::vector<int>> edges);
    // Transfers `_ways`
    EdgeOrientedGraph(EdgeOrientedGraph const& graph);

    // Returns the amount of vertices in the graph.
    int size();
    // Returns all available directions from vertex with same key value.
    std::vector<int>& operator[](int key);
};

class MatrixOrientedGraph {
    // Matrix of connections.
    // First index is a key of the beginning vertex;
    // Second index is a key of the end vertex.
    // 0  -- vertices are not connected;
    // >0 -- vertices are connected
    std::vector<std::vector<int>> _connections;
public:
    // Creates empty connection matrix.
    // int V : amount of vertices. 
    MatrixOrientedGraph(int V);
    // Copies `connections` matrix into `_connections`.
    MatrixOrientedGraph(std::vector<std::vector<int>> const& connections);

    // Returns the integer to tell if an edge exists.
    // First index is a key of the beginning vertex;
    // Second index is a key of the end vertex.
    std::vector<int>& operator[](int first);
};


class OrientedWeightedGraph {
    // Matrix of weights.
    // First index is a key of the beginning vertex;
    // Second index is a key of the end vertex.
    std::vector<std::vector<double>> _weights;
public:
    // Creates weight matrix with all infinite weights.
    // int V : amount of vertices.
    OrientedWeightedGraph(int V);
    // Creates weight matrix with the same values as the `weights` matrix.
    OrientedWeightedGraph(std::vector<std::vector<double>> const& weights);
    // Transfers matrix
    OrientedWeightedGraph(OrientedWeightedGraph const& graph);

    // Add zero weight vertex needed for Johnson's algorithm.
    void _zero_vertex();
    // Deletes the last vertex from the weight matrix.
    void _delete_vertex();
    // Returns the amount of vertices in the graph.
    int size();
    // Returns the weight of an edge.
    // First index is a key of the beginning vertex;
    // Second index is a key of the end vertex.
    std::vector<double>& operator[](int first);
};
