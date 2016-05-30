#ifndef PARSER_HPP
#define PARSER_HPP

#include <experimental/string_view>

enum request_method { get, post, unknown };

// This structure contains a rough parsing of a line of data.
struct parse_results {
  std::experimental::string_view remote_host;
  std::experimental::string_view identity;
  std::experimental::string_view user_name;
  std::experimental::string_view time;
  request_method method;
  std::experimental::string_view request;
  std::experimental::string_view protocol;
  int status;
  int response_size;
  std::experimental::string_view referer;
  std::experimental::string_view user_agent;
};

parse_results parse(std::experimental::string_view line);

#endif