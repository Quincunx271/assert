#ifndef QCX_ASSERT_HPP
#define QCX_ASSERT_HPP

#include <qcx/assert/config.hpp>
#include <qcx/assert/detail/run_assert.hpp>

#define QCX_DETAIL_ASSERT_STR2(...) #__VA_ARGS__
#define QCX_DETAIL_ASSERT_STR(...) QCX_DETAIL_ASSERT_STR2(__VA_ARGS__)

#define QCX_DETAIL_RUN_ASSERT(ENABLE, MESSAGE, ...)                                                                    \
    ::qcx::detail::run_assert(                                                                                         \
        ENABLE, [&]() -> bool { return __VA_ARGS__; },                                                                 \
        ::qcx::assert::config::get_assert_info(QCX_DETAIL_ASSERT_STR(__VA_ARGS__), MESSAGE,                            \
            ::qcx::assert::config::get_source_location(QCX_ASSERT_INTERNAL_SOURCE_LOCATION::current())))

#define QCX_ASSERT_FAST(...) QCX_DETAIL_RUN_ASSERT(::qcx::assert::config::enable_fast(), "", __VA_ARGS__)
#define QCX_ASSERT(...) QCX_DETAIL_RUN_ASSERT(::qcx::assert::config::enable_normal(), "", __VA_ARGS__)
#define QCX_ASSERT_SAFE(...) QCX_DETAIL_RUN_ASSERT(::qcx::assert::config::enable_safe(), "", __VA_ARGS__)

#define QCX_ASSERT_FAST_MSG(MESSAGE, ...)                                                                              \
    QCX_DETAIL_RUN_ASSERT(::qcx::assert::config::enable_fast(), MESSAGE, __VA_ARGS__)
#define QCX_ASSERT_MSG(MESSAGE, ...) /**/                                                                              \
    QCX_DETAIL_RUN_ASSERT(::qcx::assert::config::enable_normal(), MESSAGE, __VA_ARGS__)
#define QCX_ASSERT_SAFE_MSG(MESSAGE, ...)                                                                              \
    QCX_DETAIL_RUN_ASSERT(::qcx::assert::config::enable_safe(), MESSAGE, __VA_ARGS__)

#endif // QCX_ASSERT_HPP
