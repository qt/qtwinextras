win32 {
    TEMPLATE = subdirs
    CONFIG += ordered
    SUBDIRS += winextras imports
} else {
    # fake project for creating the documentation
    TEMPLATE = aux
    QMAKE_DOCS = $$PWD/winextras/doc/qtwinextras.qdocconf
}
