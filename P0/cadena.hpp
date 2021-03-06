#ifndef CADENA_HPP
#define CADENA_HPP

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
class Cadena
{
private:
    int error_parser(const char [],unsigned);
    char *s_;unsigned tam_=0;
    class error_handler{
        public:
            void por_que(){
                cout<<"Contruccion de la cadena es erroneo, revise los datos introducidos"<<endl;
            };
        private:
            
    };
public:
    //Constructores
    Cadena(const char, const size_t)noexcept;
    Cadena(const char[])noexcept;
    explicit Cadena(const size_t)noexcept;
    explicit Cadena()noexcept;
    Cadena(const Cadena &new_cad); 
    ~Cadena();
    operator const char*() const{
        return s_;
    }
    //Funciones 
    inline unsigned length()const noexcept{
        return tam_;
    };
    inline void show()noexcept{
        cout<<s_<<endl;
    };
    Cadena substr(size_t, size_t);
    const char& at(size_t)const;
    char& at(size_t);


    //Operadores declarados fuera para poder usar en ambos lados(excepto el =)
    Cadena& operator=(const Cadena a);
    Cadena& operator=( const char[]);
    Cadena operator+=(const Cadena& a);
    inline  char& operator[](size_t i){
        if (i<0 || i>=tam_)
        {
            throw std::out_of_range("Se ha introducido un valor fuera de rango");   
        }
        else
            return s_[i];
    };
    inline bool operator ==(Cadena a){
        return !strcmp(this->s_,a.s_);
    }
    inline bool operator!=(Cadena a){
        return !(*this==a);
    }
    inline bool operator >(Cadena a){
        //Si una cadena tiene sus caracteres mas grandes que otra==> suma de sus caracteres en ascii sera mayor que la otra
        int car_this=0,car_a=0;
        for (size_t i = 0; i < this->tam_; i++)
        {
            car_this+=int(this->s_[i]);
        }
        for (size_t i = 0; i < a.tam_; i++)
        {
            car_a+=int(a.s_[i]);
        }
        
        if (car_this> car_a)
            return true;
        else
            return false;
    };
    inline bool operator <(Cadena a){
        return !(*this > a);
    };
    inline bool operator >=(Cadena a){
        return (*this > a)||(*this==a);
    };
    inline bool operator <=(Cadena a){
        return (*this < a)||(*this == a);
    };   

    
};
//Funciones
Cadena operator+(const Cadena& a,const Cadena& b);

#endif