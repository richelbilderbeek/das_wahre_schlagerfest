# Qt Creator project of the graphical game, for Qt 6.
#
# Use a Desktop kit for the desktop version,
# use a WebAssembly kit for the WebAssembly version.
#
# The console version and the tests are built by CMakeLists.txt only.

TARGET = das_wahre_schlagerfest
TEMPLATE = app
QT += core gui widgets
CONFIG += c++17

CONFIG(release, debug|release) {
  DEFINES += NDEBUG
}

!wasm {
  # High warning levels
  QMAKE_CXXFLAGS += -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Werror

  # Joystick support is optional and desktop-only
  CONFIG += link_pkgconfig
  packagesExist(sfml-window) {
    PKGCONFIG += sfml-window
    DEFINES += USE_SFML_FOR_JOYSTICK_SUPPORT
  }
}

SOURCES += \
    daswahreschlagerfestmenudialog.cpp \
    daswahreschlagerfestterminal.cpp \
    daswahreschlagerfesttile.cpp \
    daswahreschlagerfestwidget.cpp \
    qtdaswahreschlagerfestmenudialog.cpp \
    qtdaswahreschlagerfestwidget.cpp \
    qtmain.cpp

HEADERS += \
    daswahreschlagerfestcursor.h \
    daswahreschlagerfestdisplay.h \
    daswahreschlagerfestkey.h \
    daswahreschlagerfestmenudialog.h \
    daswahreschlagerfestterminal.h \
    daswahreschlagerfesttile.h \
    daswahreschlagerfestwidget.h \
    qtdaswahreschlagerfestmenudialog.h \
    qtdaswahreschlagerfestwidget.h

FORMS += \
    qtdaswahreschlagerfestmenudialog.ui

RESOURCES += \
    DasWahreSchlagerfest.qrc
