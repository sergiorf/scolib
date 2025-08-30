
cmake_minimum_required(VERSION 3.18)
project(SCOLIB
    VERSION 0.1.0
    DESCRIPTION "SCOLIB — Simulation COre LIBrary: a modern, embeddable SPICE-lite core with a photonics roadmap"
    LANGUAGES CXX)

# Options
option(SCOLIB_BUILD_PYTHON "Build Python bindings (requires pybind11)" ON)
option(SCOLIB_BUILD_TESTS  "Build tests" ON)
option(SCOLIB_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Default to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Ensure all targets are built with -fPIC on platforms that need it (Linux)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Library
add_library(scolib
    src/core/version.cpp
    src/circuit/circuit.cpp
)

target_include_directories(scolib
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<INSTALL_INTERFACE:include>
)

target_compile_features(scolib PUBLIC cxx_std_20)

# Warnings
if(MSVC)
  target_compile_options(scolib PRIVATE /W4)
else()
  target_compile_options(scolib PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Exported header for simple visibility (not strictly required here)
target_compile_definitions(scolib PUBLIC SCOLIB_EXPORTS)

# Python bindings (optional)
if(SCOLIB_BUILD_PYTHON)
  find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)
  # Try to find pybind11 via CMake config (provided by pip or system pkg)
  find_package(pybind11 QUIET CONFIG)
  if(pybind11_FOUND)
    message(STATUS "pybind11 found: ${pybind11_DIR}")
    pybind11_add_module(scolib_py bindings/python/scolib_py.cpp)
    target_link_libraries(scolib_py PRIVATE scolib)
    set_target_properties(scolib_py PROPERTIES OUTPUT_NAME "scolib")
  else()
    message(WARNING "pybind11 not found; Python bindings will not be built.")
  endif()
endif()

# Tests
include(CTest)
if (SCOLIB_BUILD_TESTS AND BUILD_TESTING)
  add_executable(scolib_tests tests/test_basic.cpp)
  target_link_libraries(scolib_tests PRIVATE scolib)
  add_test(NAME basic COMMAND scolib_tests)
endif()

# Install (basic)
include(GNUInstallDirs)
install(TARGETS scolib
  EXPORT scolibTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT scolibTargets
  FILE scolibTargets.cmake
  NAMESPACE scolib::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/scolib
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/scolibConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)
configure_file(cmake/scolibConfig.cmake.in scolibConfig.cmake @ONLY)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/scolibConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/scolibConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/scolib
)
