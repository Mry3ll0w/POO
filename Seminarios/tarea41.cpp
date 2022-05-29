#include <iostream>

using namespace std;

//Ejercicio 1
void mostrar(int i) { cout << i << "␣[entero]" << endl; }
void mostrar(float f) { cout << f << "␣[real]" << endl; }

//Ejercicio 2
void f(char){};
void f(double){};
void f(void *){};

/*
//Ejercicio 3 (clases necesarias para que se pueda comprobar)
class B{
public:
	virtual void f(){std::cout<<"B::f()"<<std::endl;}
};

class D: public B{
public:
	void f(){std::cout<<"D::f()"<<std::endl;}
};
*/
//Ejercicio 4
struct B {
B() { std::cout << "Constructor de B\n"; }
 	virtual ~B() { std::cout << "Destructor de B\n"; }
};
struct D: B {
	D() { std::cout << "Constructor de D\n"; }
 	~D() { std::cout << "Destructor de D\n"; }
};

//Ejercicio 6

//¿Cambiaría el comportamiento de la clase cuadrado si le quitamos el
//miembro area()? No ya que sirven ambos metedos, ya que se calculan de la misma forma

class rectangulo {
public:
	rectangulo(double a, double l): ancho(a), largo(l) {}
	virtual double area() { return ancho * largo; }
	virtual ~rectangulo() = default;
private:
	double ancho, largo;
};

class cuadrado: public rectangulo {
public:
	cuadrado (double l): rectangulo(l, l) {}
	double area() {return rectangulo::area();}
};


int main(){
/*
	//Ejercicio 1
	mostrar(2);//Funciona, mostrar(int)
	mostrar(2.0);//Error de ambiguedad ya que puede entrar tanto en int como en float
	mostrar('a');//Mostrar(int), se convierte de char a int

	//Ejercicio 2
	f(0.0);//f(double)
 	f(0);//f(Char)
 	f(0.0f);//Ambiguedad, puede entrar en void* o en double
 	f("Hola");//f(void*)

 	//Ejercicio 3
	B b, *bp;
 	D d, *dp;
	bp = &d;
	bp->f();//Si es virtual llama a d::f(), si no al ser un puntero de tipo B, llama a B::f()
 	//dp = &b; ya que b no puede convertirse de un tipo b a uno d.
 	dp->f();//Virtual(suponiendo que la linea 43 es cirrecta)==> b::f(), no virtual==> d::f() 
 	dp = &d;
 	dp->f();//Virtual y no virtual ==> d::f()
*/
	//Ejercicio 4
	B *pb = new D; //Constructor de B, Constructor de D
	delete pb;// Destructor de D y Destructor de B
	//Si no definimos el destructor como virtual entonces nos queda mal destruido el objeto, ya que 
	//se destruye la parte de B y no la de D, ya que queda inaccesible
	
	cuadrado c(4);
	std::cout<<c.area()<<std::endl;

	return 0;
}

//Ejercicio 5
/*
//¿Qué destructores son virtuales?
class A { public: ~A(); };
class B : public A { public: virtual ~B(); };
class C : public B { public: virtual ~C(); };
class D : public C { public: ~D(); };

	Son Virtual B, C, D
*/


