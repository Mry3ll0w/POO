#include <iostream>
#include <string>
#include <vector>

class services;
class mapa;


int main(){

return 0;
}

class capa{
private:
    
    std::vector<std::vector<char>> m;
    bool active;
    unsigned int f,c;
    char ic;

public:

    capa(unsigned int i = 1, unsigned int j = 1, const char icono=' '):
    f(i), c(j), active(true),m(std::vector<std::vector<char>>(i,std::vector<char>(j,' '))), ic(icono)
    {}

    ~capa()=default;

    void activa_capa(){active=true;}

    void desactiva_capa(){active=false;}

    bool estado()const{return active;}

    bool& estado(){return active;}

    const char& icono()const{return ic;}

    const std::vector<char> & operator[](unsigned int i)const
    {
        if(i<0 || i>=f){
            throw std::out_of_range("El valor insertado no es correcto");
        }
        return m[i];
    }

    void inserta_elemento(unsigned int i, unsigned int j){
        
        if( i >= f || j >= c || i < 0 || j < 0){
            
            throw std::out_of_range("Se ha insertado una posicion invalida");

        }

        m[i][j]=ic;
    }

    //Devuelve T si la posición esta ocupada 
    const bool ocupada(const unsigned int i, const unsigned int j){
        if( i >= f || j >= c || i < 0 || j < 0){
            
            throw std::out_of_range("Se ha insertado una posicion invalida");

        }
        return m[i][j] != ' ';
    }

};

//Definiremos la clase mapa como una clase con una composición de capas
//Entiendo que en el mapa NO se permite que en una misma posición este 
class mapa {

private:

    capa buses, restaurantes, hospitales;
    unsigned int f, c;
    
public:

    mapa(const unsigned int i = 1, const unsigned int j = 1):
    buses(i,j,'B'),restaurantes(i,j,'R'), hospitales(i,j,'H'), f(i), c(j)
    {
    }

    void activa_capa(const char c){
        
        if(c != 'H' || c == 'R' || c == 'B'){
            throw std::invalid_argument("No existe la capa buscada");
        }

        switch(c){

            case 'H':
                hospitales.activa_capa();
            break;

            case 'R':
                restaurantes.activa_capa();
            break;

            case 'B':
                buses.activa_capa();
            break;
        }
    }

    void desactiva_capa(const char c){
        if(c != 'H' || c == 'R' || c == 'B'){
            throw std::invalid_argument("No existe la capa buscada");
        }

        switch(c){

            case 'H':
                hospitales.desactiva_capa();
            break;

            case 'R':
                restaurantes.desactiva_capa();
            break;

            case 'B':
                buses.desactiva_capa();
            break;
        }

    }

    //Inserta un elemento en la capa que se desee, en caso de estar libre esa posición
    void inserta_elemento(unsigned int i, unsigned j, const char e){

        //Control de excepciones
        if( i >= f || j >= c || i < 0 || j < 0){
            
            throw std::out_of_range("Se ha insertado una posicion invalida");

        }

        
        if(c != 'H' || c == 'R' || c == 'B'){
            throw std::invalid_argument("No existe la capa buscada");
        }

        if(!buses.ocupada(i,j) && !restaurantes.ocupada(i,j) && !hospitales.ocupada(i,j) ){

            switch(e){
                
                case 'H':
                    hospitales.inserta_elemento(i,j);
                break;

                case 'R':
                    restaurantes.inserta_elemento(i,j);
                break;

                case 'B':
                    buses.inserta_elemento(i,j);
                break;
            }

        }

    }

    void muestra_mapa(){

        for (int i=0; i < f; i++) {
            for (int j=0; j < c; j++){

                if(buses.estado() == true and buses.ocupada(i,j)){
                    
                    std::cout << buses[i][j] <<" ";//Tiene sobrecargado el operador []

                }
                
                if(restaurantes.estado() == true and restaurantes.ocupada(i,j)){
                    std::cout<< restaurantes[i][j] <<" ";
                }

                if(hospitales.estado() == true and hospitales.ocupada(i,j)){
                    std::cout<< restaurantes[i][j]<<" ";
                }
            }
            std::cout<<std::endl;//Saltamos de linea
        }

    }
    


};