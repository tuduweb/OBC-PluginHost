cmake_minimum_required(VERSION 3.14)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "
    FATAL: In-source builds are not allowed.
           You should create a separate directory for build files.
           ")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # doesnt work
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works

IF (APPLE)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/usr/local/opt/qt5/lib/cmake")
ENDIF()

project(OBCPluginHost VERSION 0.1 LANGUAGES CXX)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Widgets WebSockets Network LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets WebSockets Network LinguistTools REQUIRED)

include(./src/plugin/ObPluginInterface.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/plugin/)

set(PROJECT_SOURCES
        #resources.qrc
        src/main.cpp
)

add_executable(OBCApp
    ${PROJECT_SOURCES}
)

### add extra qt library
target_link_libraries(OBCApp
    PRIVATE Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::WebSockets
    Qt${QT_VERSION_MAJOR}::Network
)


# add_library()
# add_executable()

option(IS_BUILD_PLUGIN_EXAMPLES "build examples" ON)

# if(IS_BUILD_PLUGIN_EXAMPLES)
#     #修改目录位置 还要防止套娃现象发生
#     include(${CMAKE_CURRENT_LIST_DIR}/src/plugin/examples/)
# endif()

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/plugin/examples/)
