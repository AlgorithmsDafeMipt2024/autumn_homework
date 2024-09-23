#pragma once

// std libs:
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <variant>

#include "util.hpp"

// using weight_t = long;

template <typename vert_t, typename weight_t>
class Graph {
 public:
  /// @brief Инициализирует новый экземпляр Graph
  Graph() : edges_(), verts_() {}

  /**
   * @brief Создает новый экземпляр Graph по ребрам,
   * представленными вектором std::pair (НЕВЗВЕШЕННЫЙ)
   * @param edges_pairs: ребра графа
   * @return Graph: новый экземпляр Graph
   */
  static Graph GraphNonWeighted(
      const std::vector<std::pair<vert_t, vert_t>>& edges_pairs);

  /**
   * @brief Создает новый экземпляр Graph по ребрам,
   * представленными вектором std::pair и weight_t (ВЗВЕШЕННЫЙ)
   * @param edges_pairs: ребра графа
   * @param weights: веса ребер
   * @return Graph: новый экземпляр Graph
   *
   * @example code:
   * std::vector<std::pair<vert_t, vert_t>> edges_pairs = {{0, 1}, {1, 2},
   *                                                       {2, 0}};
   * std::vector<long> weights = {1, 2, 3};
   * Graph graph = Graph::GraphWeighted(edges_pairs, weights);
   */
  static Graph GraphWeighted(
      const std::vector<std::pair<vert_t, vert_t>>& edges_pairs,
      const std::vector<weight_t>& weights);

  /**
   * @brief Создает новый экземпляр Graph по ребрам
   * представленными вектором std::tuple (ВЗВЕШЕННЫЙ)
   * @param edges_tuples: ребра графа
   * @return Graph: новый экземпляр Graph
   *
   * @example code:
   * std::vector<std::tuple<vert_t, vert_t, weight_t>> input = {
   *   {0, 1, 5}, {1, 2, 10}, {2, 0, 3}};
   * Graph graph = Graph::GraphWeighted(input);
   */
  static Graph GraphWeighted(
      const std::vector<std::tuple<vert_t, vert_t, weight_t>>& edges_tuples);

  /**
   * @brief Создает новый экземпляр Graph по ребрам
   * представленными вектором std::string (НЕВЗВЕШЕННЫЙ)
   * @param edges_strs: ребра графа
   * @return Graph: новый экземпляр Graph
   *
   * @example code:
   * std::vector<std::string> edges_strs = {"0->1", "2->1", "3->2", "1->3"};
   * Graph graph = Graph::GraphFromStrs(edges_strs);
   */
  static Graph GraphFromStrs(const std::vector<std::string>& edges_strs);

  /**
   * @brief Создает новый экземпляр Graph по ребрам
   * представленными словарем из std::string и weight_t (ВЗВЕШЕННЫЙ)
   * @param edges_dict: ребра графа
   * @return Graph: новый экземпляр Graph
   *
   * @example code:
   * std::unordered_map<std::string, weight_t> edges_dict = {
   *     {"0->1", 5}, {"2->1", 1}, {"3->2", 2}, {"1->3", 3}};
   * Graph graph = Graph::GraphFromMap(edges_dict);
   */
  static Graph GraphFromMap(
      const std::unordered_map<std::string, weight_t>& edges_dict);

  /**
   * @brief Создает новый экземпляр Graph по матрице смежности
   * @param adj_matrix: матрица смежности
   * @param is_weighted: взвешен ли граф
   * @return Graph: новый экземпляр Graph
   *
   * @example code:
   * std::vector<std::vector<long>> adj_matrix = {{0, 1, 0},
   *                                              {1, 0, 1},
   *                                              {0, 1, 0}};
   * Graph graph = Graph::GraphFromAdjMatrix(adj_matrix);
   *
   * std::vector<std::vector<long>> adj_matrix_2 = {{0, 1, 0},
   *                                                {1, 0, 5},
   *                                                {0, 7, 0}};
   * Graph graph_2 = Graph::GraphFromAdjMatrix(adj_matrix_2, true);
   */
  static Graph GraphFromAdjMatrix(
      const std::vector<std::vector<weight_t>>& adj_matrix,
      bool is_weighted = false);

  /**
   * @brief Создает новый экземпляр Graph
   * по списку смежности (НЕВЗВЕШЕННЫЙ)
   * @param adj_list: список смежности
   * @return Graph: новый экземпляр Graph
   *
   * @example code:
   * std::vector<std::vector<vert_t>> adj_list = {{1},
   *                                              {0, 2},
   *                                              {1}};
   * Graph graph = Graph::GraphFromAdjList(adj_list);
   */
  static Graph GraphFromAdjList(
      const std::vector<std::vector<vert_t>>& adj_list);

  /// @brief Проверяет, взвешен ли граф
  bool IsWeighted() const;

  /// @return vert_t: кол-во вершин
  vert_t VertsAmount() const { return verts_.size(); }

  /// @return vert_t: кол-во ребер
  vert_t EdgesAmount() const { return edges_.size(); }

  /// @return const std::vector<vert_t>&: вершины
  const std::vector<vert_t>& Verts() const { return verts_; }

  /// @return std::vector<std::tuple<vert_t, vert_t, weight_t>>: ребра
  std::vector<std::tuple<vert_t, vert_t, weight_t>> Edges() const;

