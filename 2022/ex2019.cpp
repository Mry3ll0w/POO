#include <iostream>
#include <algorithm>//PARA MCD
#include <iomanip>
#include <numeric>


/* -------------------------------------------------------------------------- */
/*                                 EJERCICIO 1                                */
/* -------------------------------------------------------------------------- */
class racional{
    std::pair<int,int>r;
public:
    racional(int n=0, int d=1){

        if (d==0)
        {
            throw std::runtime_error("El denominador del racional no puede ser 0");
        }
        
        int mcd = std::gcd(n,d);
        r.first=n/mcd;
        r.second=d/mcd;
        
    }

    racional(const racional& a):r(a.r){}
    
   
    
    racional operator=(const int& num){
        r.first=num;
        r.second=1;
        return *this;
    }

    void muestra_racional(){std::cout<<r.first<<"/"<<r.second<<std::endl;}

    /* ------------------------------- apartado c ------------------------------- */
    void inv(){
        std::swap(r.first,r.second);
    }

    racional operator++(int){
    
        r.first+=r.second;
        int mcd = std::gcd(r.first,r.second);
        r.first/=mcd;
        r.second/=mcd;
        return *this;
    }
    
    racional& operator++(){//PREINCREMENTO
        r.first+=r.second;
        int mcd = std::gcd(r.first,r.second);
        r.first/=mcd;
        r.second/=mcd;
        return *this;
    }

    racional& operator--(){
        r.first-=r.second;
        int mcd = std::gcd(r.first,r.second);
        r.first/=mcd;
        r.second/=mcd;
        return *this;
    }

    racional operator--(int){//POST DECREMENTO
        r.first-=r.second;
        int mcd = std::gcd(r.first,r.second);
        r.first/=mcd;
        r.second/=mcd;
        return *this;
    }
    
    const int& numerador()const{return r.first;}
    const int& denominador()const{return r.second;}

};

racional operator + (const racional& a, const racional& b){
    
    int mcm = std::lcm(a.denominador(),b.denominador());

    return racional(
        (a.numerador()*mcm)+b.numerador()*mcm,b.denominador()*mcm
    );

}


/* -------------------------------------------------------------------------- */
/*                                    MAIN                                    */
/* -------------------------------------------------------------------------- */

class Doble
{
public:

	Doble(double d_=0.0):d(d_){}
	//operator double(){return d;}
	operator double()const{return d;}
private:
	double d;
};

int main()
{
	double a=1.5 ,  b=10.5;
	Doble c = 5.25, d = c;

	std::cout<<c/d*b+b*c/b+b/c<<std::endl;
	d=a=b+=c;
	std::cout<<d<<' '<<a<<' '<<b<<' '<<c<<std::endl;

}
