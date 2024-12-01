#include "merge_users.hpp"

int main() {
  std::vector<User> users = {
      User("user1", {"xxx@ya.ru", "foo@gmail.com", "lol@mail.ru"}),
      User("user2", {"foo@gmail.com", "ups@pisem.net"}),
      User("user3", {"xyz@pisem.net", "vasya@pupkin.com"}),
      User("user4", {"ups@pisem.net", "aaa@bbb.ru"}),
      User("user5", {"xyz@pisem.net"})};

  std::vector<User> merged_users = MergeUsers(users);

  // Print the merged users and their emails
  for (const auto& user : merged_users) std::cout << user << std::endl;

  return 0;
}