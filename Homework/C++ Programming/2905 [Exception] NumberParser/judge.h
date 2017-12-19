// MegaShow
#include <sstream>

class NumberParseException {};

bool isNumber(const char* str) {
  if (str == NULL || str[0] == 0 || ((str[0] == '-' || str[0] == '+') && str[1] == 0)) {
    return false;
  }
  for (int i = 0; str[i]; i++) {
    if (i == 0 && (str[0] == '-' || str[0] == '+')) {
      continue;
    }
    if (str[i] < '0' || str[i] > '9') {
      return false;
    }
  }
  return true;
}

int parseNumber(const char* str) {
  if (!isNumber(str)) {
    throw NumberParseException();
  }
  std::stringstream ss;
  ss << str;
  long long var;
  ss >> var;
  return static_cast<int>(var);
}
