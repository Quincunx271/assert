#pragma once

#include <qcx/assert/config.hpp>
#include <qcx/assert/detail/run_assert.hpp>

#define QCX_DETAIL_RUN_ASSERT(...) qcx::detail::run_assert(__VA_ARGS__, "assertion failed: " QCX_ASSERT_SOURCE_INFO QCX_DETAIL_ASSERT_STR(__VA_ARGS__) "\n")


#if QCX_ASSERT_FAST_ACTIVE
#define QCX_ASSERT_FAST(...) QCX_DETAIL_RUN_ASSERT(__VA_ARGS__)
#else
#define QCX_ASSERT_FAST(...)
#endif

#if QCX_ASSERT_ACTIVE
#define QCX_ASSERT(...) QCX_DETAIL_RUN_ASSERT(__VA_ARGS__)
#else
#define QCX_ASSERT(...)
#endif

#if QCX_ASSERT_DEBUG_ACTIVE
#define QCX_ASSERT_DEBUG(...) QCX_DETAIL_RUN_ASSERT(__VA_ARGS__)
#else
#define QCX_ASSERT_DEBUG(...)
#endif