  /**
   * @brief Выводит в поток список вершин
   * @param os: входной поток
   * @return std::ostream&: выходной поток
   */
  std::ostream& PrintVerts(std::ostream& os = std::cout) const;

  /**
   * @brief Выводит в поток список ребер
   * @param os: входной поток
   * @return std::ostream&: выходной поток
   */
  std::ostream& PrintEdges(std::ostream& os = std::cout) const;

  /**
   * @brief Выводит в поток список смежности
   * @param os: входной поток
   * @return std::ostream&: выходной поток
   */
  std::ostream& PrintAdjList(std::ostream& os = std::cout) const;

  /**
   * @brief Делает граф ненаправленным (удаляет лишние ребра)
   * @param remove_duplicates: удалять ли дубликаты
   */
  void MakeUndirected(bool remove_duplicates = false);

  /// @brief Делает граф направленным (ничего)
  void MakeDirected() { is_direct = true; }

  /// @brief Проверяет, направлен ли граф
  bool IsDirected() const { return is_direct; }

  /// @brief Удаляет из графа ребрами с одинаковым вершинами
  void RemoveDuplicates();

  /// @return std::vector<std::vector<vert_t>>: список смежности
  std::vector<std::vector<vert_t>> GetAdjList() const;

  /// @return std::vector<std::vector<vert_t>>: матрица смежности
  std::vector<std::vector<weight_t>> GetAdjMatrix() const;

  /**
   * @brief Проверяет, содержится ли ребро в графе (ВЗВЕШЕННЫЙ)
   * @param edge: ребро
   * @return true: содержится
   * @return false: не содержится
   */
  bool ContainsEdge(const std::tuple<vert_t, vert_t, weight_t>& edge) const;

  /**
   * @brief Проверяет, содержится ли ребро в графе (НЕВЗВЕШЕННЫЙ)
   * @param edge: ребро
   * @return true: содержится
   * @return false: не содержится
   */
  bool ContainsEdge(const std::pair<vert_t, vert_t>& edge) const;

  /**
   * @brief Находит вес ребра в взвешенном графе
   * @param edge: ребро
   * @return weight_t: вес
   */
  weight_t GetWeightOfEdge(const std::pair<vert_t, vert_t>& edge) const;

  void AddVert(vert_t vert);
  void AddEdge(vert_t start_vert, vert_t end_vert, weight_t weight);
  void AddEdge(vert_t start_vert, vert_t end_vert);

  void RemoveVert(vert_t vert);
  void RemoveEdge(const std::pair<vert_t, vert_t>& edge_pair);
  void RemoveEdge(const std::tuple<vert_t, vert_t, weight_t>& edge_tuple);

 private:
  class Edge {
   public:
    Edge() = delete;

    Edge(vert_t start_vert, vert_t end_vert)
        : start_vert_{start_vert}, end_vert_{end_vert} {}

    Edge(vert_t start_vert, vert_t end_vert, weight_t weight);

    Edge(std::pair<vert_t, vert_t> edge_pair);
    Edge(std::tuple<vert_t, vert_t, weight_t> edge_tuple);

    bool IsWeighted() const { return weight_ != 0; }

    vert_t StartVert() const { return start_vert_; }
    vert_t EndVert() const { return end_vert_; }
    weight_t Weight() const;

    // friend std::ostream& operator<<(std::ostream& os,
    //                                 const Graph<vert_t, weight_t>::Edge&
    //                                 edge);
    friend Graph;

    bool operator==(const Edge& rhs) const {
      return start_vert_ == rhs.start_vert_ && end_vert_ == rhs.end_vert_ &&
             weight_ == rhs.weight_;
    }

    bool operator!=(const Edge& rhs) const { return !(*this == rhs); }

    auto operator<=>(const Edge& rhs) const;

    const std::string& Name() const;

   private:
    vert_t start_vert_;
    vert_t end_vert_;
    weight_t weight_ = 0;
  };

  std::vector<Edge> edges_;
  std::vector<vert_t> verts_;

  bool is_direct = true;

 public:
  friend std::ostream& operator<<(std::ostream& os,
                                  const Graph<vert_t, weight_t>::Edge& edge) {
    os << edge.Name();
    return os;
  }

 private:
  Graph(const std::vector<Edge>& edges);

  static std::pair<vert_t, vert_t> ParseEdgeString(const std::string& edge_str);
};

// template <typename vert_t, typename weight_t>
// inline std::ostream& operator<<(std::ostream& os,
//                                 const Graph<vert_t, weight_t>::Edge& edge)

template <typename vert_t, typename weight_t>
inline std::ostream& operator<<(std::ostream& os,
                                const Graph<vert_t, weight_t>& graph) {
  os << "Edges:\n     ";
  graph.PrintEdges(os);

  os << "\n";

  os << "Vertices:\n     ";
  graph.PrintVerts(os);
  return os;
}

template <typename vert_t, typename weight_t>
inline vert_t StartVertFromTuple(
    const std::tuple<vert_t, vert_t, weight_t>& edge) {
  return std::get<0>(edge);
}

template <typename vert_t, typename weight_t>
inline vert_t EndVertFromTuple(
    const std::tuple<vert_t, vert_t, weight_t>& edge) {
  return std::get<1>(edge);
}

template <typename vert_t, typename weight_t>
inline weight_t WeightFromTuple(
    const std::tuple<vert_t, vert_t, weight_t>& edge) {
  return std::get<2>(edge);
}
