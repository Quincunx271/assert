#include <iostream>
#include <stdexcept>

#include <qcx/assert.hpp>

void run_assert_test();

int main()
{
    qcx::register_assert_handler(qcx::throw_handler);
    try {
        run_assert_test();
    } catch (std::logic_error const&) {
        std::cout << "logic_error";
    }
}
