#include "daswahreschlagerfestwidget.h"

#include <boost/test/unit_test.hpp>

#include "daswahreschlagerfestdisplay.h"

using namespace ribi::dws;

namespace {

struct TestDisplay : public Display
{
  void DoDisplay(const Widget&) override {}
  void OnChanged(const Widget&) override {}
};

} //~namespace

BOOST_AUTO_TEST_CASE(dws_widget_cursor_moves)
{
  TestDisplay display;
  Widget w(&display);
  BOOST_CHECK_EQUAL(w.GetCursor().x, 4);
  w.PressKey(Key::left);
  BOOST_CHECK_EQUAL(w.GetCursor().x, 3);
  w.PressKey(Key::right);
  BOOST_CHECK_EQUAL(w.GetCursor().x, 4);
  w.PressKey(Key::down);
  BOOST_CHECK_EQUAL(w.GetCursor().y, 1);
}

BOOST_AUTO_TEST_CASE(dws_widget_game_over_on_full_board)
{
  //Three in a row is impossible on this board,
  //so it fills up after two tiles in the bottom row
  TestDisplay display;
  Widget w(&display, 2, 2);
  BOOST_CHECK(!w.IsGameOver());
  w.PressKey(Key::down);
  w.PressKey(Key::down);
  BOOST_CHECK(!w.IsGameOver());
  w.PressKey(Key::down);
  w.PressKey(Key::down);
  BOOST_CHECK(w.IsGameOver());
}

BOOST_AUTO_TEST_CASE(dws_widget_ignores_keys_after_game_over)
{
  TestDisplay display;
  Widget w(&display, 2, 2);
  for (int i = 0; i != 4; ++i) w.PressKey(Key::down);
  const int x = w.GetCursor().x;
  w.PressKey(Key::left);
  w.PressKey(Key::right);
  BOOST_CHECK_EQUAL(w.GetCursor().x, x);
}
