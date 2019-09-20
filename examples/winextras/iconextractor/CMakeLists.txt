# Generated from iconextractor.pro.

cmake_minimum_required(VERSION 3.14)
project(iconextractor LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(INSTALL_EXAMPLEDIR "examples")

find_package(Qt6 COMPONENTS Core)
find_package(Qt6 COMPONENTS Gui)
find_package(Qt6 COMPONENTS WinExtras)

add_executable(iconextractor
    main.cpp
)
target_link_libraries(iconextractor PUBLIC
    Qt::Core
    Qt::Gui
    Qt::WinExtras
    shell32
    user32
)

install(TARGETS iconextractor
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
