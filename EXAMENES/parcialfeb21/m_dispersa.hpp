#ifndef m_dispersa_HPP
#define m_dispersa_HPP
#include <iostream>
#include <vector>
#include <initializer_list>
class MatrizDispersa{
    struct terna{
        terna(size_t a, size_t b,double v_):f(a),c(b),v(v_){}
        size_t f,c;
        double v;
        bool operator < (const terna& t){
            return (f<t.f || (f==t.f && c<t.c));
            /* Si la fila es menor ==> return bool , si son iguales pasa a columnas */
        }
    };
    size_t m,n;
    std::vector<terna>val; /* terna* val */
    bool buscar(size_t , size_t, size_t&);

    public:
        explicit MatrizDispersa(const size_t&,const size_t&);
        explicit MatrizDispersa(std::initializer_list<terna>&);
        size_t filas()const{return m;}
        size_t columnas()const{return n;}
        size_t n_valores()const{ return val.size();}
        void asignar(size_t , size_t ,double);
        double valor(size_t , size_t );
        /*EJERCICIO 5*/
        void print_matrix();
        
}; 

MatrizDispersa::MatrizDispersa(const size_t& f_=1, const size_t& c_=1):m(f_),n(c_) {}

MatrizDispersa::MatrizDispersa(std::initializer_list<terna>&t)/* {1,2,10.3},{3,4,9.23} */
{
    size_t i=0;
    /* El ultimo {} tiene m,n ,v */
    m = val[val.size()-1].f;
    n = val[val.size()-1].c;
    

    while (i< val.size())
    {
        asignar(val[i].f,val[i].c,val[i].v);
        ++i;
    }
    
}



bool MatrizDispersa::buscar(size_t f, size_t c, size_t& indice){
    bool aux_encontrado=false;
    size_t i=0;
    terna t(f,c,1);
    /* Encuentra la posicion en la que esta la terna buscada (si no esta sale con i = end) */
    for (  i = 0; i < val.size()&& val[i] < t; i++);
    /* Con esto tenemos la posicion del indice para la insercion a posteriori */
    if (i > val.size())
    {
        indice = val.size();
    }
    else{
        indice = i;
        if (!(t<val[i])){/*Si la terna buscada no es mas small que la dada es igual, no puede ser mas grande */
            aux_encontrado = true;
        }
    }
    return aux_encontrado;
}

void MatrizDispersa::asignar(size_t f , size_t c,double v) {
    size_t indice;
    /* excepciones del enunciado */
    if (f>= m || c>=n)
    {
        throw std::out_of_range("Filas y/o columnas fuera de rango");
    }
    /* Algoritmo */
    if (v == 0)
    {
        val.erase(val.begin()+indice);
    }
    else{
        if (buscar(f,c,indice)==false)
        {
            val.insert(val.begin()+indice,terna(f,c,v));
        }
        else{
            val[indice].v = v; //Si lo encuentro asi asi sustituyo valor por nuevo
        }
    }
    
}

double MatrizDispersa::valor(size_t f_, size_t c_){
    if (f_ >= m || c_>=n)
    {
        throw std::out_of_range("Filas o columnas fuera de rango");
    }
    
    size_t indice =0;
    bool e= buscar(f_,c_,indice);
    if (e==false)
    {
        return 0;
    }
    else
        return val[indice].v;
    
}

void MatrizDispersa::print_matrix(){ 
    
    for(int i=0; i<m; i++){ 
        for (int j = 0; j < n; j++)
        {
            for (auto it : val )
            {
                if (it.c == j && it.f )
                {
                    std::cout<<it.v<<"  ";
                }
                else
                    std::cout<<0<<"  ";
            }
            std::cout<<std::endl;
        }
        
    }    
}
/*                                          EJERCICIO 6
    No es necesario definir un destructor ya que no existen reservas dinamicas en MatrizDispersa 
*/
//TERMINAR 7 y 8

#endif 