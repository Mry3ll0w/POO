#include <iostream>
#include <climits>
#include <string>
class Binario {
    static const size_t bits_elto = CHAR_BIT * sizeof(unsigned);
    size_t n, m;
    unsigned * bits;
public:
    Binario (const int& n =1):bits(new unsigned [n]){
        
        for(size_t i=0; i<n; i++)
            bits[i] = 0;
        
        m = (n+ bits_elto)/bits_elto;
        
    };
    Binario(Binario&& other){
        n = other.n;
        m = other.m;
        
        delete []bits;//Borramos bits para volver a reasignarlo
        bits = new unsigned [n];
        for(size_t i=0; i<n; i++)
            bits[i] = other.bits[i];
        
        other.~Binario();//Destruimos el objeto que se pasa al constructor de movimiento
    }
    ~Binario(){
        delete []bits;
    }
    Binario(Binario& other){
        n = other.n;
        m = other.m;
        
        delete []bits;//Borramos bits para volver a reasignarlo
        bits = new unsigned [n];
        for(size_t i=0; i<n; i++)
            bits[i] = other.bits[i];
    }
    Binario operator =(const Binario other){//Para que pueda hacer b1 = objeto
        n = other.n;
        m = other.m;
        
        delete []bits;//Borramos bits para volver a reasignarlo
        bits = new unsigned [n];
        for(size_t i=0; i<n; i++)
            bits[i] = other.bits[i];
        
        return *(this);
    }

    const Binario operator ~(){
        //Cambiamos el numero de bits 0 a 1 ;
        Binario t(n);//Creamos una copia del mismo
        for(int i=0; i<t.n; i++)
            t.bits[i] = 1;//Todos a 1, segun lo que pide el enunciado
        
        return t ;
    } 
};

using namespace std;//Avoid using std:: ....

int main(){
    Binario b1(12), b2;
    b1 = ~b2;
    b2 = move(b1);
return 0;
}