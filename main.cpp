#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

#include "daswahreschlagerfestmenudialog.h"

int main(int argc, char* argv[])
{
  //Each game has different tiles
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  return ribi::dws::MenuDialog().Execute(std::vector<std::string>(argv, argv + argc));
}
