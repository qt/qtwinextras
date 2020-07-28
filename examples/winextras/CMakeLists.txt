# Generated from winextras.pro.

if(WIN32)
    add_subdirectory(iconextractor)
endif()
if(TARGET Qt::Multimedia AND TARGET Qt::Widgets AND WIN32)
    add_subdirectory(musicplayer)
endif()
if(TARGET Qt::Multimedia AND TARGET Qt::Quick AND WIN32)
    add_subdirectory(quickplayer)
endif()
