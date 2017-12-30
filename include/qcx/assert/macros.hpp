#ifndef QCX_ASSERT_MACROS_H_
#define QCX_ASSERT_MACROS_H_

#include <qcx/assert/config.hpp>
#include <qcx/assert/detail/run_assert.hpp>

#define QCX_DETAIL_RUN_ASSERT(...) qcx::detail::run_assert(__VA_ARGS__, QCX_ASSERT_INFO(QCX_DETAIL_ASSERT_STR(__VA_ARGS__)))

#if QCX_ASSERT_FAST_ACTIVE
#define QCX_ASSERT_FAST(...) QCX_DETAIL_RUN_ASSERT(__VA_ARGS__)
#else
#define QCX_ASSERT_FAST(...) ((void)0)
#endif

#if QCX_ASSERT_ACTIVE
#define QCX_ASSERT(...) QCX_DETAIL_RUN_ASSERT(__VA_ARGS__)
#else
#define QCX_ASSERT(...) ((void)0)
#endif

#if QCX_ASSERT_SAFE_ACTIVE
#define QCX_ASSERT_SAFE(...) QCX_DETAIL_RUN_ASSERT(__VA_ARGS__)
#else
#define QCX_ASSERT_SAFE(...) ((void)0)
#endif

#endif
