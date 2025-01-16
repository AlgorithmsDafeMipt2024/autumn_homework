#include "topo.hpp"

void topo_recr(EdgeOrientedGraph& graph, std::stack<int>& vstack, std::vector<int>& vcolor, int current) {
    vcolor[current] = 1;
    for (auto n : graph[current]) {
        if (vcolor[n] == 2)
            continue;
        if (vcolor[n] == 1) {
            vstack = {};
            throw std::exception(); // if graph is cyclic
        }
        topo_recr(graph, vstack, vcolor, n); 
    }
    vcolor[current] = 2;
    vstack.push(current);
}

std::vector<int> topo_sort(EdgeOrientedGraph graph, int from_key=0) {
    std::vector<int> fin_seq;
    std::stack<int> vert_stack;
    // 0 -- white
    // 1 -- grey
    // 2 -- black
    std::vector<int> vert_color(graph.size());
    vert_color[from_key] = 1;
    topo_recr(graph, vert_stack, vert_color, from_key);
    
    while (!vert_stack.empty()) {
        fin_seq.push_back(vert_stack.top());
        vert_stack.pop();
    }
    return fin_seq;
}