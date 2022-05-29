#include <iostream>


int main(){

return 0;
}

//Ejercicio 1
class B {
public:
	virtual void f()=0;//1 Definición del método virtual
};

class D :public C{

public:
	void f(){std::cout<<"D::f()"<<std::endl;}

};

//b) La clase B se llama interfaz, ya que solo sirve para definir clases que tengan que tener 
//ciertos métodos
//C) 
void metodo_ej1(){
	B b, *bp; // Falla ya que no se puede instanciar objetos de B
	D d;

	bp = &d;
	bp->f();
}