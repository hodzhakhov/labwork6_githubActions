
#include <lib/number.h>
#include <iostream>

int main() {
    uint2022_t v = from_string("123456789");
    std::cout << v * v << std::endl;

    return 0;
}
