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
#ifndef QTDASWAHRESCHLAGERFESTWIDGET_H
#define QTDASWAHRESCHLAGERFESTWIDGET_H



#include <QPixmap>
#include <QWidget>
#include "daswahreschlagerfestdisplay.h"
#include "daswahreschlagerfesttile.h"
#include "daswahreschlagerfestwidget.h"

class QTimer;

namespace ribi {
namespace dws {

///The game on screen. Responds to events, instead of waiting for keys
///in a loop, as a loop would block the web browser in the WebAssembly version
class QtDwsWidget : public QWidget, public ribi::dws::Display
{
  Q_OBJECT

public:
  explicit QtDwsWidget(QWidget *parent = nullptr);
  QtDwsWidget(const QtDwsWidget&) = delete;
  QtDwsWidget& operator=(const QtDwsWidget&) = delete;

  void DoDisplay(const Widget& widget) override;
  void OnChanged(const Widget& widget) override;

  ///The size at which the tiles are shown at their original size
  QSize sizeHint() const override;

signals:
  ///The window is closing: the game has ended or the user quit
  void closed();

protected:
  void closeEvent(QCloseEvent *) override;
  void keyPressEvent(QKeyEvent *) override;
  void paintEvent(QPaintEvent *) override;

private slots:
  void OnJoystickCheck();

private:
  const QPixmap m_beer;
  const QPixmap m_bratwurst;
  const QPixmap m_empty;

  ///The game logic
  Widget m_game;

  QTimer * const m_timer_joystick;

  ///Obtain the pixmap for this tile
  const QPixmap& GetPixmap(const Tile& tile) const noexcept;

  ///Respond to a key, either from a keyboard or a joystick
  void Press(const Key key);
};

} //~namespace dws
} //~namespace ribi


#endif // QTDASWAHRESCHLAGERFESTWIDGET_H
