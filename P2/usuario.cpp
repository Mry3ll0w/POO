#include "usuario.hpp"
#include "cadena.hpp"
#include <random>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <unistd.h>

using namespace std;

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

