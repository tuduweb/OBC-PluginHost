project(ObPlugin-examples-Mock)

cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

option(QVPLUGIN_USE_QT6 "Use Qt6")
if(QVPLUGIN_USE_QT6)
    set(QV_QT_LIBNAME Qt6)
else()
    set(QV_QT_LIBNAME Qt5)
endif()

find_package(${QV_QT_LIBNAME} COMPONENTS Core Widgets Gui Network REQUIRED)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

#set(OBC_PLUGINDIR ${CMAKE_SOURCE_DIR}/src/plugin)

include(../../ObPluginInterface.cmake)
include_directories(./)
include_directories(${OBPLUGIN_INTERFACE_INCLUDE_DIR})



set(OBC_PLUGIN_MOCK_SOURCES

    #kernels
    ${CMAKE_CURRENT_LIST_DIR}/kernel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/kernel.cpp

    #pluginInterface
    ${CMAKE_CURRENT_LIST_DIR}/MockPlugin.hpp
    ${CMAKE_CURRENT_LIST_DIR}/MockPlugin.cpp

    ${CMAKE_CURRENT_LIST_DIR}/MockGUI.hpp
    ${CMAKE_CURRENT_LIST_DIR}/MockGUI.cpp
)

#指定输出目录
if(DEFINED OBC_LIB_OUTPUT_PATH)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OBC_LIB_OUTPUT_PATH})
    message("output dir" ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
endif()

message(${CMAKE_CURRENT_LIST_DIR})

# neet to change output dir
add_library(${PROJECT_NAME} MODULE
    ${OBPLUGIN_INTERFACE_HEADERS}
    ${OBC_PLUGIN_MOCK_SOURCES}
)

if(APPLE)
    add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_INSTALL_NAME_TOOL} -add_rpath "@executable_path/../Frameworks/" $<TARGET_FILE:${PROJECT_NAME}>)
endif()

target_link_libraries(${PROJECT_NAME}
    ${QV_QT_LIBNAME}::Core
    ${QV_QT_LIBNAME}::Gui
    ${QV_QT_LIBNAME}::Widgets
    ${QV_QT_LIBNAME}::Network
)

#install(TARGETS ${PROJECT_NAME} DESTINATION share/qv2ray/plugins)
