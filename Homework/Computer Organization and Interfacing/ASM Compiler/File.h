#ifndef __FILE_H__
#define __FILE_H__

#include <string>

using namespace std;

class File final {
  public:
    static bool Write(const string& path, const string& text);
    static string Read(const string& path);

  private:
    File();
};

#endif // __FILE_H__
