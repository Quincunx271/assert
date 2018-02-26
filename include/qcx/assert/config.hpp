#pragma once

#if !defined(QCX_ASSERT_LEVEL_NONE)      \
    && !defined(QCX_ASSERT_LEVEL_FAST)   \
    && !defined(QCX_ASSERT_LEVEL_NORMAL) \
    && !defined(QCX_ASSERT_LEVEL_SAFE)

#if defined(QCX_TARGET_OPTIMIZED_BUILD)
#define QCX_ASSERT_LEVEL_FAST
#elif defined(QCX_TARGET_SAFE_BUILD)
#define QCX_ASSERT_LEVEL_SAFE
#else
#define QCX_ASSERT_LEVEL_NORMAL
#endif

#endif

#if defined(QCX_ASSERT_LEVEL_NONE)         \
        + defined(QCX_ASSERT_LEVEL_FAST)   \
        + defined(QCX_ASSERT_LEVEL_NORMAL) \
        + defined(QCX_ASSERT_LEVEL_SAFE)   \
    > 1
#error Cannot have multiple of QCX_ASSERT_LEVEL_{NONE, FAST, NORMAL, SAFE} specified
#endif

#ifdef QCX_ASSERT_LEVEL_NONE
#define QCX_ASSERT_FAST_ACTIVE 0
#define QCX_ASSERT_ACTIVE 0
#define QCX_ASSERT_SAFE_ACTIVE 0
#endif

#ifdef QCX_ASSERT_LEVEL_FAST
#define QCX_ASSERT_FAST_ACTIVE 1
#define QCX_ASSERT_ACTIVE 0
#define QCX_ASSERT_SAFE_ACTIVE 0
#endif

#ifdef QCX_ASSERT_LEVEL_NORMAL
#define QCX_ASSERT_FAST_ACTIVE 1
#define QCX_ASSERT_ACTIVE 1
#define QCX_ASSERT_SAFE_ACTIVE 0
#endif

#ifdef QCX_ASSERT_LEVEL_SAFE
#define QCX_ASSERT_FAST_ACTIVE 1
#define QCX_ASSERT_ACTIVE 1
#define QCX_ASSERT_SAFE_ACTIVE 1
#endif

#define QCX_DETAIL_ASSERT_STR2(...) #__VA_ARGS__
#define QCX_DETAIL_ASSERT_STR(...) QCX_DETAIL_ASSERT_STR2(__VA_ARGS__)
