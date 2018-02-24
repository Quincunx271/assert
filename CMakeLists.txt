cmake_minimum_required(VERSION 3.8)

project(qcx_assert VERSION 0.1.0 LANGUAGES CXX)

option(QCX_ASSERT_CI_DEFAULTS "sets all the option defaults for continuous integration")
option(QCX_ASSERT_PCH
  "compile with precompiled headers (potential speedup). Requires cotire.cmake in CMAKE_MODULE_PATH")
option(QCX_ASSERT_TREAT_WARNINGS_AS_ERRORS "compiles with -Werror" ${QCX_ASSERT_CI_DEFAULTS})

include(CTest)

##########
# qcx_assert
##

add_library(qcx_assert INTERFACE )
add_library(qcx_assert::qcx_assert ALIAS qcx_assert)
target_include_directories(qcx_assert
  INTERFACE
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_features(qcx_assert
  INTERFACE
    cxx_std_17
)

add_subdirectory(test)
