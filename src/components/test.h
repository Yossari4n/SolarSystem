#ifndef test_hpp
#define test_hpp

#include <iostream>

#include "IComponent.h"

class Test : public IComponent {
public:
    
    Test(int a, float b, bool c) : a(a), b(b), c(c) {}
    
    void Update() override {
        a++;
        std::cout << a << '\n';
    }
    
    int a;
    float b;
    bool c;
};

#endif
