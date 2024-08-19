#include <iostream>

int main() { 
  int *p = new int;
  *p = 0;
  std::cout << *p;
  return 0; 
}
