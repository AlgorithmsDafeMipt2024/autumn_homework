#include "util.hpp"

EdgeOrientedGraph::EdgeOrientedGraph(int V, std::vector<std::vector<int>> edges) {
    _ways = std::vector<std::vector<int>>(V);
    for (auto x : edges)
        _ways[x[0]].push_back(x[1]);
}

EdgeOrientedGraph::EdgeOrientedGraph(EdgeOrientedGraph const& graph) : _ways(graph._ways) {}

int EdgeOrientedGraph::size() { return _ways.size(); }

std::vector<int>& EdgeOrientedGraph::operator[] (int key) { return _ways[key]; }


MatrixOrientedGraph::MatrixOrientedGraph(int V) {
    _connections = std::vector<std::vector<int>>(V, std::vector<int>(V));
}

MatrixOrientedGraph::MatrixOrientedGraph(std::vector<std::vector<int>> const& connections) : _connections(connections) {}

int OrientedWeightedGraph::size() { return _weights.size(); }

std::vector<int>& MatrixOrientedGraph::operator[](int first) { return _connections[first]; }


OrientedWeightedGraph::OrientedWeightedGraph(int V) {
    _weights = std::vector<std::vector<double>>(V, 
        std::vector<double>(V, std::numeric_limits<double>::infinity()));
}

OrientedWeightedGraph::OrientedWeightedGraph(std::vector<std::vector<double>> const& weights) : _weights(weights) {
    int V = weights.size();
    for (auto& x : weights)
        if (V != x.size())
            throw std::exception();
}

OrientedWeightedGraph::OrientedWeightedGraph(OrientedWeightedGraph const& graph) : _weights(graph._weights) {}

void OrientedWeightedGraph::_zero_vertex() {
    for (auto& x : _weights)
        x.push_back(std::numeric_limits<double>::infinity());
    _weights.push_back(std::vector<double>(this->size()+1));
    _weights[this->size()-1][this->size()-1] = std::numeric_limits<double>::infinity();
}

void OrientedWeightedGraph::_delete_vertex() {
    _weights.pop_back();
    for (auto& x : _weights)
        x.pop_back();
}

int OrientedWeightedGraph::size() { return _weights.size(); }

std::vector<double>& OrientedWeightedGraph::operator[](int first) { return _weights[first]; }