# Generated from qpixmap.pro.

#####################################################################
## tst_qpixmap Test:
#####################################################################

add_qt_test(tst_qpixmap
    SOURCES
        tst_qpixmap.cpp
    PUBLIC_LIBRARIES
        Qt::Gui
        Qt::WinExtras
)

## Scopes:
#####################################################################

extend_target(tst_qpixmap CONDITION QT_FEATURE_dynamicgl OR (WIN32 AND NOT TARGET Qt::OpenGL)
    PUBLIC_LIBRARIES
        gdi32
        user32
)
