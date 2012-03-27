
#include <iostream>

struct Version
{
    uint8_t a,b,c,d;
    uint32_t num () const { return a << 24 | b << 16 | c << 8 | d; }
};

int main ()
{
    Version v1 = {0,1,2,3};
    std::cout << "Version(0,1,2,3).num() = " << v1.num() << std::endl;

    Version v2 = {3,2,1,0};
    std::cout << "Version(3,2,1,0).num() = " << v2.num() << std::endl;

    return 0;
}

