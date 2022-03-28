#include <iostream>
using namespace std;//Avoid using std:: ....

class ej{
    int a;
public:
    ej(int b=1):a(b) {}
    ej(const ej& e){
        this->a=e.a;
        std::cout<<"soy el constructor de copia"<<std::endl;
    }
    ej(ej && e){
        a=e.a;
        e.a=0;
        std::cout<<"soy el constructor de movimiento"<<std::endl;
    }
    
    int elemento(){return a;}
    
};


int main(){
    ej a{45},b{std::move(a)};
    std::cout<<a.elemento()<<std::endl;
return 0;
}

