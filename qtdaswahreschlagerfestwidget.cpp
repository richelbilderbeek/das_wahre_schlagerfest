#include "qtdaswahreschlagerfestwidget.h"

#include <algorithm>
#include <cassert>

#include <QCloseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>

#ifdef USE_SFML_FOR_JOYSTICK_SUPPORT
#include <SFML/Window/Joystick.hpp>
#endif // USE_SFML_FOR_JOYSTICK_SUPPORT

ribi::dws::QtDwsWidget::QtDwsWidget(QWidget *parent)
  : QWidget(parent),
    m_beer(":/images/DasWahreSchlagerfestBeer.png"),
    m_bratwurst(":/images/DasWahreSchlagerfestBratwurst.png"),
    m_empty(":/images/DasWahreSchlagerfestSmiley.png"),
    m_game(this),
    m_timer_joystick{new QTimer(this)}
{
  assert(m_beer.width() == 102);
  assert(m_bratwurst.width() == 102);
  assert(m_empty.width() == 102);

  setFocusPolicy(Qt::StrongFocus);
  setWindowTitle("Das Wahre Schlagerfest");

  #ifdef USE_SFML_FOR_JOYSTICK_SUPPORT
  //Timer for checking the joystick input
  QObject::connect(m_timer_joystick,SIGNAL(timeout()),this,SLOT(OnJoystickCheck()));
  m_timer_joystick->setInterval(100);
  m_timer_joystick->start();
  #endif // USE_SFML_FOR_JOYSTICK_SUPPORT
}

void ribi::dws::QtDwsWidget::closeEvent(QCloseEvent * e)
{
  emit closed();
  QWidget::closeEvent(e);
}

void ribi::dws::QtDwsWidget::DoDisplay(const Widget& /* widget */)
{
  update();
}

const QPixmap& ribi::dws::QtDwsWidget::GetPixmap(const Tile& tile) const noexcept
{
  switch (tile)
  {
    case Tile::beer     : return m_beer;
    case Tile::bratwurst: return m_bratwurst;
    default: break;
  }
  assert(tile == Tile::empty);
  return m_empty;
}

void ribi::dws::QtDwsWidget::keyPressEvent(QKeyEvent * e)
{
  switch (e->key())
  {
    case Qt::Key_Right:  Press(Key::right); return;
    case Qt::Key_Down:   Press(Key::down); return;
    case Qt::Key_Left:   Press(Key::left); return;
    case Qt::Key_Escape: Press(Key::quit); return;
    default: break;
  }
  //When the game is over, any other key returns to the menu,
  //so that a player still holding an arrow key sees the game is over
  if (m_game.IsGameOver()) close();
}

void ribi::dws::QtDwsWidget::OnChanged(const Widget& /* widget */)
{
  update();
}

void ribi::dws::QtDwsWidget::OnJoystickCheck()
{
  #ifdef USE_SFML_FOR_JOYSTICK_SUPPORT
  sf::Joystick::update();
  const int joystick_index{0};
  if (sf::Joystick::isConnected(joystick_index))
  {
    if (sf::Joystick::hasAxis(joystick_index, sf::Joystick::X))
    {
      const double dx{sf::Joystick::getAxisPosition(joystick_index, sf::Joystick::X)};
      if (dx < -50.0) { Press(Key::left); }
      if (dx >  50.0) { Press(Key::right); }
    }
    if (sf::Joystick::hasAxis(joystick_index, sf::Joystick::Y))
    {
      const double dy{sf::Joystick::getAxisPosition(joystick_index, sf::Joystick::Y)};
      if (dy > 50.0) { Press(Key::down); }
    }
    if (sf::Joystick::isButtonPressed(joystick_index,0)) {
      close();
    }
  }
  #endif // USE_SFML_FOR_JOYSTICK_SUPPORT
}

void ribi::dws::QtDwsWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.fillRect(rect(),Qt::black);
  painter.setRenderHint(QPainter::SmoothPixmapTransform);

  //Fit the board in the window, as the WebAssembly version
  //has as much room as the web page gives it
  const std::vector<std::vector<Tile>>& v = m_game.GetTiles();
  const int rows = static_cast<int>(v.size());
  const int cols = static_cast<int>(v[0].size());
  const int tile_size = m_beer.width();
  const double scale = std::min(
    static_cast<double>(width()) / (cols * tile_size),
    static_cast<double>(height()) / (rows * tile_size)
  );
  painter.translate(
    (width() - (cols * tile_size * scale)) / 2.0,
    (height() - (rows * tile_size * scale)) / 2.0
  );
  painter.scale(scale,scale);

  for (int y=0; y!=rows; ++y)
  {
    for (int x=0; x!=cols; ++x)
    {
      painter.drawPixmap(x * tile_size, y * tile_size, GetPixmap(v[y][x]));
    }
  }

  const QRect board(0, 0, cols * tile_size, rows * tile_size);
  if (m_game.IsGameOver())
  {
    painter.fillRect(board,QColor(0,0,0,160));
    QFont font = painter.font();
    font.setPixelSize(tile_size);
    font.setBold(true);
    painter.setFont(font);
    painter.setPen(Qt::yellow);
    painter.drawText(board,Qt::AlignCenter,"Game over");
    return;
  }
  const Cursor& cursor = m_game.GetCursor();
  painter.drawPixmap(cursor.x * tile_size, cursor.y * tile_size, GetPixmap(cursor.tile));
}

void ribi::dws::QtDwsWidget::Press(const Key key)
{
  if (key == Key::quit)
  {
    close();
    return;
  }
  m_game.PressKey(key);
}

QSize ribi::dws::QtDwsWidget::sizeHint() const
{
  const std::vector<std::vector<Tile>>& v = m_game.GetTiles();
  return QSize(
    static_cast<int>(v[0].size()) * m_beer.width(),
    static_cast<int>(v.size()) * m_beer.height()
  );
}
