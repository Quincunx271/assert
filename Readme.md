## Overview

*Qcx/Assert* is a small header-only library providing more fine grained control over
the `assert` found in `<cassert>`. With regular `assert()`, you have to turn
them *all* on or off, but sometimes you want to have an assertion in the release
executable because it's cheap or critical to the application. Sometimes you
might want to have an expensive assertion for those debugging sessions that you
need to verify your invariants stayed invariant. This is where *Assert* comes
in.

Note: This library may still make drastic backwards-incompatible changes. It's
not at the 1.0 stage yet.

## Requirements

This is a C++20 library.

## Example

```cpp
// header file
#include <qcx/assert.hpp>

class MyClass {
    // ...
public:
    void set_data(int data)
    {
        QCX_ASSERT_SAFE(data != 42);
        this->data = data;
    }

    Result do_computation(Argument arg) const;
};

// source file
Result MyClass::do_computation(Argument arg) const
{
    QCX_ASSERT_MSG("Argument must be valid because ...", arg.is_valid());
    // ...
}
```

## Rules of thumb

* Use `QCX_ASSERT_FAST` almost never. It's for those critical moments, or when
  the assertion time would be unnoticeable.
* Use `QCX_ASSERT` in source files. It's for assertions that you wouldn't
  necessarily want on in production.
* Use `QCX_ASSERT_SAFE` for inline functions, where the amount of work checking
  for the assertion is significant compared to the rest of the work of the
  function. You might also want to use this in a source file for doing
  expensive checks.
* Use the `_MSG` variant if you want to have an additional message in the
  assertion error.

## Configuration

*Qcx/Assert* is made to be highly configurable under the tweak headers method
from [vector-of-bool's blog post][vob-tweak].

By default, only `QCX_ASSERT_FAST` and `QCX_ASSERT` assertion variants are on,
with the `QCX_ASSERT` variants turning off for `NDEBUG` in the same manner as
`assert()`.

To configure, make a tweak header with the filename **qcx-assert.tweaks.hpp**.
Inside that header, you may `#include` files from the `qcx/assert/config`
directory only.

### Setting Assertion Level

```c++
#include <qcx/assert/config/assert_level.hpp>

namespace qcx::assert::config {
    constexpr auto level() { return assert_level::normal; } // or ::fast or ::safe
}

// OR:
namespace qcx::assert::config {
    constexpr bool enable_safe() { return true; } // implies enable_normal() and enable_fast()
    // Explicit is allowed:
    constexpr bool enable_fast() { return false; }
    constexpr bool enable_normal() { return true; }
}
```

Runtime configuration is legal:

```c++
qcx::assert::assert_level_e level = qcx::assert::assert_level::fast;

namespace qcx::assert::config {
    assert_level_e level() { return ::level; }
    // assigning `level` chooses the assertion level
}

// OR:
namespace qcx::assert::config {
    bool enable_safe() { return std::getenv("SAFE_ASSERTS"); }
    bool enable_fast() { return std::getenv("FAST_ASSERTS"); }
    bool enable_normal() { return std::getenv("NORMAL_ASSERTS"); }
}
```

### Configuring the Assertion Handler

```c++
#include <qcx/assert/config/handler.hpp>

namespace qcx::assert::config {
    // The function _must_ not return; it is undefined behavior if it does.
    [[noreturn]] void assertion_handler(assert_info const& info);
}
```

See `qcx::assert::abort_assert_handler(...)` in **qcx/assert/config/handler.hpp** for
an example assertion_handler (it is the default handler).

### Customizing Source Information

```c++
#include <qcx/assert/config/attributes.hpp> // For QCX_ALWAYS_INLINE
#include <qcx/assert/config/handler.hpp>

namespace qcx::assert::config {
    QCX_ALWAYS_INLINE inline auto get_source_location(std::source_location loc)
    {
        // Removes all source information
        return qcx::assert::source_location();
    }

    QCX_ALWAYS_INLINE inline auto get_assert_info(
        std::string_view assertion_content, std::string_view message, qcx::assert::source_location loc)
    {
        // You can change the assertion_content and source_info here as well
        return qcx::assert::assert_info{
            .assertion_contents = assertion_content,
            .message = message,
            .source_info = loc,
        };
    }
}
```

## Acknowledgements

Bloomberg's `BSLS_ASSERT` from [the BDE][bde] is the inspiration for this library. This is basically a clone of that idea, which was shared in a cppcon 2014 talk.

  [bde]: https://github.com/bloomberg/bde
  [vob-tweak]: https://vector-of-bool.github.io/2020/10/04/lib-configuration.html
