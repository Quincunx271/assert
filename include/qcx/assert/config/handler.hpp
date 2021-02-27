#ifndef QCX_ASSERT_CONFIG_HANDLER_HPP
#define QCX_ASSERT_CONFIG_HANDLER_HPP

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <span>
#include <string>
#include <string_view>

#if __cpp_lib_source_location
#    include <source_location>
#    define QCX_ASSERT_INTERNAL_SOURCE_LOCATION ::std::source_location
#else
#    include <experimental/source_location>
#    define QCX_ASSERT_INTERNAL_SOURCE_LOCATION ::std::experimental::source_location
#endif

#include <qcx/assert/config/attributes.hpp>

namespace qcx::assert {
    struct source_location {
        std::uint_least32_t line = {};
        std::string_view file_name = "";
        std::string_view function_name = "";

        constexpr source_location() = default;

        constexpr source_location(QCX_ASSERT_INTERNAL_SOURCE_LOCATION loc)
            : line(loc.line())
            , file_name(loc.file_name())
            , function_name(loc.function_name())
        {
        }
    };

    struct assert_info {
        std::string_view assertion_contents;
        std::string_view message;
        source_location source_info;
    };

    class position_str {
    private:
        static constexpr std::size_t max_uint64_length = 20 + 1; // Add one to avoid going before the front

        char buffer[max_uint64_length];
        std::string_view buf_view;

    public:
        constexpr position_str(std::uint_least32_t x) { buf_view = to_str(x, buffer); }

        constexpr std::string_view str_view() const { return buf_view; }

    private:
        static constexpr std::string_view to_str(std::uint_least32_t x, std::span<char, max_uint64_length> buffer)
        {
            if (x == 0) return "0";
            auto cur = buffer.end();
            --cur;

            while (x > 0) {
                *cur-- = static_cast<char>('0' + x % 10);
                x /= 10;
            }

            return std::string_view(cur + 1, buffer.end());
        }
    };

    inline std::string form_default_assert_message(assert_info const& info)
    {
        std::string result;

        position_str line_(info.source_info.line);
        std::string_view line = line_.str_view();

        result.reserve(info.source_info.file_name.size() + (sizeof(":") - 1) + line.size() + (sizeof(": ") - 1)
            + info.source_info.function_name.size() + (sizeof(": ") - 1) //
            + (sizeof("Assertion `") - 1) + info.assertion_contents.size() + (sizeof("' failed with message: ") - 1)
            + info.message.size() + (sizeof(".") - 1));

        result += info.source_info.file_name;
        result += ':';
        result += line;
        result += ": ";
        result += info.source_info.function_name;
        result += ": ";
        result += "Assertion `";
        result += info.assertion_contents;
        result += "' failed";

        if (!info.message.empty()) {
            result += " with message: ";
            result += info.message;
        }
        result += '.';

        return result;
    }

    [[noreturn]] inline void abort_assert_handler(assert_info const& info)
    {
        std::string message = qcx::assert::form_default_assert_message(info);
        std::fputs(message.c_str(), stderr);
        std::fputc('\n', stderr);
        std::fflush(stderr);

        std::abort();
    }
}

#endif // QCX_ASSERT_CONFIG_HANDLER_HPP
