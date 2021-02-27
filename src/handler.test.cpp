#include <qcx/assert/config/handler.hpp>

#include <string>

#include <catch2/catch.hpp>

TEST_CASE("position_str can convert to string_view")
{
    std::uint_least32_t x = GENERATE(values<std::uint_least32_t>({0, 1, (std::uint_least32_t)-1}));

    qcx::assert::position_str x_str(x);
    CHECK(x_str.str_view() == std::to_string(x));
}

TEST_CASE("form_default_assert_message works without a message")
{
    qcx::assert::source_location info;
    info.line = 183;
    info.function_name = "void function(int)";
    info.file_name = "doohicky.cpp";

    qcx::assert::assert_info assert_info = {
        .assertion_contents = "(x + y) == z",
        .message = "",
        .source_info = info,
    };

    auto const message = qcx::assert::form_default_assert_message(assert_info);

    using Catch::Matchers::Contains;

    CHECK_THAT(message, Contains(std::string(info.function_name)));
    CHECK_THAT(message, Contains(std::string(info.file_name)));
    CHECK_THAT(message, Contains(std::to_string(info.line)));
    CHECK_THAT(message, Contains(std::string(assert_info.assertion_contents)));
    CHECK_THAT(message, !Contains("message"));
}

TEST_CASE("form_default_assert_message works with a message")
{
    qcx::assert::source_location info;
    info.line = 183;
    info.function_name = "void function(int)";
    info.file_name = "doohicky.cpp";

    qcx::assert::assert_info assert_info = {
        .assertion_contents = "(x + y) == z",
        .message = "point not on correct line",
        .source_info = info,
    };

    auto const message = qcx::assert::form_default_assert_message(assert_info);

    using Catch::Matchers::Contains;

    CHECK_THAT(message, Contains(std::string(info.function_name)));
    CHECK_THAT(message, Contains(std::string(info.file_name)));
    CHECK_THAT(message, Contains(std::to_string(info.line)));
    CHECK_THAT(message, Contains(std::string(assert_info.assertion_contents)));
    CHECK_THAT(message, Contains("message"));
    CHECK_THAT(message, Contains(std::string(assert_info.message)));
}
