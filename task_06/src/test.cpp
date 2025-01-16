#include <gtest/gtest.h>
#include <LCA.h>

TEST(LCATest, Simple) {
    Node* root = new Node(20);
    root->left = new Node(8);
    root->right = new Node(22);
    root->left->left = new Node(4);
    root->left->right = new Node(12);
    root->left->right->left = new Node(10);
    root->left->right->right = new Node(14);

    int n1 = 10, n2 = 14;
    Node* t = LCA(root, n1, n2);
    ASSERT_EQ(t->data, 12);

    n1 = 8, n2 = 14;
    t = LCA(root, n1, n2);
    ASSERT_EQ(t->data, 8);

    n1 = 10, n2 = 22;
    t = LCA(root, n1, n2);
    ASSERT_EQ(t->data, 20);

}
