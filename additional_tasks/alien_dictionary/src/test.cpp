#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <vector>

#include "utils.hpp"

// Helper function to capture the output of FindAlphabeticOrder
std::string CaptureOutput(const std::vector<std::string>& dictionary) {
  std::ostringstream output;
  std::streambuf* oldCoutBuffer =
      std::cout.rdbuf(output.rdbuf());  // Redirect cout to output stream

  FindAlphabeticOrder(dictionary);  // Call the function

  std::cout.rdbuf(oldCoutBuffer);  // Restore cout
  return output.str();
}

TEST(AlienDictionaryTests, SimpleTest) {
  std::vector<std::string> dictionary = {"hl", "ld", "wd", "dd"};
  std::string output = CaptureOutput(dictionary);
  ASSERT_EQ(output, "hlwd\n");  // Expected order
}

TEST(AlienDictionaryTests, BasicOrderTest) {
  std::vector<std::string> dictionary = {"baa", "abcd", "abca", "cab", "cad"};
  std::string output = CaptureOutput(dictionary);
  ASSERT_EQ(output, "bdac\n");  // Expected order
}

TEST(AlienDictionaryTests, NoOrderTest) {
  std::vector<std::string> dictionary = {"abc", "bca", "bac", "cab"};
  std::string output = CaptureOutput(dictionary);
  ASSERT_EQ(output,
            "The graph contains a cycle. Topological sorting is not "
            "determined.\n");  // Cycle detected
}

TEST(AlienDictionaryTests, SingleWordTest) {
  std::vector<std::string> dictionary = {"a"};
  std::string output = CaptureOutput(dictionary);
  ASSERT_EQ(output, "a\n");  // Only one character
}

TEST(AlienDictionaryTests, EmptyDictionaryTest) {
  std::vector<std::string> dictionary = {};
  std::string output = CaptureOutput(dictionary);
  ASSERT_EQ(output, "");  // No output for empty dictionary
}

TEST(AlienDictionaryTests, ComplexOrderTest) {
  // Updated dictionary to test a different order
  std::vector<std::string> dictionary = {"aaa", "abb", "bat", "bar",
                                         "cab", "cat", "tar", "rat"};

  // Updated expected output based on the new dictionary
  std::string output = CaptureOutput(dictionary);
  ASSERT_EQ(output, "abctr\n");  // Check for possible valid orders
}