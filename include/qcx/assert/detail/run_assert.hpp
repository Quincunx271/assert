#pragma once

#include <qcx/assert/config.hpp>
#include <qcx/assert/handler.hpp>

namespace qcx::detail {
    inline void run_assert(bool condition, qcx::assert_info const& info)
    {
        if (!condition) qcx::detail::assert_handler(info);
    }
}
