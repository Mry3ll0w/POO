#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>

using namespace std;//Avoid using std:: ....

//Declaracion de clases (Apartado A)
class Vehiculo{
protected:
    string matricula;
public: 
    
    virtual void MostrarVehiculo()=0;
    virtual ~Vehiculo(){}//Hay que instanciarlo en las clases base, para que no falle el compilado, simplemente con poner los {} sirve
};

class Turismo : Vehiculo {
private:
    int MaxPasajeros;
public:
    void MostrarVehiculo(){cout<<matricula<<endl;}
    const int& PasajerosMaximos()const{return MaxPasajeros;}
    int& PasajerosMaximos(){return MaxPasajeros;}
    Turismo(const string M, const int& P):MaxPasajeros(P){matricula = M;}   
};

class Camion: Vehiculo {
private:
    int PesoMaximo;
public:
    Camion(const int& P, const string& M):PesoMaximo(P){matricula = M;}
    const int& Peso()const { return PesoMaximo;}
    int& Peso(){return PesoMaximo;}
    void MostrarVehiculo(){cout<<matricula<<endl;}
};

/**
 * @brief La función debe guardar cada puntero en función al objeto que apunta. Si apunta a un objeto Camión, 
 * lo guarda en el vector de Camión.
 * 
 * @param vector<Vehiculo>& V, vector<Turismo>& Coches, vector<Camion>& Camiones
 * 
 * @return void 
 */
void Ordena(vector<Vehiculo*> &V, vector<Turismo*> &Coches, vector<Camion*> &Camiones){

    //Recorremos el vector de vehiculos
    for(size_t i = 0 ; i < V.size(); ++i){

        if(Turismo * m = dynamic_cast<Turismo*>(V[i]) ){
            Coches.emplace_back(m);
        }
        else if(Camion * c = dynamic_cast<Camion*>(V[i])){
            Camiones.emplace_back(c);
        }

    }

}

    int main()
{
    Camion C(1234,"M1");
    C.MostrarVehiculo();
    

return 0;
}
