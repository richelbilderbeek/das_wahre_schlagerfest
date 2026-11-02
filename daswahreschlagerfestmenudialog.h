#ifndef DASWAHRESCHLAGERFESTMENUDIALOG_H
#define DASWAHRESCHLAGERFESTMENUDIALOG_H

#include <string>
#include <vector>

namespace ribi {
namespace dws {

///The command-line interface, and the information about this program
struct MenuDialog
{
  ///Run the command-line interface, returns the exit code
  int Execute(const std::vector<std::string>& args) const;

  ///The text shown in the 'About' screen
  std::string GetAbout() const;

  ///The text shown as command-line help
  std::string GetHelp() const;

  std::string GetVersion() const;
  std::vector<std::string> GetVersionHistory() const;
};

} //~namespace dws
} //~namespace ribi

#endif // DASWAHRESCHLAGERFESTMENUDIALOG_H
