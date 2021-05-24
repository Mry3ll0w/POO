#include <iostream>
using namespace std;//Avoid using std:: ....

class a {
    int x;
    public:
        a(){cout<<"ctor de a"<<endl;}
        void f(){cout<<"f() de a"<<endl;}
};
class b:virtual public a{
    int x;
    public:
        b(){cout<<"ctor de b"<<endl;}
        void f(){cout<<"f() de b"<<endl;}
};
class c:virtual public a{
    int x;
    public:
        c(){cout<<"ctor de c"<<endl;}
        void f(){cout<<"f() de b"<<endl;}
};
class D:public b,public c{
    int x;
    public:
        D(){cout<<"ctor de d"<<endl;}
};

int main(){
    a *pa;
    b *pb;
    D d,*pd;

    pd = &d;

    pa= &d;
    pa->f();

    pb=&d;
    pb->f();

    pd = (D*)pb;
    pd->b::f();
    d.c::f();

    return 0;
}