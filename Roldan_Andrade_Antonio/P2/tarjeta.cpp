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
    if (numeros.insert(numero_).second==false)
    {
        throw Num_duplicado(numero_);
    }
/* ------------------------- La tarjeta esta Caducada ------------------------ */
    if (caducidad_ < Fecha())//Si la fecha de caducidad es mayor o igual que la actual entonces esta caducada
    {
        throw Caducada(fecha_caducidad);
    }
    auto tit_ = const_cast<Usuario*>(titular_);
    
    tit_->es_titular_de(*this);
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
    numeros.erase(numero_);
    
}

bool Tarjeta::activa(bool f) {
    activa_=f;
    return activa_;
}

ostream& operator<<(std::ostream& salida,const Tarjeta::Tipo a)noexcept{
    switch(a){ 
        case Tarjeta::VISA: salida << "VISA"; break;
        case Tarjeta::Mastercard: salida << "Mastercard"; break; 
        case Tarjeta::Maestro: salida << "Maestro"; break; 
        case Tarjeta::JCB:salida << "JCB"; break; 
        case Tarjeta::AmericanExpress: salida << "AmericanExpress"; break; 
        case Tarjeta::Otro: salida << "Otro"; break;  
    }
    return salida;
}

ostream& operator<<(std::ostream& salida,const Tarjeta& t)noexcept{
    int i=0;
    salida << t.tipo() << std::endl << t.numero() << std::endl; 
 
    Cadena aux_cad_temp = t.titular()->nombre(); 
     
    while(aux_cad_temp[i]!='\0') 
    {
        if (islower(aux_cad_temp[i])) aux_cad_temp[i]=toupper(aux_cad_temp[i]);i++;
    } 
    salida << aux_cad_temp << " "; 
    i=0; 
    aux_cad_temp = t.titular()->apellidos(); 
    while(aux_cad_temp[i]!='\0') 
    {
        if (islower(aux_cad_temp[i])) aux_cad_temp[i]=toupper(aux_cad_temp[i]);i++;
    } 
    salida << aux_cad_temp << std::endl; 
    salida << "Caduca: " << std::setfill ('0') << std::setw (2) << t.caducidad().mes() << "/" << std::setw (2) << (t.caducidad().anno() % 100) << std::endl; 
    return salida; 
}

bool operator < (const Tarjeta& a, const Tarjeta& b){
    return a.numero()<b.numero();
}
