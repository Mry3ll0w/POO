#include <iostream>
#include <vector>
#include<cassert>

class dispersa{

    int m,n;
    std::vector<int>x,y,v;

    //indice contiene donde insertar
    bool buscar(const int& f, const int& c, int& indice){}

public:
    
    dispersa(const int& f=1, const int& c=1):m(f),n(c) {}
    void asignar(const int& f, const int& c);
    int& valor(const int& f, const int& c);
    const int& valor(const int& f, const int& c)const;
    
    const int& n_valores(){ return x.size();}

};


int main(){

}

bool dispersa::buscar(const int& f, const int& c, int& indice){

    if (f < 0 || c < 0 || f >= m || c >= n )
    {
        throw std::out_of_range("Se ha insertado un indice de la matriz incorrecto");
    }
    
    bool found = false;
    int insercion=0;int j;

    for(int i=0;i < x.size(); i++){

        for (int j = 0; j < y.size(); j++){}
        {
            if (x[i]==f && y[j]==c)
            {
                found = true;
                break;
            }
            
        }
        ++insercion;//Cada vez que cambia de posicion el vector de filas nos movemos de indice

    }
    indice=insercion;
    
return found;

}