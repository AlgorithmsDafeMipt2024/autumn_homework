#include <gtest/gtest.h>

#include "packman.hpp"

TEST(Test, Example_1) {
  // Example 1: Small graph
  DependencyGraph dg_1;

  dg_1.AddVertex("Basic_Package");
  dg_1.AddVertex("Extention");

  dg_1.AddDirEdge(0, 1);

  PackageManager packman_1(dg_1);

  // std::vector<std::vector<std::string>> answers{{"Basic_Package"},
  // {"Basic_Package", "Extention"}};

  std::vector<std::string> answer{"Basic_Package", "Extention"};

  ASSERT_EQ(answer, packman_1.FindDownloadingOrder());
}

TEST(Test, Example_2) {
  // Example 2: Three vertices, one edge
  DependencyGraph dg_2;

  dg_2.AddVertex("First");
  dg_2.AddVertex("Second");
  dg_2.AddVertex("Independent");

  dg_2.AddDirEdge(0, 1);

  PackageManager packman_2(dg_2);

  // std::vector<std::vector<std::string>> answers{
  //     {"First"}, {"First", "Second"}, {"Independent"}};

  std::vector<std::string> answer{{"Independent", "First", "Second"}};

  ASSERT_EQ(answer, packman_2.FindDownloadingOrder());
}

TEST(Test, Example_3) {
  // Example 3: Five vertices, more complex dependencies
  DependencyGraph dg_3;

  dg_3.AddVertex("BaseLib");
  dg_3.AddVertex("TestLib");
  dg_3.AddVertex("DataLib");
  dg_3.AddVertex("AlgorithmLib");
  dg_3.AddVertex("ToolLib");

  dg_3.AddDirEdge(0, 1);
  dg_3.AddDirEdge(0, 2);
  dg_3.AddDirEdge(2, 3);
  dg_3.AddDirEdge(3, 4);

  PackageManager packman_3(dg_3);

  // std::vector<std::vector<std::string>> answers{
  //     {"BaseLib"},
  //     {"BaseLib", "TestLib"},
  //     {"BaseLib", "DataLib"},
  //     {"BaseLib", "DataLib", "AlgorithmLib"},
  //     {"BaseLib", "DataLib", "AlgorithmLib", "ToolLib"}};

  std::vector<std::string> answer{"BaseLib", "DataLib", "AlgorithmLib",
                                  "ToolLib", "TestLib"};

  ASSERT_EQ(answer, packman_3.FindDownloadingOrder());
}

TEST(Test, Example_4) {
  // Example 4: More complex graph, multiple paths
  DependencyGraph dg_4;

  dg_4.AddVertex("Start");
  dg_4.AddVertex("A1");
  dg_4.AddVertex("A2");
  dg_4.AddVertex("B1");
  dg_4.AddVertex("B2");
  dg_4.AddVertex("C1");
  dg_4.AddVertex("C2");
  dg_4.AddVertex("End");

  dg_4.AddDirEdge(0, 1);
  dg_4.AddDirEdge(0, 2);
  dg_4.AddDirEdge(1, 3);
  dg_4.AddDirEdge(2, 4);
  dg_4.AddDirEdge(3, 5);
  dg_4.AddDirEdge(4, 6);
  dg_4.AddDirEdge(5, 7);
  dg_4.AddDirEdge(6, 7);
  PackageManager packman_4(dg_4);

  // std::vector<std::vector<std::string>> answers{
  //     {"Start"},
  //     {"Start", "A1"},
  //     {"Start", "A2"},
  //     {"Start", "A1", "B1"},
  //     {"Start", "A2", "B2"},
  //     {"Start", "A1", "B1", "C1"},
  //     {"Start", "A2", "B2", "C2"},
  //     {"Start", "A1", "B1", "C1", "A2", "B2", "C2", "End"}};

  std::vector<std::string> answer{"Start", "A1", "B1", "C1",
                                  "A2",    "B2", "C2", "End"};

  ASSERT_EQ(answer, packman_4.FindDownloadingOrder());
}