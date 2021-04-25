#include "usuario.hpp"
#include "cadena.hpp"
#include <random>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <unistd.h>

using namespace std;

/* ------------------------------- CLASE CLAVE ------------------------------ */

Clave::Clave(const char* input){
    //Excepcion de clave demasiado corta
    if (strlen(input)<5){throw Clave::CORTA;}
    //Encriptado    
    char const MD5chars[]="./0123456789ABCDEFGHIJKLMNOPQRST"
    "UVWXYZabcdefghijklmnopqrstuvwxyz";
    random_device r_dev;
    char salida[2]={MD5chars[rand() % 64],MD5chars[rand()% 64]};

    if (crypt(input,salida)==nullptr)
    {
        throw Clave::ERROR_CRYPT;
    }
    clave_cifrada =crypt(input,salida);
} 


bool Clave::verifica(const char* a)const{
    Cadena v(crypt(a,clave_cifrada.c_str()));
    return v == clave_cifrada;
}


/* ------------------------------ CLASE USUARIO ----------------------------- */


Usuario::Usuario(const char* id,const char* nombre, const char* apellidos, const char* direccion, const char* clave)
    : identficador_(Cadena(id)),
      nombre_(Cadena(nombre)),
      apellidos_(Cadena(apellidos)),
      direccion_(Cadena(direccion)),
      pass_(Clave(clave).clave())
{
    if (identificadores.insert(&identficador_).second==false)
	{
		throw Id_duplicado(identficador_);//Este user ya existe
	}
    
}





