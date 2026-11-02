#include "daswahreschlagerfestmenudialog.h"

#include <iostream>
#include <sstream>

#include "daswahreschlagerfestterminal.h"
#include "daswahreschlagerfestwidget.h"

int ribi::dws::MenuDialog::Execute(const std::vector<std::string>& args) const
{
  const int argc = static_cast<int>(args.size());
  if (argc != 2)
  {
    std::cout << GetHelp() << '\n';
    return argc == 1 ? 0 : 1;
  }
  const std::string& arg = args[1];
  if (arg == "-h" || arg == "--help")
  {
    std::cout << GetHelp() << '\n';
    return 0;
  }
  if (arg == "-v" || arg == "--version")
  {
    std::cout << GetVersion() << '\n';
    return 0;
  }
  const bool is_demo = arg == "-d" || arg == "--demo";
  const bool is_play = arg == "-p" || arg == "--play";
  if (!is_demo && !is_play)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  Terminal terminal;
  terminal.SetAutoPlay(is_demo);
  Widget w(&terminal);
  terminal.Execute(w);
  return 0;
}

std::string ribi::dws::MenuDialog::GetAbout() const
{
  std::stringstream s;
  s << "Das Wahre Schlagerfest, a truely fun game\n"
    << "Version " << GetVersion() << "\n"
    << "Copyright 2003-2026 Richel Bilderbeek\n"
    << "https://richelbilderbeek.github.io/das_wahre_schlagerfest/\n"
    << "Licensed under the GNU General Public License, version 3 or later";
  return s.str();
}

std::string ribi::dws::MenuDialog::GetHelp() const
{
  return
    "Das Wahre Schlagerfest, a truely fun game\n"
    "\n"
    "Options:\n"
    "  -d, --demo     See a demo\n"
    "  -h, --help     Show this help\n"
    "  -p, --play     Play the game\n"
    "  -v, --version  Show the version";
}

std::string ribi::dws::MenuDialog::GetVersion() const
{
  return "5.0";
}

std::vector<std::string> ribi::dws::MenuDialog::GetVersionHistory() const
{
  return {
    "2003-09-30: version 1.1: first VCL (Windows-only) version",
    "2012-07-21: version 2.0: ported to Qt (cross-platform)",
    "2012-07-29: version 2.1: changed graphics to old-school",
    "2012-08-09: version 2.2: changed graphics, changed new tile selection (rendering the eat-it all tile) obsolete",
    "2014-01-30: version 2.3: added command-line demo and play mode",
    "2014-01-31: version 2.4: added terminal-like mode from command-line",
    "2014-02-10: version 2.5: added terminal-like mode in desktop version",
    "2015-08-28: version 3.0: removed terminal-like mode in desktop version, ported to NDS",
    "2015-11-15: version 4.0: moved to own GitHub",
    "2015-11-28: version 4.1: added joystick support",
    "2026-11-02: version 5.0: ported to Qt6, added WebAssembly version, added game over"
  };
}
