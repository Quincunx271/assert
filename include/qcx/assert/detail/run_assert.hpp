#ifndef QCX_ASSERT_DETAIL_RUN_ASSERT_HPP
#define QCX_ASSERT_DETAIL_RUN_ASSERT_HPP

#include <qcx/assert/config.hpp>
#include <qcx/assert/config/attributes.hpp>
#include <qcx/assert/config/handler.hpp>

namespace qcx::detail {
    QCX_ALWAYS_INLINE
    inline void run_assert(auto enabled, auto const& condition_fn, qcx::assert::assert_info const& info)
    {
        if (enabled) {
            if (!condition_fn()) { qcx::assert::config::assertion_handler(info); }
        }
    }
}

#endif // QCX_ASSERT_DETAIL_RUN_ASSERT_HPP
