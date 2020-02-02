cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")

# automatically use vcpkg if VCPKG_ROOT is defined
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  message(STATUS "Using VCPKG_ROOT $ENV{VCPKG_ROOT}")
  set(CMAKE_TOOLCHAIN_FILE
      "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
endif()

# Remove MinSizeRel build configuration, not useful
set(CMAKE_CONFIGURATION_TYPES Debug Release RelWithDebInfo CACHE STRING INTERNAL FORCE )

project(freeking)

# Configure C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# disable in-source builds
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# default build type to RelWithDebInfo
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

# Output binaries to bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Check if our compiler has filesystem or experimental/filesystem
include(CheckIncludeFileCXX)
check_include_file_cxx("filesystem" _CXX_FILESYSTEM_HAVE_HEADER)
check_include_file_cxx("experimental/filesystem" _CXX_FILESYSTEM_HAVE_EXPERIMENTAL_HEADER)
mark_as_advanced(_CXX_FILESYSTEM_HAVE_HEADER)
mark_as_advanced(_CXX_FILESYSTEM_HAVE_EXPERIMENTAL_HEADER)

# Dependencies
find_package(SDL2 REQUIRED)
find_package(OpenAL REQUIRED)
find_package(fmt REQUIRED)

# Wrap OpenAL Soft in an interface
if (OPENAL_FOUND AND NOT TARGET OpenAL::OpenAL)
  add_library(OpenAL::OpenAL INTERFACE IMPORTED GLOBAL)
  set_target_properties(OpenAL::OpenAL PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${OPENAL_INCLUDE_DIR})
  set_target_properties(OpenAL::OpenAL PROPERTIES INTERFACE_LINK_LIBRARIES ${OPENAL_LIBRARY})
endif()

# The Code
add_subdirectory(Source)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/bin/$<CONFIG>")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
