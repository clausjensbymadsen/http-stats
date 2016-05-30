#include <cassert>
#include <algorithm>
#include <stdexcept>
#include <sstream>

#include "convert.hpp"
#include "log.hpp"

#include "parser.hpp"

using namespace std;
using namespace std::experimental;

const char whitespace[] = { ' ', '\t' };

bool eol(string_view line, string_view::size_type index) {
  return index >= line.size();
}

bool is_whitespace(char ch) {
  return find(begin(whitespace), end(whitespace), ch) != end(whitespace);
}

void skip_whitespace(string_view line, string_view::size_type& index) {
  while ((!eol(line, index)) && (is_whitespace(line.at(index)))) {
    ++index;
  }
}

string_view parse_token(string_view line, string_view::size_type& index) {
  auto initial_index = index;

  while ((!eol(line, index)) && (!is_whitespace(line.at(index)))) {
    ++index;
  }

  return string_view(&line[initial_index], index - initial_index);
}

string_view parse_string(string_view line, string_view::size_type& index, char start_delimiter, char end_delimiter) {
  string_view result;
  string_view::size_type initial_index;

  if (line.at(index) != start_delimiter) throw runtime_error("Wrong starting delimiter");
  ++index;
  initial_index = index;
  while (true) {
    if (eol(line, index)) break;
    if ((index > 0) && (line[index] == end_delimiter) && (line[index - 1] != '\\')) break;

    ++index;
  }
  if (eol(line, index)) throw runtime_error("Wrong ending delimiter");
  assert(line.at(index) == end_delimiter);
  ++index;

  return string_view(&line[initial_index], index - initial_index - 1);
}

string_view inline parse_string(string_view line, string_view::size_type& index, char delimiter) {
  return parse_string(line, index, delimiter, delimiter);
}

string_view inline parse_string(string_view line, string_view::size_type& index) {
  return parse_string(line, index, '\"');
}

parse_results parse(string_view line) {
  static const string_view not_applicable("-");

  parse_results results;

  try {
    string_view string;
    string_view::size_type index = 0;

    skip_whitespace(line, index);
    string = parse_token(line, index);
    if (string != not_applicable)
      results.remote_host = string;

    skip_whitespace(line, index);
    string = parse_token(line, index);
    if (string != not_applicable)
      results.identity = string;

    skip_whitespace(line, index);
    string = parse_token(line, index);
    if (string != not_applicable)
      results.user_name = string;

    skip_whitespace(line, index);
    string = parse_string(line, index, '[', ']');
    if (string != not_applicable)
      results.time = string;

    skip_whitespace(line, index);
    string = parse_string(line, index);
    if (string != not_applicable)
      results.request = string;

    skip_whitespace(line, index);
    string = parse_token(line, index);
    if (string != not_applicable)
      results.status = string_to_int(string);

    skip_whitespace(line, index);
    string = parse_token(line, index);
    if (string != not_applicable)
      results.response_size = string_to_int(string);

    skip_whitespace(line, index);
    string = parse_token(line, index);
    if (string != not_applicable)
      results.referer = string;

    skip_whitespace(line, index);
    string = parse_token(line, index);
    if (string != not_applicable)
      results.user_agent = string;
  }
  catch (const exception& e) {
    log("Failed to parse line: ", line);
    throw;
  }

  return results;
}
