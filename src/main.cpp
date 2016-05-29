#include <string>
#include <iostream>
#include <fstream>

#include "version.hpp"
#include "log.hpp"
#include "stopwatch.hpp"
#include "config.hpp"
#include "parser.hpp"
#include "statistics.hpp"
#include "output.hpp"

// TODO: Feature idea: support piping
// TODO: Feature idea: auto-detect log format
// TODO: Feature idea: various output formats (e.g. JSON, XML, etc.)

// TODO: Generate documentation with Doxygen?

using namespace std;
using namespace std::experimental;

int main(int argc, const char* argv[]) {
  try {
    log("Application version: ", major_version, ".", minor_version, ".", revision);

    configuration config = setup(argc, argv);

    switch(config.mode) {
      case version:
        cerr << "Version " << major_version << "." << minor_version << "." << revision << endl;
        break;
      case help:
        cerr << "Generates statistics on web server access log files." << endl << endl;
        cerr << "Usage: http-stats files [switches]" << endl << endl;
        cerr << "-help      Show information on how to use the application." << endl;
        cerr << "-version   Show application version information." << endl;
        break;
      default:
        statistics stats;
        stopwatch watch;

        watch.start();
        for(const string_view& filename : config.files) {
          log("Parsing ", filename, ".");

          ifstream file;
          file.exceptions(ios::badbit);
          file.open(filename.to_string());

          string line;
          while (getline(file, line)) {
            stats.add_parse_results(parse(line));
          }
        }
        watch.stop();
        log("Parsing finished. ", stats.count, " line", (stats.count != 1) ? "s" : "", " in ",
            config.files.size(), " file", (config.files.size() != 1) ? "s" : "", " parsed in ", watch, ".");

        output_console(stats);
        break;
    }
  }
  catch (const exception& e) {
    log("Exception: ", e.what());
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
