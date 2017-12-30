#include <catch.hpp>

#include <qcx/assert.hpp>

// The build system needs to have -DQCX_ASSERT_LEVEL_NORMAL

static_assert(QCX_ASSERT_FAST_ACTIVE);
static_assert(QCX_ASSERT_ACTIVE);
static_assert(!QCX_ASSERT_SAFE_ACTIVE);

TEST_CASE("")
{
    qcx::use_assert_handler(qcx::throw_assert_handler);

    SECTION("fast assert")
    {
        REQUIRE_THROWS_AS(QCX_ASSERT_FAST(false), qcx::assertion_error);
    }
    SECTION("regular assert")
    {
        REQUIRE_THROWS_AS(QCX_ASSERT(false), qcx::assertion_error);
    }
    SECTION("safe assert")
    {
        REQUIRE_NOTHROW(QCX_ASSERT_SAFE(false));
    }
}
