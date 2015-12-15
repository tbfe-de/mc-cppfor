#include <bitset>
#include <chrono>
#include <iomanip>
#include <iostream>

#define SZ 800000000

bool a[SZ];
std::bitset<SZ> b;

int main() {

    std::cout << sizeof(a) << std::endl;
    std::cout << sizeof(b) << std::endl;

    a[17] = a[34] = a[1221] = true;
    b[17] = b[34] = b[1221] = true;

    int acnt = 0, bcnt = 0;

    std::cout << "counting 'true' in native bool array..." << std::flush;
    auto start = std::chrono::high_resolution_clock::now();
    for (std::size_t idx = 0; idx < SZ; ++idx) if (a[idx]) ++acnt;
    std::cout << " = " << acnt << std::endl;
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
              << " usec" << std::endl;
    

    std::cout << "counting 'true' in bitset..." << std::flush;
    start = std::chrono::high_resolution_clock::now();
    for (std::size_t idx = 0; idx < SZ; ++idx) if (b[idx]) ++bcnt;
    std::cout << " = " << bcnt << std::endl;
    end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
              << " usec" << std::endl;
}
