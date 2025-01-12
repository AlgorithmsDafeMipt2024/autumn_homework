#include <gtest/gtest.h>

#include "lca.hpp"

TEST(LCATest, IntGraphDirected) {
  Graph<int, int> graph =
      Graph<int, int>::GraphFromAdjList({{1, 2}, {0, 3, 4}, {0, 5, 6}});
  LCA<int, int> lca(graph, 0);
  EXPECT_EQ(lca.RequestLCA(3, 4), 1);
  EXPECT_EQ(lca.RequestLCA(3, 6), 0);
  EXPECT_EQ(lca.RequestLCA(5, 6), 2);
  EXPECT_EQ(lca.RequestLCA(1, 6), 0);
  EXPECT_EQ(CalculateLCA(graph, 0, 3, 4), 1);  // Test FindLCA function
  EXPECT_EQ(CalculateLCA(graph, 0, 3, 6), 0);
}

TEST(LCATest, IntGraphUndirected) {
  Graph<int, int> graph =
      Graph<int, int>::GraphFromAdjList({{1, 2}, {0, 3, 4}, {0, 5, 6}});
  graph.MakeUndirected();
  LCA<int, int> lca(graph, 0);
  EXPECT_EQ(lca.RequestLCA(3, 4), 1);
  EXPECT_EQ(lca.RequestLCA(3, 6), 0);
  EXPECT_EQ(lca.RequestLCA(5, 6), 2);
  EXPECT_EQ(lca.RequestLCA(1, 6), 0);
  EXPECT_EQ(CalculateLCA(graph, 0, 3, 4), 1);  // Test FindLCA function
  EXPECT_EQ(CalculateLCA(graph, 0, 3, 6), 0);
}

TEST(LCATest, IntGraphSingleNode) {
  Graph<int, int> graph;

  EXPECT_THROW((LCA<int, int>(graph, 0)), std::invalid_argument);

  graph.AddVert(0);

  LCA<int, int> lca(graph, 0);
  // If there is only the root, LCA should still work, return the root itself
  EXPECT_EQ(lca.RequestLCA(0, 0), 0);
  // test if we can actually call CalculateLCA function with an empty graph
  EXPECT_EQ(CalculateLCA(graph, 0, 0, 0), 0);
}

// Тесты для класса LCA и функции FindLCA с string вершинами
TEST(LCATest, StringGraphDirected) {
  Graph<std::string, int> graph = Graph<std::string, int>::GraphFromStrs(
      {"a->b", "a->c", "b->d", "b->e", "c->f", "c->g"});
  LCA<std::string, int> lca(graph, "a");
  EXPECT_EQ(lca.RequestLCA("d", "e"), "b");
  EXPECT_EQ(lca.RequestLCA("d", "f"), "a");
  EXPECT_EQ(lca.RequestLCA("g", "e"), "a");
  EXPECT_EQ(lca.RequestLCA("b", "g"), "a");
  EXPECT_EQ(
      CalculateLCA(graph, std::string("a"), std::string("d"), std::string("e")),
      std::string("b"));  // Test FindLCA function
  EXPECT_EQ(
      CalculateLCA(graph, std::string("a"), std::string("d"), std::string("f")),
      std::string("a"));
}

TEST(LCATest, StringGraphUndirected) {
  Graph<std::string, int> graph = Graph<std::string, int>::GraphFromStrs(
      {"a->b", "a->c", "b->d", "b->e", "c->f", "c->g"});
  graph.MakeUndirected();
  LCA<std::string, int> lca(graph, "a");
  EXPECT_EQ(lca.RequestLCA("d", "e"), "b");
  EXPECT_EQ(lca.RequestLCA("d", "f"), "a");
  EXPECT_EQ(lca.RequestLCA("g", "e"), "a");
  EXPECT_EQ(lca.RequestLCA("b", "g"), "a");
  EXPECT_EQ(
      CalculateLCA(graph, std::string("a"), std::string("d"), std::string("e")),
      std::string("b"));  // Test FindLCA function
  EXPECT_EQ(
      CalculateLCA(graph, std::string("a"), std::string("d"), std::string("f")),
      std::string("a"));
}

TEST(LCATest, StringGraphSingleNode) {
  Graph<std::string, int> graph = Graph<std::string, int>::GraphFromStrs({});

  EXPECT_THROW((LCA<std::string, int>(graph, "a")), std::invalid_argument);

  graph.AddVert("a");

  LCA<std::string, int> lca(graph, "a");
  EXPECT_EQ(lca.RequestLCA("a", "a"), "a");
  EXPECT_EQ(
      CalculateLCA(graph, std::string("a"), std::string("a"), std::string("a")),
      std::string("a"));
}

