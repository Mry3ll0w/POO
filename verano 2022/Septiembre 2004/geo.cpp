#include <iostream>

using namespace std;//Avoid using std:: ....

class Elipse{
    double rx, ry;
public:
    void escalar(size_t i , size_t j){
        rx *=i;
        ry *=j;
    }
    virtual void dibujar()= 0;
    Elipse(const double& x=0, const double& y=0):rx(x),ry(y){}
    double& radio_x() {return rx;}
    double& radio_y() {return ry;}


};

/**
 * La relacion entre elipse y circunferencia es que la circunferencia es una especializacion
 * de la clase elipse, ya que tiene los mismos metodos y la diferencia reside en que ambos 
 * radios son iguales.
 * 
 * En el apartado 2 se dice que las figuras planas son abstracciones de elipses y ademas todas
 * las figuras planas constan de un metodo dibujar que le permite variar su escala.
 * Al tratarse de figuras geometricas el metodo dibujar no puede ser iguales en todas, por tanto
 * definimos este como metodo virtual puro, para obligar a las clases que hereden de elipse que 
 * implementen el mismo según su necesidad.
 * Quedando de la siguiente forma:
 * 
 */
class circunferencia: public Elipse{
public:
    circunferencia(const double& r = 0):Elipse(r,r){}
    void dibujar(){}
};

class figura_plana:public Elipse{
    void dibujar(){}
};

int main(){
    
return 0;
}