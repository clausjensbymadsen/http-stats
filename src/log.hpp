#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <experimental/string_view>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void inline log() {
  #ifndef NDEBUG
    std::clog << std::endl;
  #endif
}

template<typename... Ts>
void inline log(const std::experimental::string_view& data, Ts... datalist) {
  for(char ch : data) {
    std::clog << ch;
  }
  log(datalist...);
}

template<typename T, typename... Ts>
void inline log(T data, Ts... datalist) {
  #ifndef NDEBUG
    std::clog << data;
    log(datalist...);
  #endif
}

#pragma GCC diagnostic pop

#endif