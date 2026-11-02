#include <QApplication>
#include "qtdaswahreschlagerfestmenudialog.h"


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Q_INIT_RESOURCE(DasWahreSchlagerfest);
  ribi::dws::QtMenuDialog w;
  w.ShowMenu();
  return a.exec();
}