// Тесты для граничных случаев
TEST(LCATest, SameNodeLCA) {
  Graph<int, int> graph =
      Graph<int, int>::GraphFromAdjList({{1, 2}, {0, 3, 4}, {0, 5, 6}});
  LCA<int, int> lca(graph, 0);
  EXPECT_EQ(lca.RequestLCA(3, 3), 3);
  EXPECT_EQ(CalculateLCA(graph, 0, 3, 3), 3);
}

TEST(LCATest, RootNodeLCA) {
  Graph<int, int> graph =
      Graph<int, int>::GraphFromAdjList({{1, 2}, {0, 3, 4}, {0, 5, 6}});
  LCA<int, int> lca(graph, 0);
  EXPECT_EQ(lca.RequestLCA(0, 3), 0);
  EXPECT_EQ(CalculateLCA(graph, 0, 0, 3), 0);
}

TEST(LCATest, IsolatedIntVertex) {
  Graph<int, int> graph =
      Graph<int, int>::GraphFromAdjList({{1, 2}, {0, 3, 4}, {0, 5, 6}});
  LCA<int, int> lca(graph, 0);

  EXPECT_THROW({ lca.RequestLCA(3, 7); }, std::invalid_argument);
  EXPECT_THROW({ CalculateLCA(graph, 0, 3, 7); }, std::invalid_argument);
}

TEST(LCATest, IsolatedStringVertex) {
  Graph<std::string, int> graph = Graph<std::string, int>::GraphFromStrs(
      {"a->b", "a->c", "b->d", "b->e", "c->f", "c->g"});
  LCA<std::string, int> lca(graph, "a");
  EXPECT_THROW({ lca.RequestLCA("d", "h"); }, std::invalid_argument);
  EXPECT_THROW(
      {
        CalculateLCA(graph, std::string("a"), std::string("d"),
                     std::string("h"));
      },
      std::invalid_argument);
}

TEST(LCATest, IsolatedIntRoot) {
  Graph<int, int> graph;
  EXPECT_THROW((LCA<int, int>(graph, 0)),
               std::invalid_argument);  // проверяем исключение в конструкторе
}

TEST(LCATest, NotConnectedToInt) {
  Graph<int, int> graph = Graph<int, int>::GraphFromAdjList(
      std::vector<std::vector<int>>({{}, {}}));

  EXPECT_THROW({ CalculateLCA(graph, 0, 0, 1); }, std::logic_error);
}

TEST(LCATest, NotConnectedToString) {
  Graph<std::string, int> graph =
      Graph<std::string, int>::GraphFromStrs({"a->b"});
  LCA<std::string, int> lca(graph, "a");
  EXPECT_THROW({ lca.RequestLCA("a", "c"); }, std::logic_error);
  EXPECT_THROW(
      {
        CalculateLCA(graph, std::string("a"), std::string("a"),
                     std::string("c"));
      },
      std::logic_error);
}

TEST(LCATest, IntGraphDirected_Complex1) {
  Graph<int, int> graph =
      Graph<int, int>::GraphFromAdjList({{1, 2}, {3, 4}, {5}, {}, {}, {}});
  LCA<int, int> lca(graph, 0);
  EXPECT_EQ(lca.RequestLCA(3, 4), 1);
  EXPECT_EQ(lca.RequestLCA(3, 5), 0);
  EXPECT_EQ(lca.RequestLCA(4, 5), 0);
  EXPECT_EQ(lca.RequestLCA(1, 2), 0);
  EXPECT_EQ(CalculateLCA(graph, 0, 3, 4), 1);
  EXPECT_EQ(CalculateLCA(graph, 0, 3, 5), 0);
}

TEST(LCATest, IntGraphDirected_Complex2) {
  Graph<int, int> graph = Graph<int, int>::GraphFromAdjList(
      {{1, 2}, {3, 4}, {5}, {6}, {}, {7}, {}});
  LCA<int, int> lca(graph, 0);
  EXPECT_EQ(lca.RequestLCA(6, 7), 0);
  EXPECT_EQ(lca.RequestLCA(3, 6), 3);
  EXPECT_EQ(lca.RequestLCA(5, 7), 5);
  EXPECT_EQ(lca.RequestLCA(4, 7), 0);

  EXPECT_EQ(CalculateLCA(graph, 0, 6, 7), 0);
  EXPECT_EQ(CalculateLCA(graph, 0, 3, 6), 3);
}

