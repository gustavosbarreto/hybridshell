include(ExternalProject)

set(IOJS_DIR ${CMAKE_SOURCE_DIR}/3rdparty/iojs/)

set(IOJS_STATIC_LIBRARIES
  libcares.a
  libhttp_parser.a
  libiojs.a
  libopenssl.a
  libuv.a
  libv8_base.a
  libv8_libbase.a
  libv8_libplatform.a
  libv8_nosnapshot.a
  libzlib.a)

ExternalProject_Add(iojs
  PREFIX ${CMAKE_SOURCE_DIR}/3rdparty/iojs/
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/3rdparty/iojs/
  BUILD_IN_SOURCE 1
  CONFIGURE_COMMAND ./configure --enable-static
  BUILD_COMMAND $(MAKE)
  INSTALL_COMMAND "")

