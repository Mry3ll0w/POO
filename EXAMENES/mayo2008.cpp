#include <iostream>
#include <set>
#include <map>

void ej2();
int main(){
    /* Ejercicio 1 ==> Diagrama */
    class A;class B; class C; 
    class D; class E; class F;
    class A{
    };
    class B:public A{
        
    };
    class D{
        B* rel3;
    };
    class E:public A{
        std::set<D*>rel5;
    };
    class C{
        D* rel4;
    };
    class F:public C, public E{};
    return 0;
}

void ej2(){
    using namespace std;
    class X{
        public:
            X(string s="por omision"){
                cout<<"ctor x"<<endl;
            }
    };
    class A{
        X x;
        public:
            A():x("A"){cout<<"ctor de A"<<endl;}
            void f(){cout<<"metodo f de a"<<endl;}
    };
    class B:virtual public A{
        X x;
        public:
            B(){cout<<"ctor de B"<<endl;}
            void f(){cout<<"f de B"<<endl;}
    };
    class C:virtual public A{
        X x;
        public:
            C(){cout<<"ctor de C"<<endl;}
            void f(){cout<<"f de c"<<endl;}
    };
    class D: public B,public C{
        X x;
        public:
        D():x("D"){cout<<"ctor de D"<<endl;}
    };
    /*
        a) Cuantos atributos y cuantos 
            metodos tiene clase D?
            Tiene los metodos de a,b,c,d
        b) Hay algun miembro duplicado?
            Hay duplicados 2 x (B::X y C::X), el resto no
            ya que la herencia es virtual
        c) Como se accede a cada uno de los miembros?
            Pereza
    */

}