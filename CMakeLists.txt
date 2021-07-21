cmake_minimum_required(VERSION 3.21)

include(cmake/in-source-guard.cmake)

project(
    cppsvc
    VERSION 0.1.0
    DESCRIPTION "Library for creating services (supports Windows Only)"
    HOMEPAGE_URL "https://github.com/EliSauder/cppsvc"
    LANGUAGES NONE
)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "Installation path" FORCE)

find_package(lingo REQUIRED)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(cppsvc_cppsvc INTERFACE)
add_library(cppsvc::cppsvc ALIAS cppsvc_cppsvc)

target_link_libraries(cppsvc_cppsvc INTERFACE lingo)

set_property(
    TARGET cppsvc_cppsvc PROPERTY
    EXPORT_NAME cppsvc
)

target_include_directories(
    cppsvc_cppsvc ${cppsvc_warning_guard}
    INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_compile_features(cppsvc_cppsvc INTERFACE cxx_std_20)

# ---- Install rules ----

include(cmake/install-rules.cmake)

# ---- Examples ----

if(PROJECT_IS_TOP_LEVEL)
  option(BUILD_EXAMPLES "Build examples tree." "${cppsvc_DEVELOPER_MODE}")
  if(BUILD_EXAMPLES)
    add_subdirectory(example)
  endif()
endif()

# ---- Developer mode ----

if(NOT cppsvc_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of cppsvc"
  )
endif()

include(CTest)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()

option(BUILD_MCSS_DOCS "Build documentation using Doxygen and m.css" OFF)
if(BUILD_MCSS_DOCS)
  include(cmake/docs.cmake)
endif()

option(ENABLE_COVERAGE "Enable coverage support separate from CTest's" OFF)
if(ENABLE_COVERAGE)
  include(cmake/coverage.cmake)
endif()

include(cmake/lint-targets.cmake)
include(cmake/spell-targets.cmake)
