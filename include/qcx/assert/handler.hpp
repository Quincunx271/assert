#pragma once

#include <cstddef> // std::size_t
#include <cstdio> // std::fputs
#include <cstdlib> // std::abort
#include <stdexcept> //std::logic_error
#include <string>
#include <string_view>

#define QCX_ASSERT_INFO(...)                                     \
    ::qcx::assert_info                                           \
    {                                                            \
        ::std::string_view{__VA_ARGS__},                         \
            ::std::string_view{__FILE__},                        \
            ::std::string_view{QCX_DETAIL_ASSERT_STR(__LINE__)}, \
    }

namespace qcx {
    struct assert_info {
        std::string_view message;
        std::string_view file;
        std::string_view line;
    };

    using assert_handler_f = void(assert_info const& info);

    struct assertion_error : std::logic_error {
        using std::logic_error::logic_error;
    };

    namespace detail {
        inline std::string_view assert_msg_prefix = "assertion_error: ";

        template <typename SizeInfoF, typename FormF>
        constexpr void form_assert_msg(assert_info const& info, SizeInfoF sizeInfo, FormF form)
        {
            sizeInfo(assert_msg_prefix.size()
                + info.file.size()
                + 1 // for ':'
                + info.line.size()
                + 2 // for ": "
                + info.message.size());
            form(assert_msg_prefix);
            form(info.file);
            form(std::string_view{":"});
            form(info.line);
            form(std::string_view{": "});
            form(info.message);
        }
    }

    [[noreturn]] inline void throw_assert_handler(assert_info const& info)
    {
        std::string message;
        detail::form_assert_msg(info,
            [&](auto size) { message.reserve(size); },
            [&](auto str) { message.append(str); });

        throw assertion_error{message};
    }

    [[noreturn]] inline void abort_assert_handler(assert_info const& info)
    {
        detail::form_assert_msg(info, [](auto) {},
            [](auto sv) {
                std::fwrite(sv.data(), 1, sv.size(), stderr);
            });
        std::fputc('\n', stderr);

        std::abort();
    }

    namespace detail {
        inline assert_handler_f* assert_handler = abort_assert_handler;
    }


// Clang warns about the function returning, but we know that our assert_handler won't return.
// Clang doesn't know this, since the assert_handler could have been set to a function
// pointer that *does* return.
#ifdef __clang__
#define QCX_ASSERT_INTERNAL_UNREACHABLE() __builtin_unreachable()
#else
#define QCX_ASSERT_INTERNAL_UNREACHABLE()
#endif

    [[noreturn]] inline void assert_handler(assert_info const& info)
    {
        detail::assert_handler(info);
        QCX_ASSERT_INTERNAL_UNREACHABLE();
    }

    inline void use_assert_handler(assert_handler_f* handler)
    {
        detail::assert_handler = handler;
    }
}
