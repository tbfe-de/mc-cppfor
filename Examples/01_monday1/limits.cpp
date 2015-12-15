#include <cstdint>
#include <limits>
#include <iostream>

int main() {
    std::cout.setf(std::ios::boolalpha);
    std::cout << static_cast<int>(std::numeric_limits<std::int_least8_t>::min()) << " .. "
              << static_cast<int>(std::numeric_limits<std::int_least8_t>::max()) << '\n';
    std::cout << static_cast<int>(std::numeric_limits<std::int_fast8_t>::min()) << " .. "
              << static_cast<int>(std::numeric_limits<std::int_fast8_t>::max()) << '\n';
    std::cout << std::numeric_limits<std::int_least16_t>::min() << " .. "
              << std::numeric_limits<std::int_least16_t>::max() << '\n';
    std::cout << std::numeric_limits<std::int_fast16_t>::min() << " .. "
              << std::numeric_limits<std::int_fast16_t>::max() << '\n';
    std::cout << static_cast<bool>(static_cast<void*>(0)) << '\n';
}
