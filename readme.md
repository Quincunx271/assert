## Overview

*Assert* is a small header-only library providing more fine grained control over
the `assert` found in `<cassert>`. With regular `assert()`, you have to turn
them *all* on or off, but sometimes you want to have an assertion in the release
executable because it's cheap or critical to the application. Sometimes you
might want to have an expensive assertion for those debugging sessions that you
need to verify your invariants stayed invariant. This is where *Assert* comes
in.

Note: This library may still make drastic backwards-incompatible changes. It's
not at the 1.0 stage yet.

## Requirements

This is a C++17 library.

## Example

```cpp
// header file
#include <qcx/assert.hpp>

class MyClass {
    // ...
public:
    void set_data(int data)
    {
        QCX_ASSERT_DEBUG(data != 42);
        this->data = data;
    }

    Result do_computation(Argument arg) const;
};

// source file
Result MyClass::do_computation(Argument arg) const
{
    QCX_ASSERT(arg.is_valid());
    // ...
}
```

## How to

Rule of thumb:

* Use `QCX_ASSERT_FAST` almost never. It's for those critical moments, or when
  the assertion time would be unnoticeable.
* Use `QCX_ASSERT` in source files. It's for assertions that you wouldn't
  necessarily want on in production.
* Use `QCX_ASSERT_DEBUG` for inline functions, where the amount of work checking
  for the assertion is significant compared to the rest of the work of the
  function. You might also want to use this in a source file for doing
  expensive checks.

### Choose which assertions are on

By default, only `QCX_ASSERT_FAST` and `QCX_ASSERT` assertions are on. This can
be controlled by passing preprocessor defines to your build system.

You may pass only one of the following:

* `-DQCX_TARGET_OPTIMIZED_BUILD` - only `QCX_ASSERT_FAST` assertions on
* `-DQCX_TARGET_DEBUG_BUILD` - all assertions on

Or, you may instead choose to pass only one of the following:

* `-DQCX_ASSERT_LEVEL_NONE` - all assertions off
* `-DQCX_ASSERT_LEVEL_FAST` - only `QCX_ASSERT_FAST` assertions on
* `-DQCX_ASSERT_LEVEL_NORMAL` - `QCX_ASSERT_FAST` and `QCX_ASSERT` on
* `-DQCX_ASSERT_LEVEL_DEBUG` - all assertions on

Note: make sure all components are built with the same assertion setting, or
you risk violating the *One Definition Rule.*

### Customize assertion handler

The assertion handler can be customized by calling
`qcx::register_assertion_handler(myHandler)`. There are 2 handlers provided:

* `qcx::abort_handler` - prints the assertion message and `abort()`s
* `qcx::throw_handler` - throws a `std::logic_error` with the assertion message

The function signature should be:

    [[noreturn]] void myHandler(char const* message)

**Note:** This function signature is extremely likely to change in the future

## Dependencies

This library has no dependencies.

## Tests

To run the tests, you need to have ruby installed. Run **run_tests.rb** from
the test directory.

Note: The tests are only known to work on Windows, but they *should* be cross
platform.

## Acknowledgements

Bloomberg's `BSLS_ASSERT` from [the BDE][bde] is the inspiration for this library. This is basically a clone of that idea, which was shared in a cppcon 2014 talk.

  [bde]: https://github.com/bloomberg/bde
