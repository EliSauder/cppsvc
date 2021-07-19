cmake_minimum_required(VERSION 3.14)

project(cppsvcTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/windows-set-path.cmake)

if(PROJECT_IS_TOP_LEVEL)
  find_package(cppsvc REQUIRED)
  enable_testing()
endif()

add_executable(cppsvc_test source/cppsvc_test.cpp)
target_link_libraries(cppsvc_test PRIVATE cppsvc::cppsvc)
target_compile_features(cppsvc_test PRIVATE cxx_std_20)

add_test(NAME cppsvc_test COMMAND cppsvc_test)
