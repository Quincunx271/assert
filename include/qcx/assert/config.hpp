#ifndef QCX_ASSERT_CONFIG_HPP
#define QCX_ASSERT_CONFIG_HPP

#if __has_include(<qcx-assert.tweaks.hpp>)
#    include <qcx-assert.tweaks.hpp>
#endif

#include <qcx/assert/config/assert_level.hpp>
#include <qcx/assert/config/attributes.hpp>
#include <qcx/assert/config/handler.hpp>

namespace qcx::assert::config {
    namespace defaults {
    }

    using namespace defaults;

    namespace defaults {
        QCX_ALWAYS_INLINE constexpr auto level()
        {
#ifndef NDEBUG
            return assert_level::normal;
#else
            return assert_level::fast;
#endif
        }

        QCX_ALWAYS_INLINE inline auto enable_safe() { return config::level() == assert_level::safe; }

        QCX_ALWAYS_INLINE inline auto enable_normal()
        {
            return config::enable_safe() || config::level() == assert_level::normal;
        }

        QCX_ALWAYS_INLINE inline auto enable_fast()
        {
            return config::enable_normal() || config::level() == assert_level::fast;
        }

        [[noreturn]] QCX_NOINLINE inline auto assertion_handler(assert_info const& info)
        {
            qcx::assert::abort_assert_handler(info);
        }

        QCX_ALWAYS_INLINE inline auto get_source_location(QCX_ASSERT_INTERNAL_SOURCE_LOCATION loc)
        {
            return qcx::assert::source_location(loc);
        }

        QCX_ALWAYS_INLINE inline auto get_assert_info(
            std::string_view assertion_content, std::string_view message, qcx::assert::source_location loc)
        {
            return qcx::assert::assert_info{
                .assertion_contents = assertion_content,
                .message = message,
                .source_info = loc,
            };
        }
    }
}

#endif // QCX_ASSERT_CONFIG_HPP
