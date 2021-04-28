#ifndef TARJETA_H
#define TARJETA_H
#include "cadena.hpp"

#include "fecha.hpp"
#include <set>
class Usuario;
class Numero
{
public:
	//CONSTRUCTORES
	Numero(const char* n);
	const char* numero()const{return numero_.c_str();}
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
        Razon razon(){return r;}   
    };

private:
	Cadena numero_;
};

/* ------------------------------ CLASE TARJETA ----------------------------- */

class Tarjeta
{
public:

    enum Tipo{Otro,VISA,Mastercard,Maestro,JCB,AmericanExpress};
	Tarjeta(const Numero& numero, Usuario& user,const Fecha& fecha_caducidad);
    const Fecha cuando ()const{return caducidad_;}
    void anular_titular(){titular_=nullptr;activa_=false;}
    void no_es_titular(){anular_titular();}//Solicitada por el enunciado, aunque anular titular lo hace 
/* ------------------- Clases para el manejo de excepciones ------------------ */
    class Caducada
    {
    private:
        Fecha f_caducada;
    public:
        Caducada(const Fecha& f_):f_caducada(f_){};
        const Fecha& cuando()const {return f_caducada;}   
    };
    class Num_duplicado{
        public:
            Num_duplicado(const Numero& n_):n(n_){};
            const Numero& que()const{return n;}
        private:
            Numero n;
    };
    class Desactivada{
        private:
        public:
            Desactivada(){}
    };
    Tarjeta(Tarjeta&)=delete;
/* ------------------------------ observadores ------------------------------ */
    const Numero& numero()const{return numero_;}
    const Usuario* titular()const{ return titular_; }
    const Fecha& caducidad()const{ return caducidad_;}
    const bool activa()const{return activa_;}
    bool& activa(){return activa_;}
    const Tipo tipo()const;
	~Tarjeta(){
        if (activa_==true||titular_!=nullptr){no_es_titular();}
    };
/* ------------------ SOBRECARGA DEL OPERADOR DE INSERCION ------------------ */

private:
    Numero numero_;
    Usuario* titular_;
    Fecha caducidad_;
    bool activa_;
    std::set<Tarjeta*>Tarjetas;
    
};

bool alg_luhn(const char *numero);
bool operator <(const Numero&, const Numero&);


#endif