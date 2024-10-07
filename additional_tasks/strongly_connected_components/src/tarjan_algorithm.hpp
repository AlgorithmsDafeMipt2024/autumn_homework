#pragma once

#include <algorithm>
#include <stack>

#include "graph/graph.hpp"

template <typename vert_t>
static std::vector<vert_t> StronglyConnectedComponentsStep(
    const vert_t& v, size_t& curr_index, std::stack<vert_t>& verts_stack,
    std::unordered_map<vert_t, size_t>& indexes,
    std::unordered_map<vert_t, size_t>& low_links,
    std::unordered_map<vert_t, bool>& is_on_stack,
    std::unordered_map<vert_t, std::vector<vert_t>>& adj_list)

{
  // в curr_index храним количество ранее обработанных вершин,
  // indexes[v] - это "время входа" в вершину v
  indexes[v] = curr_index;
  low_links[v] = curr_index;
  curr_index++;

  verts_stack.push(v);

  // is_on_stack нужно, чтобы проверять принадлежность вершины стеку за O(1)
  is_on_stack[v] = true;

  // перебираем рёбра, исходящие из v
  for (size_t i = 0; i < adj_list[v].size(); i++) {
    vert_t w = adj_list[v][i];

    if (indexes[w] == 0) {
      // вершина w ранее не посещалась; запускаемся из неё рекурсивно
      StronglyConnectedComponentsStep(w, curr_index, verts_stack, indexes,
                                      low_links, is_on_stack, adj_list);

      low_links[v] = std::min(low_links[v], low_links[w]);
    } else if (is_on_stack[w]) {
      // вершина w находится в стеке, значит, принадлежит той же компоненте
      // сильной связности, что и v

      // если w не в стеке, значит, ребро (v, w) ведёт в ранее обработанную
      // компоненту сильной связности и должна быть проигнорирована

      //! замечание: в следующей строке намеренно используется indexes[w] вместо
      //! low_links[w] - это отсылает к исходной статье Тарьяна

      //(если заменить indexes[w] на low_links[w], ничего не изменится)
      low_links[v] = std::min(low_links[v], indexes[w]);
    }
  }

  vert_t u{};
  std::vector<vert_t> strongly_connected_components{};

  // вершина v - корень текущей компоненты сильной связности,
  // все вершины в стеке от v и выше образуют эту компоненту
  if (low_links[v] == indexes[v]) {
    do {
      u = verts_stack.top();
      verts_stack.pop();

      is_on_stack[u] = false;
      strongly_connected_components.push_back(u);
    } while (u != v);
  }

  return strongly_connected_components;
}

template <typename vert_t, typename weight_t>
std::vector<std::vector<vert_t>> StronglyConnectedComponents(
    Graph<vert_t, weight_t> graph) {
  std::vector<std::vector<vert_t>> ans{};

  std::stack<vert_t> verts_stack;
  size_t curr_index = 0;

  std::unordered_map<vert_t, size_t> indexes;
  std::unordered_map<vert_t, size_t> low_links;
  std::unordered_map<vert_t, bool> is_on_stack;

  for (auto const& vert : graph.Verts()) {
    indexes[vert] = 0;
    low_links[vert] = 0;
    is_on_stack[vert] = false;
  }

  // std::unordered_map<vert_t, size_t> indexes(
  //     graph.Verts().begin(), graph.Verts().end(),
  //     [](const vert_t& vert) { return 0; });
  // std::unordered_map<vert_t, size_t> low_links(indexes);  // копируем из
  // indexes std::unordered_map<vert_t, bool> is_on_stack(
  //     graph.Verts().begin(), graph.Verts().end(),
  //     [](const vert_t& vert) { return false; });

  std::unordered_map<vert_t, std::vector<vert_t>> adj_list = graph.GetAdjList();

  for (const auto& v : graph.Verts())
    if (indexes[v] == 0) {
      // std::cout << indexes << std::endl;

      ans.push_back(StronglyConnectedComponentsStep(v, curr_index, verts_stack,
                                                    indexes, low_links,
                                                    is_on_stack, adj_list));
    }

  return ans;
}
