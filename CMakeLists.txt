cmake_minimum_required(VERSION 3.0)

project(qiojs)

include(iojs.cmake)

set(CMAKE_AUTOMOC ON)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()

find_package(Qt5Gui)
find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5WebEngineWidgets)
find_package(Qt5WebChannel)
find_package(Qt5WebSockets)
find_package(Threads)

add_definitions(-DTHREAD_POOL_SIZE=4)

include_directories(
  ${Qt5Gui_PRIVATE_INCLUDE_DIRS}

  ${CMAKE_SOURCE_DIR}/3rdparty/

  ${IOJS_DIR}/deps/
  ${IOJS_DIR}/deps/v8/
  ${IOJS_DIR}/deps/uv/include/
  ${IOJS_DIR}/deps/v8/include/
  ${IOJS_DIR}/deps/cares/include/)

file(GLOB QT_EVENT_DISPATCHER_LIBUV
  ${CMAKE_SOURCE_DIR}/3rdparty/qt-event-dispatcher-libuv/src/eventdispatcherlibuv.cpp
  ${CMAKE_SOURCE_DIR}/3rdparty/qt-event-dispatcher-libuv/src/eventdispatcherlibuv/*.cpp)

file(GLOB_RECURSE SOURCE_FILES src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${QT_EVENT_DISPATCHER_LIBUV})

foreach(IOJS_LIB ${IOJS_STATIC_LIBRARIES})
  target_link_libraries(${PROJECT_NAME} -Wl,--whole-archive ${IOJS_DIR}/out/Release/${IOJS_LIB} -Wl,--no-whole-archive)
endforeach(IOJS_LIB)

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS} Qt5::Core Qt5::Widgets)

add_dependencies(${PROJECT_NAME} iojs)

