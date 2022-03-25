#include <iostream>
using namespace std;
template	<class	T1,	class	T2>
class par
{
public:
        par():prime(T1()),segun(T2()){}
        par(const	T1&	x,	const	T2&	y)	:	prime(x),	segun(y)	{}
        T1	primero()	const	{	return	prime;	}
        T2	segundo()	const	{	return	segun;	}
        T1&	primero()	{	return	prime;	}
        T2&	segundo()	{	return	segun;	}
        
    private:
        T1	prime;
        T2	segun;
};
/* 
    a) Sobrecargue	operator	<<	para	la	plantilla	de	clase	par

    b)  Defina	un	tipo	racional	a	partir	de	ella	para	representar	
        números	racionales	con	el	signo	en	el	numerador.
        Sobrecargue	el	operador	de	suma	de	números	racionales.

    c) Defina	una	clase	complejo con	partes	real	e	imaginaria	de	tipo double.	Sobrecargue	el	operador	de	
        autosuma	(+=)	de	números	complejos */
//a 
template <class T1,class T2>       
ostream& operator <<(ostream& os, par<T1,T2>& parxy){
    os<<parxy.primero()<<" "<<parxy.segundo();
    return os;
}
//b)
class racional{
    par<double,double>r;
    public:
    racional(const double& i,const double& j){r.primero()= i;r.segundo()=j;}
    double denominador(){return r.primero();}
    double numerador(){return r.segundo();}
    ~racional()=default;
    
};
racional operator + (racional& a,racional& b){
    return racional (a.numerador()+b.numerador(),a.denominador()+b.denominador());
}
//apartado c
class complejo{
    par<double,double>num;
    public:
    complejo(const double& a,const double& b){num.primero()=a;num.segundo()=b;}
    ~complejo()=default;
    double& imag(){return num.primero();}
    double& real(){return num.segundo();}
    complejo operator +=(complejo& c){
        num.primero()+=c.imag();
        num.segundo()+=c.real();
        return *this;
    }
};

int main(){
    par<int,int> p(1,2);
    cout<<p<<endl;
    return 0;
}

