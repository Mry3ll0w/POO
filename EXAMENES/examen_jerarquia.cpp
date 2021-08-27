#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
/*EJERCICIO 4
Implementa una jerarquía de clases con herencia. 

APARTADO a)
Las clase padre es Vehículo con un string que representa la fecha de fabricación del coche y sus hijas, 
Turismo y Camion
Turismo tiene un int que representa el maxPasajeros
Camion tiene un int que representa el pesoMax

La herencia debe ser disjoint y con participación total, o sea que no pueden existir objetos Vehículo

La clase Vehículo tiene un metodo mostrarVehiculo() que imprime la información específica del vehículo y cada 
clase tiene un observador para cada atributo

APARTADO b)
Hacer la función ordenaVehiculos(), que recibe 3 vectores y no devuelve nada

-Un vector de punteros a Vehículo
-Un vector de punteros a Camión
-Un vector de punteros a Turismo

Los dos últimos vectores deben ser vacíos y pasados por referencia

La función debe guardar cada puntero en función al objeto que apunta. 
Si apunta a un objeto Camión, lo guarda en el vector de Camión
*/
class vehiculo{
public:
    vehiculo(std::string s):fecha_fabricacion(s){}
    virtual void mostrarVehiculo()=0;
    std::string const f_fab()const{return fecha_fabricacion;}
protected:
    std::string fecha_fabricacion; 
};
class camion :vehiculo{
    int maxPasajeros;
public:
    const int max_pasajeros()const{return maxPasajeros;}
    camion(std::string f, int pas):vehiculo(f),maxPasajeros(pas){}
    void mostrarVehiculo(){
        std::cout<<"Matricula: "<<f_fab()<<std::endl;
        std::cout<<"Max Pasajeros: "<<maxPasajeros<<std::endl;
    }
};

class turismo: public vehiculo{
    double maxpeso;
public:
    turismo(std::string f, double p):vehiculo(f),maxpeso(p){}
    const double maxPeso()const{return maxpeso;}
    void mostrarVehiculo(){
        std::cout<<"Matricula: "<<f_fab()<<std::endl;
        std::cout<<"Max Peso: "<<maxpeso<<std::endl;
    }
};
/* ------------------------------- apartado b ------------------------------- */
void ordenarVehiculos(std::vector<vehiculo*> vv, std::vector<turismo*>& vt, std::vector<camion*>& vc)
{
    if( !vt.empty() || ! vc.empty() ){ //Si los vectores contenedores de camion y turismo estan vacios
        for(size_t i = 0; i != vv.size(); ++i){
            if (turismo* t = dynamic_cast<turismo*>(vv[i])) //si puede hacer el dynamic cast es de tipo turismo
                vt.insert(vt.end(), t);
            else if (camion* c = dynamic_cast<camion*>(vv[i]))//si puede hacer el dynamic cast es de tipo camion 
                vc.insert(vc.end(), c);
        }
    }
}

/* ------------------------------ MAIN PRUEBAS ------------------------------ */
int main(){
    

}