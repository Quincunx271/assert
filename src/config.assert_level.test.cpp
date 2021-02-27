#include <qcx/assert/config/assert_level.hpp>

#include <catch2/catch.hpp>

namespace assert_level = qcx::assert::config::assert_level;

TEST_CASE("assert level equality is correct")
{
    STATIC_REQUIRE(assert_level::off == assert_level::off);
    STATIC_REQUIRE_FALSE(assert_level::off != assert_level::off);
    STATIC_REQUIRE(assert_level::off != assert_level::fast);
    STATIC_REQUIRE_FALSE(assert_level::off == assert_level::fast);
    STATIC_REQUIRE(assert_level::off != assert_level::normal);
    STATIC_REQUIRE_FALSE(assert_level::off == assert_level::normal);
    STATIC_REQUIRE(assert_level::off != assert_level::safe);
    STATIC_REQUIRE_FALSE(assert_level::off == assert_level::safe);

    STATIC_REQUIRE(assert_level::fast == assert_level::fast);
    STATIC_REQUIRE_FALSE(assert_level::fast != assert_level::fast);
    STATIC_REQUIRE(assert_level::fast != assert_level::off);
    STATIC_REQUIRE_FALSE(assert_level::fast == assert_level::off);
    STATIC_REQUIRE(assert_level::fast != assert_level::normal);
    STATIC_REQUIRE_FALSE(assert_level::fast == assert_level::normal);
    STATIC_REQUIRE(assert_level::fast != assert_level::safe);
    STATIC_REQUIRE_FALSE(assert_level::fast == assert_level::safe);

    STATIC_REQUIRE(assert_level::normal == assert_level::normal);
    STATIC_REQUIRE_FALSE(assert_level::normal != assert_level::normal);
    STATIC_REQUIRE(assert_level::normal != assert_level::off);
    STATIC_REQUIRE_FALSE(assert_level::normal == assert_level::off);
    STATIC_REQUIRE(assert_level::normal != assert_level::fast);
    STATIC_REQUIRE_FALSE(assert_level::normal == assert_level::fast);
    STATIC_REQUIRE(assert_level::normal != assert_level::safe);
    STATIC_REQUIRE_FALSE(assert_level::normal == assert_level::safe);

    STATIC_REQUIRE(assert_level::safe == assert_level::safe);
    STATIC_REQUIRE_FALSE(assert_level::safe != assert_level::safe);
    STATIC_REQUIRE(assert_level::safe != assert_level::off);
    STATIC_REQUIRE_FALSE(assert_level::safe == assert_level::off);
    STATIC_REQUIRE(assert_level::safe != assert_level::fast);
    STATIC_REQUIRE_FALSE(assert_level::safe == assert_level::fast);
    STATIC_REQUIRE(assert_level::safe != assert_level::normal);
    STATIC_REQUIRE_FALSE(assert_level::safe == assert_level::normal);
}
