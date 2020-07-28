# Generated from qtwinextras.pro.

cmake_minimum_required(VERSION 3.15.0)

include(.cmake.conf)
project(QtWinExtras
    VERSION "${QT_REPO_MODULE_VERSION}"
    DESCRIPTION "Qt WinExtras Libraries"
    HOMEPAGE_URL "https://qt.io/"
    LANGUAGES CXX C
)

find_package(Qt6 ${PROJECT_VERSION} CONFIG REQUIRED COMPONENTS BuildInternals Widgets Quick) # special case
find_package(Qt6 ${PROJECT_VERSION} CONFIG OPTIONAL_COMPONENTS) # special case

# special case begin
if (NOT WIN32)
    return()
endif()
# special case end

qt_build_repo()
