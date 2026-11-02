#include <cstdlib>
#include <ctime>

#include <QApplication>
#include "qtdaswahreschlagerfestmenudialog.h"


int main(int argc, char *argv[])
{
  //Each game has different tiles
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  QApplication a(argc, argv);
  Q_INIT_RESOURCE(DasWahreSchlagerfest);
  ribi::dws::QtMenuDialog w;
  w.ShowMenu();
  return a.exec();
}
