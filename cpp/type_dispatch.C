
#include <string>
#include <iostream>
#include <initializer_list>

using std::string;
using std::cout;
using std::cerr;
using std::endl;


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


// static id -> type lookup table
template<int T> struct Type {};
template<> struct Type<BOO> { typedef Boo t; };
template<> struct Type<BAA> { typedef Baa t; };


// stateless body
template<class Body>
inline void switch_ (int i)
{
    switch (i) {
        case BOO: { Body::case_((Boo *) NULL); } break;
        case BAA: { Body::case_((Baa *) NULL); } break;
        default:
            cerr << "Unknown case: " << i << endl;
    }
}

// stateful body
template<class Body>
inline void switch_ (int i, Body body)
{
    switch (i) {
        case BOO: { body.Body::case_((Boo *) NULL); } break;
        case BAA: { body.Body::case_((Baa *) NULL); } break;
        default:
            cerr << "Unknown case: " << i << endl;
    }
}


struct TestBody
{
    int ii;

    template<class type>
    void case_ (type *)
    {
        cout << "ii = " << ii << ", name = " << type::name << endl;
    }
};

struct TestBody2
{
    template<class type>
    static void case_ (type *)
    {
        cout << "name = " << type::name << endl;
    }
};


int main ()
{
    for (int i = 0; i < type_count; ++i) {
        TestBody body = {i * i};
        switch_(i, body);
    }

    for (int i = 0; i < type_count; ++i) {
        switch_<TestBody2>(i);
    }

    return 0;
}

