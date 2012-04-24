
#include <string>
#include <iostream>

using std::string;


enum TypeId
{
    BOO,
    BAA,

    type_count
};

struct Boo { static const string name; };
const string Boo::name = "boo";

struct Baa { static const string name; };
const string Baa::name = "baa";


template<int T>
struct Type {}; // abstract

template<> struct Type<BOO> { typedef Boo t; };
template<> struct Type<BAA> { typedef Baa t; };


template<class Body, int type_id>
struct TypeCase
{
    TypeCase (Body & body)
    {
        std::cerr << "Unknown case: " << type_id << std::endl;
    }
}; // abstract

template<class Body>
void type_dispatch (Body & body, int i)
{
    switch (i) {
        case BOO: { TypeCase<Body, BOO> x(body); } break;
        case BAA: { TypeCase<Body, BAA> x(body); } break;
        default:
            std::cerr << "Unknown case: " << i << std::endl;
    }
}


struct TestBody
{
    int i;
};
template<int type_id>
struct TypeCase<TestBody, type_id>
{
    TypeCase (TestBody & body)
    {
        std::cout << "id = " << body.i
            << ", name = " << Type<type_id>::t::name << std::endl;
    }
};

int main ()
{
    for (int i = 0; i < type_count; ++i) {
        TestBody body = {i};
        type_dispatch(body, i);
    }

    return 0;
}

