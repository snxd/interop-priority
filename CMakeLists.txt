cmake_minimum_required(VERSION 2.8)

include_directories(.)
include_directories(interop)

add_subdirectory(interop)

set(PRIORITY_SRC
    priorityinterop.c
    priorityinvoke.c
    prioritytask.c)
set(PRIORITY_HEADERS
    priority.h
    prioritytask.h)

if(WIN32)
    list(APPEND PRIORITY_SRC windows/priority.c)
    list(APPEND PRIORITY_SRC windows/resource.rc)
    list(APPEND PRIORITY_HEADERS windows/resource.h)
elseif(APPLE)
    list(APPEND PRIORITY_SRC mac/priority.c)
elseif(UNIX)
    list(APPEND PRIORITY_SRC linux/priority.c)
endif()

if(WIN32)
    set(CMAKE_SHARED_LINKER_FLAGS
        "${CMAKE_MODULE_LINKER_FLAGS} \"/DEF:${CMAKE_CURRENT_SOURCE_DIR}/windows/priority.def\"")
elseif(APPLE)
    set(CMAKE_XCODE_ATTRIBUTE_EXPORTED_SYMBOLS_FILE
        "${CMAKE_CURRENT_SOURCE_DIR}/mac/priority.def")
elseif(UNIX)
    set(CMAKE_SHARED_LINKER_FLAGS 
        "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/linux/priority.def")
    set(CMAKE_SHARED_LINKER_FLAGS 
        "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--gc-sections")
endif()

project(priority C)

add_library(${PROJECT_NAME} SHARED ${PRIORITY_SRC} ${PRIORITY_HEADERS})
target_link_libraries(${PROJECT_NAME} interoplib)
