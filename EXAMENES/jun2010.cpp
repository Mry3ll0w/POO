#include <iostream>
#include <string>
#include <vector>

class capa{
private:
    
    std::vector<std::vector<char>> m;
    bool active;
    unsigned int f,c;
    char ic;

public:

    capa(unsigned int i = 1, unsigned int j = 1, const char icono='-'):
    f(i), c(j), active(true),m(std::vector<std::vector<char>>(i,std::vector<char>(j,'-'))), ic(icono)
    {}

    ~capa()=default;

    void activa_capa(){active=true;}

    int filas(){return f;}
    int columnas(){return c;}

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
        if(active)
            m[i][j]=ic;
        else
            throw std::runtime_error("La capa esta desactivada");
    }

    //Devuelve T si la posición esta ocupada 
    const bool ocupada(const unsigned int i, const unsigned int j){
        if( i >= f || j >= c || i < 0 || j < 0){
            
            throw std::out_of_range("Se ha insertado una posicion invalida");

        }
        return m[i][j] != '-';
    }

    capa& operator = (capa& ca){
        f = ca.f;
        c = ca.c;
        ic = ca.ic;
        m = ca.m;
        return *this;
    }

};

//Definiremos la clase mapa como una clase con una composición de capas
//Entiendo que en el mapa NO se permite que en una misma posición este 
class mapa {

private:

    capa buses, restaurantes, hospitales;
    std::vector<std::vector<char>> general;
    unsigned int f, c;

    void wipe_capa(const char c){
        for ( int i=0; i<f ;i++ ){
            for ( int j=0; j<c; j++){
              if (general[i][j] == c)
              {
                  general[i][j] = '-';
              }
              
            }
        }
    }

    void recover_capa(const char c){
        capa t ;
        switch (c){
            
            case 'H': t = hospitales; break;
            case 'R': t = restaurantes; break;
            case 'B': t = buses; break;

        }

        //Recorremos la capa reactivada y la metemos en la general
        for ( int i=0; i<t.filas() ;i++ ){
            for ( int j=0; j<t.columnas(); j++){
              
              if (t[i][j] == c)
              {
                general[i][j] = t[i][j];
              }
              

            }
        }


    }
    
public:

    mapa(const unsigned int i = 1, const unsigned int j = 1):
    buses(i,j,'B'),restaurantes(i,j,'R'), hospitales(i,j,'H'), f(i), c(j), 
    general(std::vector<std::vector<char>>(i,std::vector<char>(j,'-')))
    {
    }

    void activa_capa(const char c){
        
        if(c != 'H' && c != 'R' && c != 'B'){
            throw std::invalid_argument("No existe la capa buscada");
        }

        switch(c){

            case 'H':
                recover_capa(c);
                hospitales.activa_capa();
            break;

            case 'R':
                recover_capa(c);
                restaurantes.activa_capa();
            break;

            case 'B':
                recover_capa(c);
                buses.activa_capa();
            break;
        }
    }

    void desactiva_capa(const char c){
        if(c != 'H' && c != 'R' && c != 'B'){
            throw std::invalid_argument("No existe la capa buscada");
        }

        switch(c){

            case 'H':
                hospitales.desactiva_capa();
                std::cout<<"Desactivo capa hospital"<<std::endl;
                wipe_capa('H');
            break;

            case 'R':
                wipe_capa('R');
                restaurantes.desactiva_capa();
            break;

            case 'B':
                wipe_capa('B');
                buses.desactiva_capa();
            break;
        }

    }

    //Inserta un elemento en la capa que se desee, en caso de estar libre esa posición
    void inserta_elemento(unsigned int i, unsigned j, const char c){

        //Control de excepciones
        if( i >= f || j >= c || i < 0 || j < 0){
            
            throw std::out_of_range("Se ha insertado una posicion invalida");

        }

        
        if(c != 'H' && c != 'R' && c != 'B'){
           
            throw std::invalid_argument("No existe la capa buscada");
        }

        if(!buses.ocupada(i,j) && !restaurantes.ocupada(i,j) && !hospitales.ocupada(i,j) ){
            
            switch(c){
                
                case 'H':
                    
                    std::cout<<"Inserto Hospital"<<std::endl;
                    hospitales.inserta_elemento(i,j);
                    general[i][j]='H';
                    
                break;

                case 'R':
                    std::cout<<"Inserto Restaurante"<<std::endl;
                    restaurantes.inserta_elemento(i,j);
                    general[i][j]='R';
                break;

                case 'B':
                    general[i][j]='B';
                    std::cout<<"Inserto bus"<<std::endl;
                    buses.inserta_elemento(i,j);
                break;
            }

        }
        else{ 

            std::cout<<"Posicion ocupada "<<std::endl;
        }

    }

    void muestra_mapa(){

        for (int i=0; i < f; i++) {
            for (int j=0; j < c; j++){
                
               std::cout<<general[i][j]<<" ";

            }
            std::cout<<std::endl;//Saltamos de linea
        }

      

    }
    
    bool estado_capa(const char c){

        switch(c){
            case 'H':
                return hospitales.estado();
            break;

            case 'R':
                return restaurantes.estado();
            break;

            case 'B':
                return buses.estado();
            break;

            default:
                throw std::invalid_argument("Esa capa no existe");
            break;
        }

    }

    const capa & restauracion()const{return restaurantes;}
    const capa & bus()const{return buses;}
    const capa & hospital(){return hospitales;}
};


int main(){

mapa m(3,3);


m.inserta_elemento(0,0,'H');
m.inserta_elemento(0,1,'R');

m.desactiva_capa('H');

m.muestra_mapa();

m.activa_capa('H');

m.muestra_mapa();

return 0;
}

