#include <cassert>

#include "config.hpp"

using namespace std;
using namespace std::experimental;

configuration setup(int argc, const char* argv[]) {
  configuration result;

  if (argc > 1) {
    for (int index = 1; index < argc; ++index) {
      string_view argument = string_view(argv[index]);
      assert(argument.size() > 0);

      // Switches starts with a dash. If no leading dash, assume it's a file name.
      if (argument[0] != '-')
        result.files.push_back(argument);
      else {
        if (argument == "-version")
          result.mode = version;
        if (argument == "-help")
          result.mode = help;
      }
    }
  }

  // Default file name if no file names are specified.
  if (result.files.size() == 0) result.files.push_back("access2.log");

  return result;
}