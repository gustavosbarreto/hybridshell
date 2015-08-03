cmake_minimum_required(VERSION 3.0)

project(qt)

set(CMAKE_AUTOMOC ON)

find_package(Qt5Gui)
find_package(Qt5Widgets)
find_package(Qt5WebEngineWidgets)
find_package(Qt5WebChannel)
find_package(Qt5WebSockets)

include_directories(${CMAKE_JS_INC})

file(GLOB_RECURSE SOURCE_FILES "src/*")

qt5_add_resources(RESOURCES qtnode.qrc)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${RESOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB} Qt5::Widgets Qt5::WebEngineWidgets Qt5::WebChannel Qt5::WebSockets)

