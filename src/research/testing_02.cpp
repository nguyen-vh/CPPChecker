// Source - https://stackoverflow.com/a/1488815
// Posted by luke, modified by community. See post 'Timeline' for change history
// Retrieved 2026-05-20, License - CC BY-SA 4.0

#include <algorithm>
#include <string>

std::string str;

str.erase(std::remove(str.begin(), str.end(), '\n'), str.cend());
