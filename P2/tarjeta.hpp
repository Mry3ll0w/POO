#ifndef TARJETA_H
#define TARJETA_H
#include "cadena.hpp"
#include "usuario.hpp"
#include "fecha.hpp"`
#include <set>

class Numero
{
public:
	//CONSTRUCTORES
	Numero(const char* n);
	~Numero();
	operator const char*()const{return numero_.c_str();}
	//Excepciones
	enum Razon{LONGITUD,DIGITOS,NO_VALIDO};

    /**
     * Clase incorrecto para el manejo de excepciones
     * */
    class Incorrecto
    {
    private:
        Numero::Razon r;
    public:
        Incorrecto(const Numero::Razon r_):r(r_){};
        Razon razon(Razon a){return r;}   
    };

private:
	Cadena numero_;
};

/* ------------------------------ CLASE TARJETA ----------------------------- */

class Tarjeta
{
public:
    enum Tipo{Ctro,VISA,Mastercard,Maestro,JCB,AmericanExpress};
	Tarjeta(const char* numero, Usuario& user,const char* fecha_caducidad);
	~Tarjeta();
private:
    Numero numero_;
    Usuario* titular;
    Fecha caducidad;
    bool activa;
    std::set<Tarjeta*>tarjetas;
};

bool alg_luhn(const char *numero);
bool operator <(const Numero&, const Numero&);


#endif