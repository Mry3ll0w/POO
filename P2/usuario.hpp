#ifndef USUARIO_H
#define USUARIO_H
#include "cadena.hpp"
#include "fecha.hpp"
#include <random>
#include <crypt.h>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <unistd.h>
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

    bool verifica(const char*)const;
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