#ifndef CADENA_HPP
#define CADENA_HPP
#include<vector>
#include <iostream>
#include <cstring>
using namespace std;
class Cadena
{
private:
    int error_parser(const char [],unsigned);
    char *s_;unsigned tam_;
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
    Cadena(Cadena&&c){
        c.tam_=0;
        c.s_=nullptr;//No termino de entender para que se hace
        cout<<"Se llama al constructor de movimiento"<<endl;
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
        if (this->tam_ > a.tam_)
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
//iteradores P1///
typedef char* iterator;
typedef const char* const_iterator;
typedef std::reverse_iterator<iterator>reverse_iterator;
typedef std::reverse_iterator<const_iterator>const_reverse_iterator;
//Funciones de los distintos con iteradores (p1)
iterator begin()noexcept{
    return s_;
}
const_iterator begin() const noexcept{return s_;}//begin puede devolver const o no const segun el tipo cbign siempre const
const_iterator cbegin() const noexcept{return s_;}
iterator end()noexcept{return s_+tam_;}
const_iterator end()noexcept const{return const_iterator(s_+tam_);}
const_iterator cend()noexcept const{return const_iterator(s_+tam_);}
const_iterator end()noexcept const{return const_iterator(s_+tam_);}
reverse_iterator rbegin()noexcept{return reverse_iterator(s_+tam_);}//usamos reverse it para convertir de char* a reverser_it
reverse_iterator rend()noexcept{return reverse_iterator(s_);}
const_reverse_iterator rend()noexcept const{return const_reverse_iterator(s_);}
const_reverse_iterator crend()noexcept const{return const_reverse_iterator(s_);}

};
//Funciones
Cadena operator+(const Cadena& a,const Cadena& b);


#endif