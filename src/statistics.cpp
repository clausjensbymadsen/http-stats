#include "statistics.hpp"

using namespace std;

void statistics::add_parse_results(const parse_results& results) {
  ++count;

  if (results.request.size() > 0) {
    string request = results.request.to_string();
    if (request_distribution.find(request) != request_distribution.end())
      ++request_distribution[request];
    else
      request_distribution[request] = 1;
  }

  if (results.status != 0) {
    if (status_distribution.find(results.status) != status_distribution.end())
      ++status_distribution[results.status];
    else
      status_distribution[results.status] = 1;
  }
}