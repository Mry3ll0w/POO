#include <iostream>
#include <set>
#include <map>

void f();
int main(){
     f();
     return 0;
}

class a; class b; class c; class d;

class a{
};
class b:public a{
};
class e:public a{
     private:
          std::set<d*>rel5;
};
class d{
     b* rel3;
};

class c{
     std::set<d>rel4;
};
class f:public c,public e{};

/**
 * EJ2 
 *   clase x ==> ctor
 *   class a==> atributo X , ctor, metodo f
 *   class b==> atr X ,hereda virtual a, ctor b, f()
 *   class c==>  atr X ,hereda virtual a, ctor c, f()
 *   class d==> HEREDA b y c, atr x, ctor X
 * 
 * 
 *a) Cuantos atributos y metodos tiene D
     4 atr= D::X, D::B::X, D::C::X, D::B::A::X
 */
using namespace std; 
class X 
{ 
public: 
 X(string s = "por omisi´on") { cout << "Constructor de X: " << 
s << endl; } 
}; 
class A 
{ 
 X x; 
public: 
 A() : x("A") { cout << "Constructor de A" << endl; } 
 void f() { cout << "M´etodo f() de A" << endl; } 
}; 

class B : virtual public A 
{ 
 X x; 
public: 
 B() { cout << "Constructor de B" << endl; } 
 void f() { cout << "M´etodo f() de B" << endl; } 
}; 
class C : virtual public A 
{ 
 X x; 
public: 
 C() { cout << "Constructor de C" << endl; } 
 void f() { cout << "M´etodo f() de C" << endl; } 
}; 
class D : public B, public C 
{ 
 X x; 
public: 
 D() : x("D") { cout << "Constructor de D" << endl; } 
};
 
void f() 
{ 
     A    *pa; 
     B *pb; 
     D d, *pd; 
     pd = &d; 

     pa = &d; 
     pa-> f(); 
     pb = &d; 
     pb-> f(); 
     d = *pa; 
     pd = (D *)pb; 
     pd-> B::f(); 
     d.C::f(); 
}