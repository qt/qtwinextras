# Generated from quickplayer.pro.

cmake_minimum_required(VERSION 3.14)
project(quickplayer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
  set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/winextras/quickplayer")

find_package(Qt6 COMPONENTS Core)
find_package(Qt6 COMPONENTS Gui)
find_package(Qt6 COMPONENTS Quick)

add_qt_gui_executable(quickplayer
    main.cpp
)
target_link_libraries(quickplayer PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Quick
)


# Resources:
set_source_files_properties("images/media-pause-16.png"
    PROPERTIES QT_RESOURCE_ALIAS "pause-16.png"
)
set_source_files_properties("images/media-pause-32.png"
    PROPERTIES QT_RESOURCE_ALIAS "pause-32.png"
)
set_source_files_properties("images/media-play-16.png"
    PROPERTIES QT_RESOURCE_ALIAS "play-16.png"
)
set_source_files_properties("images/media-play-32.png"
    PROPERTIES QT_RESOURCE_ALIAS "play-32.png"
)
set_source_files_properties("images/media-seek-backward-32.png"
    PROPERTIES QT_RESOURCE_ALIAS "backward-32.png"
)
set_source_files_properties("images/media-seek-forward-32.png"
    PROPERTIES QT_RESOURCE_ALIAS "forward-32.png"
)
set_source_files_properties("images/media-stop-32.png"
    PROPERTIES QT_RESOURCE_ALIAS "stop-32.png"
)
set_source_files_properties("qml/main.qml"
    PROPERTIES QT_RESOURCE_ALIAS "main.qml"
)
set(quickplayer_resource_files
    "images/media-pause-16.png"
    "images/media-pause-32.png"
    "images/media-play-16.png"
    "images/media-play-32.png"
    "images/media-seek-backward-32.png"
    "images/media-seek-forward-32.png"
    "images/media-stop-32.png"
    "qml/main.qml"
)

qt6_add_resources(quickplayer "quickplayer"
    PREFIX
        "/"
    FILES
        ${quickplayer_resource_files}
)

install(TARGETS quickplayer
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
