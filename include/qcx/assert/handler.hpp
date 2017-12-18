#pragma once

#include <cstdio> // std::fputs
#include <cstdlib> // std::abort
#include <stdexcept> //std::logic_error

namespace qcx {
    using assert_handler_f = void(char const* message);

    [[noreturn]] inline void throw_handler(char const* message)
    {
        throw std::logic_error{message};
    }

    [[noreturn]] inline void abort_handler(char const* message)
    {
        std::fputs(message, stderr);
        std::abort();
    }

    namespace detail {
        inline assert_handler_f* assert_handler = abort_handler;
    }

    [[noreturn]] inline void current_handler(char const* message)
    {
        detail::assert_handler(message);
    }

    inline void register_assert_handler(assert_handler_f* handler)
    {
        detail::assert_handler = handler;
    }
}
