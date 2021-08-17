#include <iostream>
class B{
    public:
    virtual void f(){std::cout<<"f de B"<<std::endl;}
    B()=default;
    ~B()=default;
};
class D: public B{
    public:
    void f(){std::cout<<"f de D"<<std::endl;}
    D()=default;
    ~D()=default;
};

int main(){
B b, *bp;
D d, *dp;
bp = &d;
bp->f();
dp = &b;
dp->f();
dp = &d;
dp->f();
}