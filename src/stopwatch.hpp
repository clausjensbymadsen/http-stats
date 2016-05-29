#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <chrono>

class stopwatch {
private:
  std::chrono::high_resolution_clock::time_point start_time;
  std::chrono::high_resolution_clock::time_point stop_time;
public:
  void start() { start_time = std::chrono::high_resolution_clock::now(); };
  void stop() { stop_time = std::chrono::high_resolution_clock::now(); };
  long long span() const { return std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time).count(); };
};

// Add stopwatch integration to the logging system.
#ifdef LOG_HPP
template<typename... Ts>
void inline log(const stopwatch& watch, Ts... datalist) {
  //std::cerr << watch.span() << " ms";
  log(watch.span(), " ms", datalist...);
}
#endif

#endif