#include <iostream>
#include <numeric>
using namespace std;//Avoid using std:: ....

template<class T1, class T2>
class par{
protected:
    T1 prim;
    T2 segun;
public:
    par(const T1& x = T1(), const T2& y=T2()):prim(x), segun(y) {}
    T1 primero ()const {return prim;}
    T2 segundo ()const {return segun;}
    T1& primero () {return prim;}
    T2& segundo () {return segun;}

};

//Apartado a) Sobrecarga <<
template<class T1, class T2>
ostream& operator << (ostream& os, const par<T1,T2> &p){
    os<< p.primero() <<" "<< p.segundo()<< endl;
    return os;
}

//Apartado b) Crear el tipo racional como una especificación

template<class T1>
class racional : public par<T1,T1>{

public:
    
    racional(T1 a=T1(), T1 b=T1()){
        
        if(b == 0)
            throw std::invalid_argument("b tiene que ser != de 0");

        if (a > 0 && b < 0)
        {
            b *=-1;//quitamos el menor del denominador y lo ponemos en el numerador
            a *= -1;
        }
        //Lo hacemos irreducible
        int mcd = gcd(a,b);
        a /= mcd;
        b /= mcd;

        this->prim = a;
        this->segun = b;
    }

    void print (){
        cout<< this->prim<<"/"<< this->segun<<endl;
    }
    
};

template <class T>
racional<T> operator +(const racional<T>& r1, const racional<T>& r2){
    T na, nb, da, db;
    
    na = r1.primero();
    da = r1.segundo();
    
    nb = r2.primero();
    db = r2.segundo();
    if(db == da){
        return racional<T>(na+nb, da); //Llamamos al constructor para hacer la suma irreducible
    }
    else {
        int mcm = lcm(db, da);
        na *= mcm;
        nb *= mcm;
        da *= mcm;
        return racional<T>(na+nb, da);
    }
    
}

//Apartado C

class complejo : public par<double,double>{
public:
    
    complejo(double x, double i){this->prim=x;this->segun=i;}
    
    void print(){
        cout<< this->prim<< "+i"<< this->segun<< endl;
    }

    complejo& operator += (complejo& other){
        this->prim+=other.prim;
        this->segun+=other.segun;
        return *this;
    }

    complejo operator = (complejo& other){
        this->prim=other.prim;
        this->segun=other.segun;
        return *this;
    }
};



int main(){
    complejo c1(12.4,234.21), c2(2,56.12);
    c1 += c2;
    c1.print();
return 0;
}


