#include "usuario.hpp"
#include "cadena.hpp"
#include "tarjeta.hpp"
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

void Usuario::es_titular_de(Tarjeta& t) {
    if (t.titular()==this)//Compara la direccion de memoria directamente
    {
        Tarjetas.insert(make_pair(t.numero(),&t));
    }
}

Usuario::~Usuario()
{
    for (auto i:Tarjetas)
    {
        i.second->anular_titular();
    }
    identificadores.erase(&identficador_);//elimina user de la lista
}



void Usuario::no_es_titular_de(Tarjeta& t) {
    Tarjetas.erase(t.numero());//Elimina la tarjeta del set de tarjetas
}

void Usuario::compra(Articulo& a, unsigned int cantidad) {
    auto found = Articulos.find(&a);
    if (found!=Articulos.end())//Si el articulo esta en el carrito y cantidad == 0 eliminalo 
    {
        if (cantidad==0)
        {
            Articulos.erase(Articulos.find(&a));
        }
        if(cantidad>0){
           found->second=cantidad;
        }
       
    }
    else{
        Articulos.insert(make_pair(&a,cantidad));
    }
}

ostream& operator<<(std::ostream& salida,const Usuario& a)noexcept {
    salida<<a.id()<<'['<<a.pass_<<']'<<" "<<a.nombre()<<" "<<a.apellidos()<<endl;
    salida<<a.direccion()<<endl;
    for (auto i:a.Tarjetas)
    {
        salida<<i.second<<endl;
    }
    return salida;
}




