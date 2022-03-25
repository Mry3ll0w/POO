#include <iostream>
#include <vector>
#include <stdexcept>
#include "cadena.hpp"
Cadena::Cadena(const  size_t t,const char c)noexcept{
    s_=new char[t+1];
    for (size_t i = 0; i < t; i++)
    {
        s_[i]=c;
    }
    tam_=t;
}
Cadena::Cadena(const char* parser_cad)noexcept:s_(new char[strlen(parser_cad)+1]),tam_(strlen(parser_cad)){
    strcpy(s_,parser_cad);
}

 Cadena::Cadena(const size_t size)noexcept{
    tam_=size;
    s_=new char[tam_+1];
    for (size_t i = 0; i < tam_; i++)
    {
        s_[i]=' ';
    }
}

Cadena::Cadena(const Cadena &new_cad){
    tam_=new_cad.tam_;
    s_=new char[new_cad.length()+1];
    strcpy(s_,new_cad.s_);
}

Cadena::Cadena()noexcept{
    tam_=0;
    s_=new char[2];
    strcpy(s_,"");
}
//Destructor
Cadena::~Cadena(){
    delete[] s_ ;
}
//Funciones/operadores
 
Cadena& Cadena::operator=(const Cadena& a){
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
    int tam_t=a.length()+tam_;
    char temp_s[tam_t];
    tam_= a.length()+tam_;
    strcpy(temp_s,s_);
    delete []s_;
    strcat(temp_s,a.s_);
    s_=new char [tam_+1];
    strcpy(s_,temp_s);
    
    return *this;
}
    

 Cadena operator+(const Cadena& a,const Cadena& b){
    Cadena temp(a);
    return temp+=b;
}

Cadena Cadena::substr(size_t  inf, size_t sup)const{
    int j = 0; 
    if ( inf > tam_ || sup > tam_ || (inf + sup) > tam_) {
       throw std::out_of_range ("fuera de rango"); 
    }
    char * char_aux = new char[sup + 1]; //Uno más por el terminador 
   
    unsigned int fin = inf + sup; 
    while ( inf < fin ){ 
        char_aux[j] = s_[inf]; 
        ++inf; 
        ++j; 
    } 
    char_aux[j] = '\0'; 
    Cadena salida(char_aux); 
    delete[] char_aux; 
    return salida; 
}
 char Cadena::at(size_t i)const{
    if (i>=tam_)
        {
            throw std::out_of_range("Se ha introducido un valor fuera de rango");   
        }
        else
            return s_[i];
}

char & Cadena::at(size_t i){
    if (i >= tam_)
        {
            throw std::out_of_range("Se ha introducido un valor fuera de rango");   
        }
        else
            return s_[i];
}
