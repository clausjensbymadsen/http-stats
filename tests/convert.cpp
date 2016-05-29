#include "gtest/gtest.h"

#include "../src/convert.cpp"

using namespace std;
using namespace std::experimental;

TEST(convert, string_to_int_basic) {
  const string_view subject("3521");
  const int expected = 3521;

  int target;

  ASSERT_NO_THROW(target = string_to_int(subject));
  ASSERT_EQ(expected, target);
}

TEST(convert, string_to_int_basic2) {
  const string_view subject("8269");
  const int expected = 8269;

  int target;

  ASSERT_NO_THROW(target = string_to_int(subject));
  ASSERT_EQ(expected, target);
}

TEST(convert, string_to_int_BAD_INPUT) {
  const string_view subject("34k7");

  ASSERT_THROW(string_to_int(subject), runtime_error);
}

TEST(convert, string_to_int_too_big) {
  const string_view subject("12345678901234567890");

  ASSERT_THROW(string_to_int(subject), runtime_error);
}

TEST(convert, string_to_int_zero) {
  const string_view subject("0");
  const int expected = 0;

  int target;

  ASSERT_NO_THROW(target = string_to_int(subject));
  ASSERT_EQ(expected, target);
}

TEST(convert, string_to_int_negative_number) {
  const string_view subject("-4824");
  const int expected = -4824;

  int target;

  ASSERT_NO_THROW(target = string_to_int(subject));
  ASSERT_EQ(expected, target);
}
