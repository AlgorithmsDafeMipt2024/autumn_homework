#include "packman.hpp"

int main() {
  DependencyGraph dg_1;

  dg_1.AddVertex("Lib_1");
  dg_1.AddVertex("Lib_2");
  dg_1.AddVertex("Lib_3");
  dg_1.AddVertex("Lib_4");
  dg_1.AddVertex("Lib_5");

  dg_1.AddDirEdge(dg_1[0], dg_1[1]);
  dg_1.AddDirEdge(dg_1[1], dg_1[2]);
  dg_1.AddDirEdge(dg_1[2], dg_1[3]);
  dg_1.AddDirEdge(dg_1[4], dg_1[1]);
  dg_1.AddDirEdge(dg_1[0], dg_1[3]);

  dg_1.PrintGraph();

  dg_1.DeleteDirEdge(dg_1[0], dg_1[1]);

  dg_1.PrintGraph();
}
