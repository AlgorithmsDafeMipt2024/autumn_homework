#include <Lca.h>

#include <iostream>

int main() {
  Node* root = new Node(20);
  root->left = new Node(8);
  root->right = new Node(22);
  root->left->left = new Node(4);
  root->left->right = new Node(12);
  root->left->right->left = new Node(10);
  root->left->right->right = new Node(14);

  int n1 = 10, n2 = 14;
  Node* t = LCA(root, n1, n2);
  std::cout << n1 << " < " << t->data << " < " << n2 << std::endl;

  n1 = 14, n2 = 8;
  t = LCA(root, n1, n2);
  std::cout << n1 << " < " << t->data << " < " << n2 << std::endl;

  n1 = 10, n2 = 22;
  t = LCA(root, n1, n2);
  std::cout << n1 << " < " << t->data << " < " << n2 << std::endl;

  return 0;
}
