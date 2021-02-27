#ifndef QCX_ASSERT_CONFIG_ATTRIBUTES_HPP
#define QCX_ASSERT_CONFIG_ATTRIBUTES_HPP

#if defined(__clang__)
#    ifndef QCX_COMPILER_IS_CLANG
#        define QCX_COMPILER_IS_CLANG true
#    endif
#elif defined(__GNUC__)
#    ifndef QCX_COMPILER_IS_GCC
#        define QCX_COMPILER_IS_GCC true
#    endif
#elif defined(_MSC_VER)
#    ifndef QCX_COMPILER_IS_MSVC
#        define QCX_COMPILER_IS_MSVC true
#    endif
#endif

#ifndef QCX_COMPILER_IS_CLANG
#    define QCX_COMPILER_IS_CLANG false
#endif

#ifndef QCX_COMPILER_IS_GCC
#    define QCX_COMPILER_IS_GCC false
#endif

#ifndef QCX_COMPILER_IS_MSVC
#    define QCX_COMPILER_IS_MSVC false
#endif

#if QCX_COMPILER_IS_CLANG || QCX_COMPILER_IS_GCC
#    define QCX_ALWAYS_INLINE [[gnu::always_inline]]
#    define QCX_NOINLINE [[gnu::noinline]]
#elif QCX_COMPILR_IS_MSVC
#    define QCX_ALWAYS_INLINE __forceinline
#    define QCX_NOINLINE __declspec(noinline)
#endif

#ifndef QCX_ALWAYS_INLINE
#    define QCX_ALWAYS_INLINE
#endif

#ifndef QCX_NOINLINE
#    define QCX_NOINLINE
#endif

#endif // QCX_ASSERT_CONFIG_ATTRIBUTES_HPP
