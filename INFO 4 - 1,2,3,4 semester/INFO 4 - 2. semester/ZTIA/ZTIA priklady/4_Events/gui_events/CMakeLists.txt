# CMake project file for event handling examples
# Documentation: https://cmake.org/runningcmake/

cmake_minimum_required(VERSION 3.5)
project(ZTIAPL CXX C)

# Edit to your Qt5 installation
set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt5/5.8.0_1/" CACHE STRING "" FORCE)

if(WIN32)
  add_executable(events_win32 events_win32.c)
endif()

find_package(GTK2)
if(GTK2_FOUND)
  add_executable(events_gtk events_gtk.c)
  target_link_libraries(events_gtk ${GTK2_LIBRARIES})
  target_include_directories(events_gtk PRIVATE ${GTK2_INCLUDE_DIRS})
endif()

find_package(Glut)
if(GLUT_FOUND)
  add_executable(events_glut events_glut.c)
  target_link_libraries(events_glut ${GLUT_LIBRARIES})
  target_include_directories(events_glut PRIVATE ${GLUT_INCLUDE_DIRS})
endif()

find_package(Qt5 COMPONENTS Widgets)
if(Qt5_FOUND)
  set(CMAKE_AUTOMOC ON)
  add_executable(events_qt events_qt.cpp)
  target_link_libraries(events_qt Qt5::Widgets)
  target_include_directories(events_qt PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
endif()
