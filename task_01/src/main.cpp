#include "packman.hpp"

int main() {
  DependencyGraph dg;

  std::vector<std::string> packages = {"Lib_1", "Lib_2", "Lib_3", "Lib_4",
                                       "Lib_5"};
  for (const auto& package : packages) dg.AddVertex(package);

  dg.AddDirEdge(0, 1);  // Lib_1 depends on Lib_2
  dg.AddDirEdge(0, 2);  // Lib_1 depends on Lib_3
  dg.AddDirEdge(2, 3);  // Lib_3 depends on Lib_4
  dg.AddDirEdge(3, 1);  // Lib_4 depends on Lib_2
  dg.AddDirEdge(0, 3);  // Lib_1 depends on Lib_4

  PackageManager packman(dg);

  packman.FindDownloadingOrder("Lib_1");
  packman.FindDownloadingOrder("Lib_2");
  packman.FindDownloadingOrder("Lib_3");
  packman.FindDownloadingOrder("Lib_4");
  packman.FindDownloadingOrder("Lib_5");

  return 0;
}
