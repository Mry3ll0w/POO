#include <iostream>
#include <string>
using namespace std;

class complejo{
	public:
		complejo(double r_=0,double i_=0):r(r_),i(i_){};
		complejo(const complejo& c_)=default;//Constructor de copia por defecto
		/*NO ES NECESARIO USAR CTOR DE COPIA EL PREDETERMINADO SIRVE
		complejo& operator =(double r_){
			this->r=r_;
			this->i=0;
			return *this;
		}*/ 
		friend std::ostream& operator <<(ostream& salida,const complejo& c_){
			string str = std::to_string(c_.r)+" + "+"("+std::to_string(c_.i)+")"+"i";
			salida<<str;
			return salida;
		}

		double real()const{return r;}
		double& real(){return r;}
		double& imag(){return i;}
		double imag()const{return i;}
	private:
		double r,i;
};

//Funciones de los operadores
bool operator ==(const complejo a, const complejo b){
	if ((a.real()==b.real())&& (a.imag()==b.imag()))
	{
		return true;
	}
	else{
		return false;
	}
}
bool operator!=(const complejo a, const complejo b){
	return !(a==b);
}

complejo operator *(const complejo a, const complejo b){
	complejo temp(a.real()*b.real(),a.imag()*b.imag());
	return temp;
}

complejo operator -(const complejo a, const complejo b){
	complejo temp((a.real()-b.real(),a.imag()-b.imag()));
	return temp;
}

complejo operator +(const complejo a, const complejo b){
	complejo temp((a.real()+b.real(),a.imag()+b.imag()));
	return temp;
}



int main(int argc, char const *argv[])
{
	complejo a=-3,b;
	a=a*b;
	cout<<a;
	
	return 0;
}