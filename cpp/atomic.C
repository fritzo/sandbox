#include <atomic>
#include <iostream>
#include <cstdint>

using namespace std;

#define INFO(TYPE) \
    cout << "sizeof(" #TYPE ") = " << sizeof(TYPE) << '\t'; \
    cout << "sizeof(atomic<" #TYPE ">) = " << sizeof(atomic<TYPE>) << endl;

int main ()
{
    INFO(bool)
    INFO(uint8_t)
    INFO(uint16_t)
    INFO(uint32_t)
    INFO(uint64_t)

    return 0;
}
