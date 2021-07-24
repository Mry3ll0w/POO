#include <iostream>
class C {
    public:
        C(int i = 0): n(i) {}
        void mostrar() { std::cout << "i␣=␣" << n << std::endl; }
        
    private:
        int n;
        static int ej;
};
//TAREA 2.2
class Libro1{
    std::string titulo_;
    int pags_;
    public:
        Libro1(std::string t="",int p=0);
        void print(){std::cout<<titulo_<<std::endl;}
};

class Libro2{
    std::string titulo_;int pags_;
    public:
        Libro2(std::string t,int p=0);
        Libro2(const char * c);
        void print(){std::cout<<titulo_<<std::endl;}
};

int main() { 
    /* TAREA 2.1 by @Mry3ll0w
    const C c; 
    //c.mostrar(); 
    C a,b;
    */ 
    //Libro1* lib = new Libro1("EL quijote"); 
    Libro2* l2 = new Libro2("EL quijote"); 
    l2->print();
    
}
