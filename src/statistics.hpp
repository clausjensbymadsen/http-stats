#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP

#include <string>
#include <map>
#include <stdexcept>

#include "parser.hpp"

// This structure stores statistics based on the parsed data.
struct statistics {
  int count = 0;
  std::map<std::string, int> request_distribution;
  std::map<int, int> status_distribution;

  void add_parse_results(const parse_results& results);
};

#endif