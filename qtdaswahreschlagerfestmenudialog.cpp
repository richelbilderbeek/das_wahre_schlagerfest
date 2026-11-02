#include "qtdaswahreschlagerfestmenudialog.h"

#include <QKeyEvent>
#include <QMessageBox>
#include <QScreen>
#include <QTimer>

#ifdef USE_SFML_FOR_JOYSTICK_SUPPORT
#include <SFML/Window/Joystick.hpp>
#endif //USE_SFML_FOR_JOYSTICK_SUPPORT

#include "daswahreschlagerfestmenudialog.h"
#include "qtdaswahreschlagerfestwidget.h"
#include "ui_qtdaswahreschlagerfestmenudialog.h"

ribi::dws::QtMenuDialog::QtMenuDialog(QWidget *parent)
  : QDialog(parent),
    ui(new Ui::QtDwsMenuDialog),
    m_timer_joystick{new QTimer(this)}
{
  ui->setupUi(this);

  #ifdef Q_OS_WASM
  //A web page cannot be quit
  ui->button_quit->hide();
  #endif // Q_OS_WASM

  #ifdef USE_SFML_FOR_JOYSTICK_SUPPORT
  //Timer for checking the joystick input
  QObject::connect(m_timer_joystick,SIGNAL(timeout()),this,SLOT(OnJoystickCheck()));
  m_timer_joystick->setInterval(100);
  m_timer_joystick->start();
  #endif // USE_SFML_FOR_JOYSTICK_SUPPORT
}

ribi::dws::QtMenuDialog::~QtMenuDialog()
{
  delete ui;
}

void ribi::dws::QtMenuDialog::keyPressEvent(QKeyEvent * e)
{
  if (e->key() == Qt::Key_Escape)
  {
    #ifndef Q_OS_WASM
    close();
    #endif // Q_OS_WASM
    return;
  }
  QDialog::keyPressEvent(e);
}

void ribi::dws::QtMenuDialog::on_button_start_clicked()
{
  //Not modal and without exec(), as that blocks the WebAssembly version
  QtDwsWidget * const d = new QtDwsWidget;
  d->setAttribute(Qt::WA_DeleteOnClose);
  QObject::connect(d,&QtDwsWidget::closed,this,[this]()
    {
      ShowMenu();
    }
  );
  hide();
  #ifdef Q_OS_WASM
  d->showFullScreen();
  #else
  d->resize(d->sizeHint());
  d->move(screen()->availableGeometry().center() - d->rect().center());
  d->show();
  #endif // Q_OS_WASM
  d->setFocus();
}

void ribi::dws::QtMenuDialog::ShowMenu()
{
  #ifdef Q_OS_WASM
  showFullScreen();
  #else
  show();
  #endif // Q_OS_WASM
  ui->button_start->setFocus();
}

void ribi::dws::QtMenuDialog::on_button_about_clicked()
{
  //open instead of exec, as exec blocks the WebAssembly version
  QMessageBox * const d = new QMessageBox(this);
  d->setAttribute(Qt::WA_DeleteOnClose);
  d->setWindowTitle("About");
  d->setText(QString::fromStdString(MenuDialog().GetAbout()));
  //Do not inherit the large font of the menu buttons
  d->setStyleSheet(
    "QLabel { color: black; }"
    "QPushButton, QPushButton:focus {"
    "  font: 16px; color: black; background-color: white;"
    "  border: 1px solid black; padding: 4px 16px;"
    "}"
  );
  d->open();
}

void ribi::dws::QtMenuDialog::OnJoystickCheck()
{
  #ifdef USE_SFML_FOR_JOYSTICK_SUPPORT
  sf::Joystick::update();
  const int joystick_index{0};
  if (sf::Joystick::isConnected(joystick_index))
  {
    if (sf::Joystick::hasAxis(joystick_index, sf::Joystick::Y))
    {
      const double dy{sf::Joystick::getAxisPosition(joystick_index, sf::Joystick::Y)};
      if (dy > 50.0) {
        this->focusNextChild();
      }
      if (dy < -50.0) {
        this->focusPreviousChild();
      }
    }
    if (sf::Joystick::isButtonPressed(joystick_index,0)) {
      QKeyEvent key(QEvent::KeyPress,Qt::Key_Enter,Qt::NoModifier);
      keyPressEvent(&key);
    }
  }
  #endif // USE_SFML_FOR_JOYSTICK_SUPPORT
}

void ribi::dws::QtMenuDialog::on_button_quit_clicked()
{
  close();
}
