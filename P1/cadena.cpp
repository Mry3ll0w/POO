#include <iostream>
#include "cadena.hpp"

Cadena::Cadena(const char c,const  size_t t)noexcept{
    s_=new char[t+1];
    for (size_t i = 0; i < t; i++)
    {
        s_[i]=c;
    }
    tam_=t;
}
Cadena::Cadena(const char parser_cad[])noexcept{
    tam_=std::strlen(parser_cad);
    s_=new char[tam_+1];
    std::strcpy(s_,parser_cad);
    
}

 Cadena::Cadena(const size_t size)noexcept{
    tam_=size;
    s_=new char[tam_+1];
}

Cadena::Cadena(const Cadena &new_cad){
    tam_=new_cad.tam_;
    s_=new char[new_cad.length()+1];
    std::strcpy(s_,new_cad.s_);
}

Cadena::Cadena()noexcept{
    tam_=0;
    s_=new char[2];
    std::strcpy(s_," ");
}

//Destructor
Cadena::~Cadena(){
    delete []s_;
    tam_=0;
}
//Funciones/operadores
 
 Cadena& Cadena::operator=(const Cadena a){
     if (std::strcmp(a.s_,s_)==0)
    {
        return *this;
    }
    else{
         delete []s_;
        tam_=a.tam_;
        s_=new char[a.tam_+1];
        std::strcpy(s_,a.s_);
        return *this;
    }
   
 }
Cadena& Cadena::operator =(const char parser_cad[]){
    if (std::strcmp(parser_cad,s_)==0)
    {
        return *this;
    }
    else{
        delete []s_;
        tam_=std::strlen(parser_cad);
        s_=new char[tam_+1];
        std::strcpy(s_,parser_cad);
        return *this;
    }
}

 Cadena Cadena::operator +=(const Cadena& a){
    tam_= a.length()+tam_;
    std::strcat(s_,a.s_);
    return *this;
    }
    

 Cadena operator+(const Cadena& a,const Cadena& b){
    Cadena temp(a);
    return temp+=b;
}

Cadena Cadena::substr(size_t  inf_limit, size_t sup_lim){
      if (inf_limit > sup_lim)
    {
        swap(inf_limit,sup_lim);
    }
    if (inf_limit<0 || sup_lim > tam_)
    {
        throw out_of_range("Se ha introducido en la funcion un indice fuera de rango");
    }
    else{
        
       Cadena a((sup_lim - inf_limit)+1);
        size_t k =0;
        for (size_t i = inf_limit; i < sup_lim; i++)
        {
            a[k]=s_[i];
            k++;    
        }
        return a;
    }
}
const char& Cadena::at(size_t i)const{
    if (i<0 || i>=tam_)
        {
            throw std::out_of_range("Se ha introducido un valor fuera de rango");   
        }
        else
            return s_[i];
}

char & Cadena::at(size_t i){
    if (i<0 || i>=tam_)
        {
            throw std::out_of_range("Se ha introducido un valor fuera de rango");   
        }
        else
            return s_[i];
}