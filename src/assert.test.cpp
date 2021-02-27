// "tweak" file:
#include <qcx/assert/config/handler.hpp>

namespace {
    bool fast_enabled = false;
    bool normal_enabled = false;
    bool safe_enabled = false;
}

namespace qcx::assert::config {
    bool enable_fast() { return fast_enabled; }
    bool enable_normal() { return normal_enabled; }
    bool enable_safe() { return safe_enabled; }

    [[noreturn]] void assertion_handler(assert_info const& info) { throw assert::form_default_assert_message(info); }
}

// Rest of the code:
#include <qcx/assert.hpp>

#include <catch2/catch.hpp>

TEST_CASE("FAST works when enabled")
{
    std::string result = "Not run";

    int line;
    auto source_loc = QCX_ASSERT_INTERNAL_SOURCE_LOCATION::current();

    try {
        fast_enabled = true;
        // clang-format off
        line = __LINE__; QCX_ASSERT_FAST(1 + 1 == 3);
        // clang-format on
    } catch (std::string const& message) {
        result = message;
    }

    using Catch::Matchers::Contains;

    CHECK_THAT(result, Contains(source_loc.file_name()));
    CHECK_THAT(result, Contains(source_loc.function_name()));
    CHECK_THAT(result, Contains(std::to_string(line)));
    CHECK_THAT(result, Contains("1 + 1 == 3"));
    CHECK_THAT(result, !Contains("message"));
}

TEST_CASE("FAST not run when disabled")
{
    std::string result = "Not run";

    try {
        fast_enabled = false;
        QCX_ASSERT_FAST(1 + 1 == 3);
    } catch (std::string const& message) {
        result = message;
    }

    CHECK(result == "Not run");
}

TEST_CASE("FAST with message works when enabled")
{
    std::string result = "Not run";

    int line;
    auto source_loc = QCX_ASSERT_INTERNAL_SOURCE_LOCATION::current();

    try {
        fast_enabled = true;
        // clang-format off
        line = __LINE__; QCX_ASSERT_FAST_MSG("Hello, World!", 1 + 1 == 3);
        // clang-format on
    } catch (std::string const& message) {
        result = message;
    }

    using Catch::Matchers::Contains;

    CHECK_THAT(result, Contains(source_loc.file_name()));
    CHECK_THAT(result, Contains(source_loc.function_name()));
    CHECK_THAT(result, Contains(std::to_string(line)));
    CHECK_THAT(result, Contains("1 + 1 == 3"));
    CHECK_THAT(result, Contains("message"));
    CHECK_THAT(result, Contains("Hello, World!"));
}

TEST_CASE("FAST with message not run when disabled")
{
    std::string result = "Not run";

    try {
        fast_enabled = false;
        QCX_ASSERT_FAST_MSG("Hello, World!", 1 + 1 == 3);
    } catch (std::string const& message) {
        result = message;
    }

    CHECK(result == "Not run");
}

// Normal

TEST_CASE("Normal works when enabled")
{
    std::string result = "Not run";

    int line;
    auto source_loc = QCX_ASSERT_INTERNAL_SOURCE_LOCATION::current();

    try {
        normal_enabled = true;
        // clang-format off
        line = __LINE__; QCX_ASSERT(1 + 1 == 3);
        // clang-format on
    } catch (std::string const& message) {
        result = message;
    }

    using Catch::Matchers::Contains;

    CHECK_THAT(result, Contains(source_loc.file_name()));
    CHECK_THAT(result, Contains(source_loc.function_name()));
    CHECK_THAT(result, Contains(std::to_string(line)));
    CHECK_THAT(result, Contains("1 + 1 == 3"));
    CHECK_THAT(result, !Contains("message"));
}

TEST_CASE("Normal not run when disabled")
{
    std::string result = "Not run";

    try {
        normal_enabled = false;
        QCX_ASSERT(1 + 1 == 3);
    } catch (std::string const& message) {
        result = message;
    }

    CHECK(result == "Not run");
}

TEST_CASE("Normal with message works when enabled")
{
    std::string result = "Not run";

    int line;
    auto source_loc = QCX_ASSERT_INTERNAL_SOURCE_LOCATION::current();

    try {
        normal_enabled = true;
        // clang-format off
        line = __LINE__; QCX_ASSERT_MSG("Hello, World!", 1 + 1 == 3);
        // clang-format on
    } catch (std::string const& message) {
        result = message;
    }

    using Catch::Matchers::Contains;

    CHECK_THAT(result, Contains(source_loc.file_name()));
    CHECK_THAT(result, Contains(source_loc.function_name()));
    CHECK_THAT(result, Contains(std::to_string(line)));
    CHECK_THAT(result, Contains("1 + 1 == 3"));
    CHECK_THAT(result, Contains("message"));
    CHECK_THAT(result, Contains("Hello, World!"));
}

TEST_CASE("Normal with message not run when disabled")
{
    std::string result = "Not run";

    try {
        normal_enabled = false;
        QCX_ASSERT_MSG("Hello, World!", 1 + 1 == 3);
    } catch (std::string const& message) {
        result = message;
    }

    CHECK(result == "Not run");
}

// SAFE

TEST_CASE("SAFE works when enabled")
{
    std::string result = "Not run";

    int line;
    auto source_loc = QCX_ASSERT_INTERNAL_SOURCE_LOCATION::current();

    try {
        safe_enabled = true;
        // clang-format off
        line = __LINE__; QCX_ASSERT_SAFE(1 + 1 == 3);
        // clang-format on
    } catch (std::string const& message) {
        result = message;
    }

    using Catch::Matchers::Contains;

    CHECK_THAT(result, Contains(source_loc.file_name()));
    CHECK_THAT(result, Contains(source_loc.function_name()));
    CHECK_THAT(result, Contains(std::to_string(line)));
    CHECK_THAT(result, Contains("1 + 1 == 3"));
    CHECK_THAT(result, !Contains("message"));
}

TEST_CASE("SAFE not run when disabled")
{
    std::string result = "Not run";

    try {
        safe_enabled = false;
        QCX_ASSERT_SAFE(1 + 1 == 3);
    } catch (std::string const& message) {
        result = message;
    }

    CHECK(result == "Not run");
}

TEST_CASE("SAFE with message works when enabled")
{
    std::string result = "Not run";

    int line;
    auto source_loc = QCX_ASSERT_INTERNAL_SOURCE_LOCATION::current();

    try {
        safe_enabled = true;
        // clang-format off
        line = __LINE__; QCX_ASSERT_SAFE_MSG("Hello, World!", 1 + 1 == 3);
        // clang-format on
    } catch (std::string const& message) {
        result = message;
    }

    using Catch::Matchers::Contains;

    CHECK_THAT(result, Contains(source_loc.file_name()));
    CHECK_THAT(result, Contains(source_loc.function_name()));
    CHECK_THAT(result, Contains(std::to_string(line)));
    CHECK_THAT(result, Contains("1 + 1 == 3"));
    CHECK_THAT(result, Contains("message"));
    CHECK_THAT(result, Contains("Hello, World!"));
}

TEST_CASE("SAFE with message not run when disabled")
{
    std::string result = "Not run";

    try {
        safe_enabled = false;
        QCX_ASSERT_SAFE_MSG("Hello, World!", 1 + 1 == 3);
    } catch (std::string const& message) {
        result = message;
    }

    CHECK(result == "Not run");
}
