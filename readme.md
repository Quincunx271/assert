[![Build Status](https://travis-ci.org/Quincunx271/assert.svg?branch=develop)](https://travis-ci.org/Quincunx271/assert)

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
        QCX_ASSERT_SAFE(data != 42);
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
* Use `QCX_ASSERT_SAFE` for inline functions, where the amount of work checking
  for the assertion is significant compared to the rest of the work of the
  function. You might also want to use this in a source file for doing
  expensive checks.

### Choose which assertions are on

By default, only `QCX_ASSERT_FAST` and `QCX_ASSERT` assertions are on. This can
be controlled by passing preprocessor defines to your build system.

You may pass only one of the following:

* `-DQCX_TARGET_OPTIMIZED_BUILD` - only `QCX_ASSERT_FAST` assertions on
* `-DQCX_TARGET_SAFE_BUILD` - all assertions on

Or, you may instead choose to pass only one of the following:

* `-DQCX_ASSERT_LEVEL_NONE` - all assertions off
* `-DQCX_ASSERT_LEVEL_FAST` - only `QCX_ASSERT_FAST` assertions on
* `-DQCX_ASSERT_LEVEL_NORMAL` - `QCX_ASSERT_FAST` and `QCX_ASSERT` on
* `-DQCX_ASSERT_LEVEL_SAFE` - all assertions on

An assertion that is off is equivalent to `((void)0)`

Note: make sure all components are built with the same assertion setting, or
you risk violating the *One Definition Rule.*

### Customize assertion handler

The assertion handler can be customized by calling
`qcx::use_assert_handler(myHandler)`. There are 2 handlers provided:

* `qcx::abort_assert_handler` - prints the assertion message and `abort()`s
* `qcx::throw_assert_handler` - throws a `std::logic_error` with the assertion message

The function signature should be:

    [[noreturn]] void myHandler(qcx::assert_info const& message)

**Note:** This function signature is extremely likely to change in the future

It is Undefined Behavior if the handler does return.

You can also call the handlers directly, which act as a failing assertion. To 
obtain a `qcx::assert_info`, you can call `QCX_ASSERT_INFO(message)`, where
message is convertible to `std::string_view`, and one will be constructed with
the source information.

## Dependencies

This library has no dependencies.

The tests require Catch2.

## Using

To use this library after installing with *cmake*, use `find_package(QcxAssert)` and use `target_link_libraries` with `Qcx::Assert`

## Tests

To run the tests, build with *cmake* and run *ctest*.

## Acknowledgements

Bloomberg's `BSLS_ASSERT` from [the BDE][bde] is the inspiration for this library. This is basically a clone of that idea, which was shared in a cppcon 2014 talk.

  [bde]: https://github.com/bloomberg/bde
