#include <gtest/gtest.h>

#include "packman.hpp"

TEST(Test, Example_1) {
  // Example 1: Small graph
  DependencyGraph dg;
  std::vector<std::string> packages = {"Basic_Package", "Extention"};
  for (const auto& package : packages) dg.AddVertex(package);

  dg.AddDirEdge(1, 0);

  PackageManager packman(dg);

  std::vector<std::vector<std::string>> answers{{"Basic_Package"},
                                                {"Basic_Package", "Extention"}};

  for (size_t i = 0; i < answers.size(); ++i)
    ASSERT_EQ(answers[i], packman.FindDownloadingOrder(packages[i]));
}
TEST(Test, Example_2) {
  // Example 2: Three vertices, one edge
  DependencyGraph dg;

  std::vector<std::string> packages = {"First", "Second", "Independent"};

  for (const auto& package : packages) dg.AddVertex(package);

  dg.AddDirEdge(1, 0);

  PackageManager packman(dg);

  std::vector<std::vector<std::string>> answers{
      {"First"}, {"First", "Second"}, {"Independent"}};

  for (size_t i = 0; i < answers.size(); ++i)
    ASSERT_EQ(answers[i], packman.FindDownloadingOrder(packages[i]));
}

TEST(Test, Example_3) {
  // Example 3: Five vertices, more complex dependencies
  DependencyGraph dg;

  std::vector<std::string> packages = {"BaseLib", "TestLib", "DataLib",
                                       "AlgorithmLib", "ToolLib"};

  for (const auto& package : packages) dg.AddVertex(package);

  dg.AddDirEdge(1, 0);
  dg.AddDirEdge(2, 0);
  dg.AddDirEdge(3, 2);
  dg.AddDirEdge(4, 3);

  PackageManager packman(dg);

  std::vector<std::vector<std::string>> answers{
      {"BaseLib"},
      {"BaseLib", "TestLib"},
      {"BaseLib", "DataLib"},
      {"BaseLib", "DataLib", "AlgorithmLib"},
      {"BaseLib", "DataLib", "AlgorithmLib", "ToolLib"}};

  for (size_t i = 0; i < answers.size(); ++i)
    ASSERT_EQ(answers[i], packman.FindDownloadingOrder(packages[i]));
}

TEST(Test, Example_4) {
  // Example 4: More complex graph, multiple paths
  DependencyGraph dg;

  std::vector<std::string> packages = {"Start", "A1", "A2", "B1",
                                       "B2",    "C1", "C2", "End"};

  for (const auto& package : packages) dg.AddVertex(package);

  dg.AddDirEdge(1, 0);
  dg.AddDirEdge(2, 0);
  dg.AddDirEdge(3, 1);
  dg.AddDirEdge(4, 2);
  dg.AddDirEdge(5, 3);
  dg.AddDirEdge(6, 4);
  dg.AddDirEdge(7, 5);
  dg.AddDirEdge(7, 6);

  PackageManager packman(dg);

  std::vector<std::vector<std::string>> answers{
      {"Start"},
      {"Start", "A1"},
      {"Start", "A2"},
      {"Start", "A1", "B1"},
      {"Start", "A2", "B2"},
      {"Start", "A1", "B1", "C1"},
      {"Start", "A2", "B2", "C2"},
      {"Start", "A1", "B1", "C1", "A2", "B2", "C2", "End"}};

  for (size_t i = 0; i < answers.size(); ++i)
    ASSERT_EQ(answers[i], packman.FindDownloadingOrder(packages[i]));
}