#ifndef QCX_ASSERT_CONFIG_ASSERT_LEVEL_HPP
#define QCX_ASSERT_CONFIG_ASSERT_LEVEL_HPP

#include <type_traits>

namespace qcx::assert {
    template <auto V> struct val_t;

    template <bool B> struct val_t<B> : std::bool_constant<B> {
        template <bool Rhs> constexpr val_t<(B || Rhs)> operator||(val_t<Rhs>) const { return {}; }

        template <bool Rhs> constexpr val_t<(B && Rhs)> operator&&(val_t<Rhs>) const { return {}; }

        constexpr val_t<!B> operator!() const { return {}; }
    };

    template <auto V> struct val_t : std::integral_constant<decltype(V), V> {
    };

    template <auto Lhs, decltype(Lhs) Rhs> constexpr val_t<Lhs == Rhs> operator==(val_t<Lhs>, val_t<Rhs>) { return {}; }

    template <auto Lhs, decltype(Lhs) Rhs> constexpr auto operator!=(val_t<Lhs> lhs, val_t<Rhs> rhs)
    {
        return !(lhs == rhs);
    }
}

namespace qcx::assert::config {
    enum class assert_level_e {
        off,
        fast,
        normal,
        safe,
    };

    namespace assert_level {
        static constexpr auto off = qcx::assert::val_t<assert_level_e::off>{};
        static constexpr auto fast = qcx::assert::val_t<assert_level_e::fast>{};
        static constexpr auto normal = qcx::assert::val_t<assert_level_e::normal>{};
        static constexpr auto safe = qcx::assert::val_t<assert_level_e::safe>{};
    }
}

#endif // QCX_ASSERT_CONFIG_ASSERT_LEVEL_HPP