TEST(LCATest, IntGraphUndirected_Complex1) {
  Graph<int, int> graph =
      Graph<int, int>::GraphFromAdjList({{1, 2}, {0, 3, 4}, {0}, {1}, {1}, {}});
  graph.MakeUndirected();
  LCA<int, int> lca(graph, 0);
  EXPECT_EQ(lca.RequestLCA(3, 4), 1);
  EXPECT_EQ(lca.RequestLCA(2, 3), 0);
  EXPECT_EQ(lca.RequestLCA(4, 2), 0);
  EXPECT_EQ(lca.RequestLCA(1, 4), 1);
  EXPECT_EQ(CalculateLCA(graph, 0, 3, 4), 1);
  EXPECT_EQ(CalculateLCA(graph, 0, 2, 3), 0);
}

TEST(LCATest, IntGraphUndirected_Complex2) {
  Graph<int, int> graph = Graph<int, int>::GraphFromAdjList(
      {{1}, {0, 2, 3}, {1}, {1, 4}, {3, 5, 6}, {4}, {4}});
  graph.MakeUndirected();
  LCA<int, int> lca(graph, 0);
  EXPECT_EQ(lca.RequestLCA(4, 5), 4);
  EXPECT_EQ(lca.RequestLCA(2, 5), 1);
  EXPECT_EQ(lca.RequestLCA(1, 6), 1);
  EXPECT_EQ(lca.RequestLCA(1, 4), 1);
  EXPECT_EQ(CalculateLCA(graph, 0, 4, 5), 4);
  EXPECT_EQ(CalculateLCA(graph, 0, 2, 5), 1);
}

TEST(LCATest, StringGraphDirected_Complex1) {
  Graph<std::string, int> graph = Graph<std::string, int>::GraphFromStrs(
      {"a->b", "a->c", "b->d", "c->e", "c->f", "f->g"});
  LCA<std::string, int> lca(graph, "a");
  EXPECT_EQ(lca.RequestLCA("d", "g"), "a");
  EXPECT_EQ(lca.RequestLCA("g", "e"), "c");
  EXPECT_EQ(lca.RequestLCA("b", "f"), "a");
  EXPECT_EQ(
      CalculateLCA(graph, std::string("a"), std::string("d"), std::string("g")),
      std::string("a"));
  EXPECT_EQ(
      CalculateLCA(graph, std::string("a"), std::string("g"), std::string("e")),
      std::string("c"));
}

TEST(LCATest, StringGraphDirected_Complex2) {
  Graph<std::string, int> graph = Graph<std::string, int>::GraphFromStrs(
      {"a->b", "a->c", "b->d", "b->e", "c->f", "f->g", "f->h", "g->i"});
  LCA<std::string, int> lca(graph, "a");
  EXPECT_EQ(lca.RequestLCA("i", "h"), "f");
  EXPECT_EQ(lca.RequestLCA("d", "i"), "a");
  EXPECT_EQ(lca.RequestLCA("e", "d"), "b");
  EXPECT_EQ(
      CalculateLCA(graph, std::string("a"), std::string("i"), std::string("h")),
      std::string("f"));
  EXPECT_EQ(
      CalculateLCA(graph, std::string("a"), std::string("d"), std::string("e")),
      std::string("b"));
}

TEST(LCATest, StringGraphUndirected_Complex1) {
  Graph<std::string, int> graph = Graph<std::string, int>::GraphFromStrs(
      {"a->b", "a->c", "b->d", "c->e", "c->f", "f->g"});
  graph.MakeUndirected();
  LCA<std::string, int> lca(graph, "a");
  EXPECT_EQ(lca.RequestLCA("e", "g"), "c");
  EXPECT_EQ(lca.RequestLCA("b", "e"), "a");
  EXPECT_EQ(lca.RequestLCA("b", "c"), "a");
  EXPECT_EQ(
      CalculateLCA(graph, std::string("a"), std::string("e"), std::string("g")),
      std::string("c"));
  EXPECT_EQ(
      CalculateLCA(graph, std::string("a"), std::string("b"), std::string("e")),
      std::string("a"));
}

TEST(LCATest, StringGraphUndirected_Complex2) {
  Graph<std::string, int> graph = Graph<std::string, int>::GraphFromStrs(
      {"a->b", "b->c", "b->d", "c->e", "c->f", "d->g", "d->h", "e->i", "f->j"});
  graph.MakeUndirected();
  LCA<std::string, int> lca(graph, "a");
  EXPECT_EQ(lca.RequestLCA("i", "j"), "c");
  EXPECT_EQ(lca.RequestLCA("c", "g"), "b");
  EXPECT_EQ(lca.RequestLCA("a", "j"), "a");
  EXPECT_EQ(
      CalculateLCA(graph, std::string("a"), std::string("i"), std::string("j")),
      std::string("c"));
  EXPECT_EQ(
      CalculateLCA(graph, std::string("a"), std::string("c"), std::string("g")),
      std::string("b"));
}
