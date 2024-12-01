#include <gtest/gtest.h>

#include "merge_users.hpp"

// Test case to check merging of users with overlapping emails
TEST(MergeUsersTest, OverlappingEmails) {
  std::vector<User> users = {
      User("user1", {"email1@example.com", "email2@example.com"}),
      User("user2", {"email2@example.com", "email3@example.com"}),
      User("user3", {"email4@example.com"})};

  std::vector<User> except_merge = {
      User("user1",
           {"email1@example.com", "email2@example.com", "email3@example.com"}),
      User("user3", {"email4@example.com"})};

  std::vector<User> merged_users = MergeUsers(users);

  EXPECT_EQ(merged_users.size(), except_merge.size());
  for (size_t i = 0; i < merged_users.size(); ++i)
    EXPECT_EQ(merged_users[i], except_merge[i]);
}

// Test case to check merging of users with no overlapping emails
TEST(MergeUsersTest, NoOverlappingEmails) {
  std::vector<User> users = {User("user1", {"email1@example.com"}),
                             User("user2", {"email2@example.com"}),
                             User("user3", {"email3@example.com"})};

  std::vector<User> except_merge = users;

  std::vector<User> merged_users = MergeUsers(users);

  EXPECT_EQ(merged_users.size(), except_merge.size());
  for (size_t i = 0; i < merged_users.size(); ++i)
    EXPECT_EQ(merged_users[i], except_merge[i]);
}

// Test case to check merging of users with multiple names and emails
TEST(MergeUsersTest, MultipleNamesAndEmails) {
  std::vector<User> users = {
      User("user1", {"email1@example.com"}),
      User("user2", {"email1@example.com", "email2@example.com"}),
      User("user3", {"email3@example.com"})};

  std::vector<User> except_merge = {
      User("user1", {"email1@example.com", "email2@example.com"}),
      User("user3", {"email3@example.com"})};

  std::vector<User> merged_users = MergeUsers(users);

  EXPECT_EQ(merged_users.size(), except_merge.size());
  for (size_t i = 0; i < merged_users.size(); ++i)
    EXPECT_EQ(merged_users[i], except_merge[i]);
}

// Test case to check merging when there are no users
TEST(MergeUsersTest, NoUsers) {
  std::vector<User> users = {};

  std::vector<User> except_merge = {};

  std::vector<User> merged_users = MergeUsers(users);

  EXPECT_EQ(merged_users.size(), except_merge.size());
  for (size_t i = 0; i < merged_users.size(); ++i)
    EXPECT_EQ(merged_users[i], except_merge[i]);
}

// Test case to check merging of users with multiple overlapping emails and
// names
TEST(MergeUsersTest, ComplexOverlappingNamesAndEmails) {
  std::vector<User> users = {
      User("user1", {"common@example.com", "unique1@example.com"}),
      User("user2", {"common@example.com", "unique2@example.com"}),
      User("user3", {"unique3@example.com"}),
      User("user4", {"common@example.com", "unique4@example.com"}),
      User("user5", {"unique1@example.com"})};

  std::vector<User> except_merge = {
      User("user1", {"common@example.com", "unique1@example.com",
                     "unique2@example.com", "unique4@example.com"}),
      User("user3", {"unique3@example.com"})};

  std::vector<User> merged_users = MergeUsers(users);

  EXPECT_EQ(merged_users.size(), except_merge.size());
  for (size_t i = 0; i < merged_users.size(); ++i)
    EXPECT_EQ(merged_users[i], except_merge[i]);
}

// Test case to check merging with users having nested relationships
TEST(MergeUsersTest, NestedRelationships) {
  std::vector<User> users = {
      User("alice", {"alice@example.com", "bob@example.com"}),
      User("bob", {"bob@example.com", "charlie@example.com"}),
      User("charlie", {"charlie@example.com", "dave@example.com"}),
      User("dave", {"dave@example.com"}), User("eve", {"eve@example.com"})};

  std::vector<User> except_merge = {
      User("alice", {"alice@example.com", "bob@example.com",
                     "charlie@example.com", "dave@example.com"}),
      User("eve", {"eve@example.com"})};

  std::vector<User> merged_users = MergeUsers(users);

  EXPECT_EQ(merged_users.size(), except_merge.size());
  for (size_t i = 0; i < merged_users.size(); ++i)
    EXPECT_EQ(merged_users[i], except_merge[i]);
}

// Test case to check merging when users have circular references
TEST(MergeUsersTest, CircularReferences) {
  std::vector<User> users = {
      User("userA", {"emailA@example.com", "emailB@example.com"}),
      User("userB", {"emailB@example.com", "emailC@example.com"}),
      User("userC", {"emailC@example.com", "emailA@example.com"})};

  std::vector<User> except_merge = {
      User("userA",
           {"emailA@example.com", "emailB@example.com", "emailC@example.com"})};

  std::vector<User> merged_users = MergeUsers(users);

  EXPECT_EQ(merged_users.size(), except_merge.size());
  for (size_t i = 0; i < merged_users.size(); ++i)
    EXPECT_EQ(merged_users[i], except_merge[i]);
}

// Test case to check merging when users have different names but share all
// emails
TEST(MergeUsersTest, DifferentNamesSameEmails) {
  std::vector<User> users = {User("user1", {"shared@example.com"}),
                             User("user2", {"shared@example.com"}),
                             User("user3", {"shared@example.com"})};

  std::vector<User> except_merge = {User("user1", {"shared@example.com"})};

  std::vector<User> merged_users = MergeUsers(users);

  EXPECT_EQ(merged_users.size(), except_merge.size());
  for (size_t i = 0; i < merged_users.size(); ++i)
    EXPECT_EQ(merged_users[i], except_merge[i]);
}
