#include <algorithm>
#include <stdexcept>

#include "log.hpp"

#include "convert.hpp"

using namespace std;
using namespace std::experimental;

#include "parser.hpp"

int string_to_int(string_view string) {
  string_view::size_type index = 0;
  int result = 0;
  int sign = 1;

  if (string.size() > 9) throw runtime_error("Too big integer");

  // Check for sign
  if (string[index] == '-') {
    sign = -1;
    ++index;
  }

  // Read one digit at a time
  do {
    // Check if valid digit
    if ((string[index] < '0') || (string[index] > '9'))
      throw runtime_error("Invalid number");
    int digit = string[index] - '0';

    // Calculate the power of tens
    int tens = 1;
    for(string::size_type i = 0; i < (string.size() - index - 1); ++i) tens *= 10;

    result += digit * tens;
  } while (++index < string.size());

  return sign * result;
}