#include <iostream>
#include <vector>
#include <cassert>

using namespace std;//Avoid using std:: ....
class capa{
    char icono;
    size_t x, y; /* Dimensiones de la capa */
    bool active; 
    std::vector<std::vector<char>> cuadricula;
    public:
    bool status(){return status;}
    capa(char icono_=' ',size_t x_=1,size_t y_=1):icono(icono_),active(true),x(x_),y(y_){}
    ~capa()=default;
    void change_status(){active= !active;}//Cambiamos el estado 
    void insertar(const size_t f, const size_t c);
    std::vector<std::vector<char>> cuadricula_get()const {return cuadricula;}

};

class mapa{
    capa r,h,u; //Una por cada elemento 0==> R  1==>H  2==> U  
    size_t m,n;
    public:
    
    mapa(size_t m_=1, size_t n_=1){m=m_;n=n_;r = capa('R',m_,n_); h = capa('H',m_,n_); u = capa('U',m_,n_);}
    void insertar_elemento(const size_t f ,const size_t c, const char t){
        if(t=='R'){r.insertar(f,c);}
        else if(t=='H'){h.insertar(f,c);}
        else if(t=='U'){u.insertar(f,c);}
        else
            throw std::runtime_error("Esa capa no existe");
    }
    void mostrar_mapa();
    void activar_capa(const char t){
        if(t=='R'){r.change_status();}
        else if(t=='H'){h.change_status();}
        else if(t=='U'){u.change_status();}
        else
            throw std::runtime_error("Esa capa no existe");
    }
};
int main(){

    return 0;
}
void capa::insertar(const size_t f, const size_t c) {
    if (f>=x || c>=y) throw std::out_of_range("La fila introducida o la columna es invalida");
    //Simplemente la rellenamos con el lugar que tenga que ocupar
    cuadricula[f][c]=icono;
}

void mapa::mostrar_mapa() {
    std::vector<std::vector<char>> map;
    auto mr=r.cuadricula_get();
    auto mh=h.cuadricula_get();
    auto mu= u.cuadricula_get();
    //Insertamos cada uno de los mapas
    if (r.status())
    {
        for (size_t i = 0; i < m; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                map[i][j]=mr[i][j];
            }
            
        }
        
    }
    if(h.status()){
        for (size_t i = 0; i < m; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                map[i][j]=mh[i][j];
            }
            
        }
    }
    if (u.status()){}
    {
        for (size_t i = 0; i < m; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                map[i][j]=mu[i][j];
            }
            
        }
    }
    //Imprimimos el mapa
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            std::cout<<map[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

}
