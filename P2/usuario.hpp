#ifndef USUARIO_H
#define USUARIO_H
#include "cadena.hpp"
#include "fecha.hpp"

class Clave
{
private:
    Cadena clave_cifrada;
public:
    
    //Razon de fallo para el manejo de excepciones
    enum Razon{CORTA,ERROR_CRYPT};

    /**
     * Clase incorrecta para el manejo de excepciones
     * */
    class Incorrecta
    {
    private:
        Clave::Razon r;
    public:
        Incorrecta(const Clave::Razon r_):r(r_){};
        Razon razon(Razon a){return r;}   
    };


    Clave(const char*);
    const char* clave(){return clave_cifrada.c_str();}
};
class Usuario
{
private:
    /* data */
public:
    Usuario(/* args */);
    ~Usuario();
};



#endif