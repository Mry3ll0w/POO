#ifndef USUARIO_H
#define USUARIO_H
#include "cadena.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"
#include "fecha.hpp"
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
        Clave::Razon r;
    public:
        Incorrecta(const Clave::Razon r_):r(r_){};
        Razon razon(Razon a){return r;}   
    };

    bool verifica(const char*)const;
    Clave(const char*);
    const char* clave(){return clave_cifrada.c_str();}
};

/* ------------------------------ CLASE USUARIO ----------------------------- */

class Usuario
{
private:
    Cadena identficador_;
    Cadena nombre_;
    Cadena apellidos_;
    Cadena direccion_;
    Cadena pass_;
    std::unordered_set<Cadena*>identificadores;
    typedef std::unordered_map<Articulo*,unsigned int>art;
    
public:
    //CONSTRUCTORES
    Usuario(const char* id,const char* nombre, const char* apellidos, const char* direccion, const char* clave);
    Usuario(const Usuario& )=delete;
    Usuario& operator=(const Usuario)=delete;
    ~Usuario();

    //RELACIONES ENTRE TARJETA + ARTICULO
    
    std::map<Numero,Tarjeta*> Tarjetas;
    art Articulos;

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
    const Cadena id()const{return identficador_;}
    const Cadena nombre()const{return nombre_;}
    const Cadena apellidos()const{return apellidos_;}
    const Cadena direccion()const{return direccion_;}
    const std::map<Numero,Tarjeta*> tarjetas()const{return Tarjetas;}
    void es_titular_de(Tarjeta&);
    void no_es_titular_de(Tarjeta&);
    void compra( Articulo& , unsigned int);
    size_t n_articulos(){return Articulos.size();}

};



#endif