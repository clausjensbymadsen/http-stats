#include "gtest/gtest.h"

#include "../src/parser.cpp"

using namespace std;
using namespace std::experimental;

TEST(parser, skip_whitespace_basic) {
  const string_view subject("    123");
  const string_view::size_type expected_index = 4;

  string_view::size_type index = 0;

  ASSERT_NO_THROW(skip_whitespace(subject, index));
  ASSERT_EQ(expected_index, index);
}

TEST(parser, skip_whitespace_no_whitespace) {
  const string_view subject("def");
  const string_view::size_type expected_index = 0;

  string_view::size_type index = 0;

  ASSERT_NO_THROW(skip_whitespace(subject, index));
  ASSERT_EQ(expected_index, index);
}

TEST(parser, is_whitespace) {
  ASSERT_TRUE(is_whitespace(' '));
  ASSERT_TRUE(is_whitespace('\t'));
  ASSERT_FALSE(is_whitespace('h'));
  ASSERT_FALSE(is_whitespace('.'));
  ASSERT_FALSE(is_whitespace('['));
  ASSERT_FALSE(is_whitespace('-'));
  ASSERT_FALSE(is_whitespace(':'));
}

TEST(parser, parse_token_basic) {
  const string_view subject("abcd   ");
  const string_view expected("abcd");

  string_view::size_type index = 0;
  string_view target;

  ASSERT_NO_THROW(target = parse_token(subject, index));
  ASSERT_EQ(expected, target);
  ASSERT_EQ(expected.size(), index);
}

TEST(parser, parse_token_leading_nonzero_index) {
  const string_view subject("   123  ");
  const string_view expected("123");
  const string_view::size_type initial_index = 3;

  string_view::size_type index = initial_index;
  string_view target;

  ASSERT_NO_THROW(target = parse_token(subject, index));
  ASSERT_EQ(expected, target);
  ASSERT_EQ(initial_index + expected.size(), index);
}

TEST(parser, parse_token_leading_no_trailing_whitespace) {
  const string_view subject("   def");
  const string_view expected("def");
  const string_view::size_type initial_index = 3;

  string_view::size_type index = initial_index;
  string_view target;

  ASSERT_NO_THROW(target = parse_token(subject, index));
  ASSERT_EQ(expected, target);
  ASSERT_EQ(initial_index + expected.size(), index);
}

TEST(parser, parse_token_only_whitespace) {
  const string_view subject("       ");
  const string_view expected("");

  string_view::size_type index = 0;
  string_view target;

  ASSERT_NO_THROW(target = parse_token(subject, index));
  ASSERT_EQ(expected, target);
  ASSERT_EQ(expected.size(), index);
}

TEST(parser, parse_token_no_whitespace) {
  const string_view subject("123");
  const string_view expected(subject);

  string_view::size_type index = 0;
  string_view target;

  ASSERT_NO_THROW(target = parse_token(subject, index));
  ASSERT_EQ(expected, target);
  ASSERT_EQ(expected.size(), index);
}

TEST(parser, parse_string_basic) {
  const string_view subject("[abc]def");
  const string_view expected("abc");

  string_view::size_type index = 0;
  string_view target;

  ASSERT_NO_THROW(target = parse_string(subject, index, '[', ']'));
  ASSERT_EQ(expected, target);
  ASSERT_EQ(expected.size() + 2, index);
}

TEST(parser, parse_string_basic2) {
  const string_view subject("123@asdf@def");
  const string_view expected("asdf");
  const string_view::size_type initial_index = 3;

  string_view::size_type index = initial_index;
  string_view target;

  ASSERT_NO_THROW(target = parse_string(subject, index, '@'));
  ASSERT_EQ(expected, target);
  ASSERT_EQ(initial_index + expected.size() + 2, index);
}

TEST(parser, parse_string_start_delimiter) {
  const string_view subject("<abc]def");

  string_view::size_type index = 0;

  ASSERT_THROW(parse_string(subject, index, '[', ']'), runtime_error);
}

TEST(parser, parse_string_end_delimiter) {
  const string_view subject("[abc>def");

  string_view::size_type index = 0;

  ASSERT_THROW(parse_string(subject, index, '[', ']'), runtime_error);
}

TEST(parser, parse_string_escape_char) {
  const string_view subject("\"abc\\\"def\"");
  const string_view expected("abc\\\"def");

  string_view::size_type index = 0;
  string_view target;

  ASSERT_NO_THROW(target = parse_string(subject, index));
  ASSERT_EQ(expected, target);
  ASSERT_EQ(expected.size() + 2, index);
}
