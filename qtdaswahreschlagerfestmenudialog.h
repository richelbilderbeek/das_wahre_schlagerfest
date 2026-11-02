//---------------------------------------------------------------------------
/*
Das Wahre Schlagerfest, a simple game
Copyright (C) 2003-2016 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/GameDasWahreSchlagerfest.htm
//---------------------------------------------------------------------------
#ifndef QTDASWAHRESCHLAGERFESTMENUDIALOG_H
#define QTDASWAHRESCHLAGERFESTMENUDIALOG_H



#include <QDialog>

class QTimer;


namespace Ui {
  class QtDwsMenuDialog;
}

namespace ribi {
namespace dws {

class QtMenuDialog : public QDialog
{
  Q_OBJECT
    
public:
  explicit QtMenuDialog(QWidget *parent = nullptr);
  QtMenuDialog(const QtMenuDialog&) = delete;
  QtMenuDialog& operator=(const QtMenuDialog&) = delete;
  ~QtMenuDialog();

  ///Show the menu, in the way that suits the platform
  void ShowMenu();
    
private slots:
  void on_button_start_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked();

protected:
  void keyPressEvent(QKeyEvent *) override;

private slots:
  void OnJoystickCheck();

private:
  Ui::QtDwsMenuDialog *ui;

  QTimer * const m_timer_joystick;
};

} //~namespace dws
} //~namespace ribi

#endif // QTDASWAHRESCHLAGERFESTMENUDIALOG_H
