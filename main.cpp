#include <string>
#include <vector>

#include "daswahreschlagerfestmenudialog.h"

int main(int argc, char* argv[])
{
  return ribi::dws::MenuDialog().Execute(std::vector<std::string>(argv, argv + argc));
}
