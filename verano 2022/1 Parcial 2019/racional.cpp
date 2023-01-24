#include <iostream>
#include <vector>
#include <numeric>//MCD y MCM
using namespace std;//Avoid using std:: ....

class racional{
    int n, d;
public:

    racional(int n_ = 0, int d_ = 1):n(n_), d(d_){
        
        if (d == 0)
        {
            throw invalid_argument("El denominador no debe ser 0");
        }

        //Reducimos el numero al irreducible 
        int mcd = gcd(n, d);
        n /= mcd;
        d /= mcd;

        //Lo dejamos en forma canónica
        if(n < 0 && d < 0){
            n *= -1;
            d *= -1;
        }
        else if (d < 0)
            d *= -1;
            n *= -1;
        
    }

    //Solo será necesario el constructor pq el resto son usables por el predeterminado

    const int& get_n()const{
        return n;
    }
    int& get_n(){
        return n;
    }

    int& get_d(){return d;}
    const int& get_d()const{return d;}

    const racional inv()const{
        return racional(d,n);
    }

    bool operator ==(const racional& other){
        return other.n == n && other.d == d;
    }

    bool operator != (const racional& other){
        return !(*this == other);
    }

    bool operator < (const racional& other){
        return (n/d) < (other.n/other.d);
    }

    bool operator > (const racional& other){
        return (n/d) > (other.n/other.d);
    }

    bool operator >= (const racional& other){
        return !(*this < other );
    }

    bool operator <= (const racional& other){
        return !(*this > other);
    }

    racional operator + (const racional& other){
        
        int mcm = lcm(other.d , d);
        
        return racional(n*mcm + other.n*mcm, d*mcm);

    }

    racional operator * (const racional& other){
        return racional(n*other.n, d* other.d);
    }

    racional operator / (const racional & other){
        
        return racional(n * other.inv().n, d* other.inv().d);
        
    }

};



ostream& operator <<(ostream& os , const racional& r){
    os << r.get_n() << "/" << r.get_d() <<endl;
    return os;
}

int main(){
    racional r(0,1), s, t{4,-8},u(3), v=5;
    cout << t <<endl;
    racional l(t);
    cout << l <<endl;

    
return 0;
}