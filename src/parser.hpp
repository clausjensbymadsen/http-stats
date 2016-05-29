#ifndef PARSER_HPP
#define PARSER_HPP

#include <experimental/string_view>

// This structure contains a rough parsing of a line of data.
struct parse_results {
  std::experimental::string_view remote_host;
  std::experimental::string_view identity;
  std::experimental::string_view user_name;
  std::experimental::string_view time;
  std::experimental::string_view request;
  int status;
  int response_size;
  std::experimental::string_view referer;
  std::experimental::string_view user_agent;
};

parse_results parse(std::experimental::string_view line);

#endif