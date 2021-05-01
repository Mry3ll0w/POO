#include "tarjeta.hpp"
#include <iomanip> 
#include <cstring> 
#include <string.h> 
#include <cctype>
#include <algorithm>
#include "usuario.hpp"
bool luhn(const Cadena& num);
/* ------------------------------ Clase numero ------------------------------ */

Numero::Numero(const Cadena& n)
	: numero_(longitud(n))
{
    if( std::count_if(numero_.begin(), numero_.end(), static_cast<int(*)(int)>(std::isdigit)) != numero_.length() )
    {
        throw Incorrecto(Razon::DIGITOS) ;
    }
    //EXCEPCION LONGITUD
    if (numero_.length()<13||numero_.length()>19)
    {
        throw Incorrecto(Razon::LONGITUD);
    }
    //EXCEPCION NO_VALIDO
    if (!luhn(numero_))
    {
        throw Incorrecto(Razon::NO_VALIDO);
    }
    
	

}
Numero::operator const char*()const {
    return numero_.c_str();
}
Cadena Numero::espacio(const Cadena &cad)
{
    Cadena aux_cad (cad) ;

    std::remove_if(aux_cad.begin(),aux_cad.end()+1,[](char c){return isspace(c);});

    return Cadena(aux_cad.c_str()) ;

}

Cadena Numero::longitud(const Cadena &cad)
{

    Cadena aux = espacio(cad) ;

    if(aux.length() > 19 || aux.length() == 0 || aux.length() < 13 )
    {
        throw Incorrecto(Razon::LONGITUD) ;
    }

    return aux ;
}

bool operator <(const Numero& a, const Numero& b) {
	return strcmp(a,b)<0;
}




/* ------------------------------ clase tarjeta ----------------------------- */


Tarjeta::Tarjeta(const Numero& numero, Usuario& user,const Fecha& fecha_caducidad)
    : numero_(numero),
      titular_(&user),
      caducidad_(fecha_caducidad),
      activa_(true),
      tipo_(selec_tipo())
{
    
/* ------------------------- La tarjeta esta Caducada ------------------------ */
    if (caducidad_ <Fecha())//Si la fecha de caducidad es mayor o igual que la actual entonces esta caducada
    {
        throw Caducada(fecha_caducidad);

    }

}

Tarjeta::Tipo Tarjeta::selec_tipo()const{
    Cadena aux_tipo =numero_.n();
    if (aux_tipo[0]=='3')
    {
        if (aux_tipo[1]=='4'||aux_tipo[1]=='7')
        {
            return AmericanExpress;
        }
        else{
            return JCB;
        } 
    }
    else if(aux_tipo[0]=='4'){
        return VISA;
    }
    else if(aux_tipo[0]=='5'){
        return Mastercard;
    }
    else if (aux_tipo[0]=='6')
    {
        return Maestro;
    }
    else
        return Otro;
}

Tarjeta::~Tarjeta()
{
    
    if(Usuario* temp_u = const_cast<Usuario*>(titular_)) {
        temp_u->no_es_titular_de(*this);
    }

}

bool Tarjeta::activa(bool f) {
    activa_=f;
    return activa_;
}

ostream& operator<<(std::ostream& salida,const Tarjeta& a)noexcept{
    switch(a.tipo()){ 
        case Tarjeta::VISA: salida << "VISA"; break;
        case Tarjeta::Mastercard: salida << "Mastercard"; break; 
        case Tarjeta::Maestro: salida << "Maestro"; break; 
        case Tarjeta::JCB:salida << "JCB"; break; 
        case Tarjeta::AmericanExpress: salida << "AmericanExpress"; break; 
        case Tarjeta::Otro: salida << "Otro"; break;  
    }
    return salida;
}

bool operator < (const Tarjeta& a, const Tarjeta& b){
    return a.numero()<b.numero();
}
