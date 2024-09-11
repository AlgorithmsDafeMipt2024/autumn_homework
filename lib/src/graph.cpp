#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <unordered_map>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <iostream>

template<typename T, typename NameType>
class Graph {
    static_assert(std::is_arithmetic<T>::value, "Graph: paths' lenghts must be arithmetic!");
    class node {
    public:
        node(NameType name) : name{name}, paths{} {}
        NameType name{NameType()};
        std::unordered_map<node*, T> paths;

        void descr_path(node* n, T lenght = 1) {
            paths[n] = lenght;
        }

        ~node() {
            paths = {};
            name = NameType();
        }
    };

public:

    Graph(std::initializer_list<std::pair<NameType, NameType>> links, T base_lenght = 1) {
        add_paths(links, base_lenght);
    }

    Graph(std::initializer_list<std::pair<std::pair<NameType, NameType>, T>> links) {
        add_paths(links);
    }

    node* find_via_name(NameType name) {
        auto ans = std::find_if(nodes.begin(), nodes.end(), [&name](const node* x){ return x->name == name; } );
        if (ans == nodes.end()) {
            return nullptr;
        }
        return *ans;
    }

    node* operator[](NameType name) {
        find_via_name(name);
    }

    void add_paths(std::initializer_list<std::pair<NameType, NameType>> links, T base_lenght = 1) {
        /* { {Name1, Name2}, ... }*/
        for (auto i: links) {
            node* first = find_via_name(i.first);
            if (! first ) {
                first = new node{i.first};
                nodes.push_back(first);
            }
            node* second = find_via_name(i.second);
            if (! second && first != second){
                second = new node{i.second};
                nodes.push_back(second);
            }
            first->descr_path(second, base_lenght);
            continue;
        }
    }

    void add_paths(std::initializer_list<std::pair<std::pair<NameType, NameType>, T>> links) {
        /* { { Name1, Name2 }, lenght }, ... }
        */
        for (auto i: links) {
            node* first = find_via_name(i.first.first);
            if (! first ) {
                first = new node{i.first.first};
                nodes.push_back(first);
            }
            node* second = find_via_name(i.first.second);
            if (! second && first != second){
                second = new node{i.first.second};
                nodes.push_back(second);
            }
            first->descr_path(second, i.second);
            continue;
        }
    }

    ~Graph() {
        for (node* i : nodes) {
            delete i;
        }
        nodes = {};
    }

    void see_vertical() {
        for (auto i : nodes) {
            if (i->paths.size() == 0) {
                std::cout << i->name << std::endl;
                continue;
            }
            for (auto k : i->paths) {
                std::cout << i->name << " -> " << k.first->name << ", l:" << k.second << std::endl;
            }
        }
    }

    friend std::ostream& operator<< (std::ostream& os, const Graph<T, NameType>& g) {
        os << "Graph( ";
        for (auto i : g.nodes) {
            if (i->paths.size() == 0) {
                os << "{" << i->name << "}";
                continue;
            }
            for (auto k : i->paths) {
                os << "{" << i->name << " -> " << k.first->name << ", l:" << k.second << "}, ";
            }
        }
        os << ")";
        return os;
    }

private:
    std::vector<node*> nodes;
};

#endif
