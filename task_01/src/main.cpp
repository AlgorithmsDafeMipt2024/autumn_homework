#include "packman.hpp"

int main() {
  DependencyGraph dg_1;

  dg_1.AddVertex("Lib_1");
  dg_1.AddVertex("Lib_2");
  dg_1.AddVertex("Lib_3");
  dg_1.AddVertex("Lib_4");
  dg_1.AddVertex("Lib_5");

  dg_1.AddDirEdge(0, 1);
  dg_1.AddDirEdge(0, 2);
  dg_1.AddDirEdge(2, 3);
  dg_1.AddDirEdge(3, 1);
  dg_1.AddDirEdge(0, 3);

  PackageManager packman_1(dg_1);

  for (size_t j = 0; j < dg_1.Size(); ++j)
    packman_1.FindDownloadingOrder(dg_1[j]);
}
