#ifndef USUARIO_H
#define USUARIO_H
#include "../P1/cadena.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"
#include "../P1/fecha.hpp"
#include <random>
#include <crypt.h>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <unistd.h>
class Tarjeta;
//Clase CLAVE
class Clave
{
private:
    Cadena clave_cifrada;
public:
    
/* -------------- Razon de fallo para el manejo de excepciones -------------- */

    enum Razon{CORTA,ERROR_CRYPT};

    
/* ------------- Clase incorrecta para el manejo de excepciones ------------- */
    
    class Incorrecta
    {
    private:
        Razon r;
    public:
        Incorrecta(const Razon r_):r(r_){};
        Razon razon()const{return r;}   
    };

    bool verifica(const char*)const;
    Clave(const char*);
    const Cadena& clave()const{return clave_cifrada;}
};

/* ------------------------------ CLASE USUARIO ----------------------------- */

class Usuario
{

public:
    //CONSTRUCTORES
    Usuario(const Cadena& id,const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion, const Clave& clave);
    Usuario(const Usuario& )=delete;
    Usuario& operator=(const Usuario)=delete;
    ~Usuario();

    //RELACIONES ENTRE TARJETA + ARTICULO
    typedef std::map<Numero,Tarjeta*>Tarjetas;
    typedef std::unordered_map<Articulo*,unsigned int>art;
    typedef  std::unordered_set<Cadena> I;

    //Manejo de excepciones
    class Id_duplicado
    {
    private:
        Cadena id;
    public:
        Id_duplicado(const Cadena&a):id(a){}
        const Cadena idd()const{return id;}
    };
    //Metodos 
    const Cadena id()const{
        return identficador_;
    }
    const Cadena nombre()const{
        return nombre_;
    }
    const Cadena apellidos()const{
        return apellidos_;
    }
    const Cadena direccion()const{
        return direccion_;
    }
    const Tarjetas& tarjetas()const{
        return Tarjeta_;
    }
    void es_titular_de(Tarjeta&);
    void no_es_titular_de(Tarjeta& t);
    void compra( Articulo& , unsigned int cantidad=1);
    const art& compra()const noexcept{
        return Articulos;
    }
    size_t n_articulos(){
        return Articulos.size();
    }
    friend ostream& operator<<(std::ostream& salida,const Usuario& a)noexcept;
    
private:
    Cadena identficador_;
    Cadena nombre_;
    Cadena apellidos_;
    Cadena direccion_;
    Clave pass_;
    static I identificadores;
    Tarjetas Tarjeta_;
    art Articulos;
    
};
 void mostrar_carro(ostream& os,Usuario& u);


#endif