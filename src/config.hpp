#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <vector>
#include <experimental/string_view>

enum application_mode { normal, version, help };

// This structure contains the configuration of how the application is going to run.
struct configuration {
  application_mode mode = normal;
  std::vector<std::experimental::string_view> files;
};

configuration setup(int argc, const char* argv[]);

#endif