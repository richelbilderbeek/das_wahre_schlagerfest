cmake_minimum_required(VERSION 3.21)
project(das_wahre_schlagerfest VERSION 5.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

if(NOT EMSCRIPTEN)
  add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Werror)
endif()

# The game logic and terminal front-end, free of Qt
add_library(das_wahre_schlagerfest_core STATIC
  daswahreschlagerfestmenudialog.cpp
  daswahreschlagerfestterminal.cpp
  daswahreschlagerfesttile.cpp
  daswahreschlagerfestwidget.cpp
)
target_include_directories(das_wahre_schlagerfest_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# The graphical game: the desktop version, or the WebAssembly version
# when configured with the qt-cmake of a Qt for WebAssembly kit
qt_add_executable(das_wahre_schlagerfest
  DasWahreSchlagerfest.qrc
  qtdaswahreschlagerfestmenudialog.cpp
  qtdaswahreschlagerfestmenudialog.ui
  qtdaswahreschlagerfestwidget.cpp
  qtmain.cpp
)
target_link_libraries(das_wahre_schlagerfest PRIVATE das_wahre_schlagerfest_core Qt6::Widgets)

if(NOT EMSCRIPTEN)
  # Joystick support is optional and desktop-only
  find_package(SFML 2 COMPONENTS window QUIET)
  if(SFML_FOUND)
    target_compile_definitions(das_wahre_schlagerfest PRIVATE USE_SFML_FOR_JOYSTICK_SUPPORT)
    target_link_libraries(das_wahre_schlagerfest PRIVATE sfml-window)
  endif()

  add_executable(das_wahre_schlagerfest_console main.cpp)
  target_link_libraries(das_wahre_schlagerfest_console PRIVATE das_wahre_schlagerfest_core)

  find_package(Boost REQUIRED COMPONENTS unit_test_framework)
  add_executable(das_wahre_schlagerfest_test
    daswahreschlagerfesttile_test.cpp
    daswahreschlagerfestwidget_test.cpp
    main_test.cpp
  )
  target_link_libraries(das_wahre_schlagerfest_test PRIVATE
    das_wahre_schlagerfest_core
    Boost::unit_test_framework
  )
  enable_testing()
  add_test(NAME das_wahre_schlagerfest_test COMMAND das_wahre_schlagerfest_test)
endif()
