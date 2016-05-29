#include "output.hpp"

#include <iostream>

using namespace std;

void output_console(const statistics& stats) {
  cout << "Requests: " << stats.count << endl;

  cout << "Status code distribution:" << endl;
  for(const auto& entry : stats.status_distribution) {
    cout << "  " << entry.first << ": " << entry.second << " ("
    << int(entry.second * 1000.0f / stats.count) / 10.0f << "%)" << endl;
  }

  cout << "Request distribution:" << endl;
  for(const auto& entry : stats.request_distribution) {
    cout << "  " << entry.first << ": " << entry.second << " ("
    << int(entry.second * 1000.0f / stats.count) / 10.0f << "%)" << endl;
  }
}
