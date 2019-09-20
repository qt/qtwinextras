# special case begin
# Generated from src.pro.

if(NOT WIN32)
    return()
endif()

add_subdirectory(winextras)
if(TARGET Qt::Quick)
    add_subdirectory(imports)
endif()
# special case end
