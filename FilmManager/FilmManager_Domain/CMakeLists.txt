cmake_minimum_required(VERSION 3.16)

project(FilmManager_Domain LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(FilmManager_Domain SHARED
  FilmManager_Domain_global.h


  entry.h entry.cpp
  titleentry.h titleentry.cpp
  genre.h
  genre.cpp
  person.h person.cpp
  movie.h movie.cpp
  episode.h episode.cpp
  serie.h serie.cpp
  serieStatus.h
  serieStatus.cpp

)

target_link_libraries(FilmManager_Domain PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(FilmManager_Domain PRIVATE FILMMANAGER_DOMAIN_LIBRARY)
