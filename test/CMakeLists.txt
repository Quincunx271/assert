if(BUILD_TESTING)
  find_path(CATCH_INCLUDE_DIR catch.hpp)
  if(CATCH_INCLUDE_DIR STREQUAL "CATCH_INCLUDE_DIR-NOTFOUND")
    message(FATAL_ERROR "Could not find Catch2")
  endif()
  add_library(Catch INTERFACE)
  target_include_directories(Catch
    INTERFACE ${CATCH_INCLUDE_DIR}
  )

  ##########
  # Test targets
  ##

  add_executable(qcx_assert_test_fast
    test_main.cpp
    test_fast.cpp
  )
  target_link_libraries(qcx_assert_test_fast
    Catch
    qcx_assert
  )
  target_compile_definitions(qcx_assert_test_fast PRIVATE QCX_ASSERT_LEVEL_FAST)

  add_executable(qcx_assert_test_normal
    test_main.cpp
    test_normal.cpp
  )
  target_link_libraries(qcx_assert_test_normal
    Catch
    qcx_assert
  )
  target_compile_definitions(qcx_assert_test_normal PRIVATE QCX_ASSERT_LEVEL_NORMAL)

  add_executable(qcx_assert_test_safe
    test_main.cpp
    test_safe.cpp
  )
  target_link_libraries(qcx_assert_test_safe
    Catch
    qcx_assert
  )
  target_compile_definitions(qcx_assert_test_safe PRIVATE QCX_ASSERT_LEVEL_SAFE)

  add_executable(qcx_assert_test_default
    test_main.cpp
    test_normal.cpp
  )
  target_link_libraries(qcx_assert_test_default
    Catch
    qcx_assert
  )

  if (MSVC)
    target_compile_options(qcx_assert_test_fast
      PRIVATE
        /W4
        /permissive-
        $<$<CONFIG:QCX_ASSERT_TREAT_WARNINGS_AS_ERRORS>:/Wx>
    )
    target_compile_options(qcx_assert_test_normal
      PRIVATE
        /W4
        /permissive-
        $<$<CONFIG:QCX_ASSERT_TREAT_WARNINGS_AS_ERRORS>:/Wx>
    )
    target_compile_options(qcx_assert_test_safe
      PRIVATE
        /W4
        /permissive-
        $<$<CONFIG:QCX_ASSERT_TREAT_WARNINGS_AS_ERRORS>:/Wx>
    )
    target_compile_options(qcx_assert_test_default
      PRIVATE
        /W4
        /permissive-
        $<$<CONFIG:QCX_ASSERT_TREAT_WARNINGS_AS_ERRORS>:/Wx>
    )
  elseif(CMAKE_COMPILER_IS_GNUCC )
    target_compile_options(qcx_assert_test_fast
      PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        $<$<CONFIG:QCX_ASSERT_TREAT_WARNINGS_AS_ERRORS>:-Werror>
    )
    target_compile_options(qcx_assert_test_normal
      PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        $<$<CONFIG:QCX_ASSERT_TREAT_WARNINGS_AS_ERRORS>:-Werror>
    )
    target_compile_options(qcx_assert_test_safe
      PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        $<$<CONFIG:QCX_ASSERT_TREAT_WARNINGS_AS_ERRORS>:-Werror>
    )
    target_compile_options(qcx_assert_test_default
      PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        $<$<CONFIG:QCX_ASSERT_TREAT_WARNINGS_AS_ERRORS>:-Werror>
    )
  endif()

  add_test(test_fast qcx_assert_test_fast)
  add_test(test_normal qcx_assert_test_normal)
  add_test(test_safe qcx_assert_test_safe)
  add_test(test_default qcx_assert_test_default)
endif()
