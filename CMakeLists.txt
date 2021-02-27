cmake_minimum_required(VERSION 3.12)

project(qcx_assert VERSION 0.2.0 LANGUAGES CXX)

##########
# qcx_assert
##

add_library(qcx_assert INTERFACE )
add_library(Qcx::Assert ALIAS qcx_assert)
target_include_directories(qcx_assert
  INTERFACE
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_features(qcx_assert
  INTERFACE
    cxx_std_20
)

include(GNUInstallDirs)

install(DIRECTORY include/
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

set(QCX_ASSERT_CMAKE_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/QcxAssert")

install(TARGETS qcx_assert
  EXPORT QcxAssertConfig
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

set_target_properties(qcx_assert PROPERTIES EXPORT_NAME Assert)

install(EXPORT QcxAssertConfig
  NAMESPACE
    Qcx::
  DESTINATION
    ${QCX_ASSERT_CMAKE_INSTALL_DIR}
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/QcxAssertConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
  ARCH_INDEPENDENT
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/QcxAssertConfigVersion.cmake
  DESTINATION
    ${QCX_ASSERT_CMAKE_INSTALL_DIR}
)
