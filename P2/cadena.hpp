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
    Cadena(const size_t,char )noexcept;
    Cadena(const char[])noexcept;
    explicit Cadena(const size_t)noexcept;
    explicit Cadena()noexcept;
    Cadena(const Cadena& new_cad); 
    ~Cadena();

    Cadena(Cadena&&c):s_(c.s_),tam_(c.tam_){
        c.tam_=0;
        c.s_=nullptr;
    }
    //Funciones 
    inline unsigned length()const noexcept{
        return tam_;
    };
    inline void show()noexcept{
        cout<<s_<<endl;
    };
    Cadena substr(size_t, size_t)const;
    char at(size_t)const;
    char& at(size_t);
    const char* c_str()const noexcept{
        return s_;
    }

    //Operadores declarados fuera para poder usar en ambos lados(excepto el =)
    Cadena& operator=(const Cadena& a);
    Cadena& operator=( const char[] );
    Cadena& operator =(Cadena&& a){
        s_=a.s_;
        tam_=a.tam_;
        a.tam_=0;a.s_=nullptr;
        return *this;
    }
    Cadena operator+=(const Cadena& a);
    inline  char& operator[](size_t i)noexcept{
            return s_[i];
    };
    inline char operator[](size_t i)const noexcept {
        return s_[i];
    }
      
//iteradores P1///
typedef char* iterator;
typedef const char* const_iterator;
typedef std::reverse_iterator<iterator>reverse_iterator;
typedef std::reverse_iterator<const_iterator>const_reverse_iterator;
//Funciones de los distintos con iteradores (p1)
inline iterator begin()noexcept{
    return s_;
}
inline const_iterator begin() const noexcept{
    return s_;
}//begin puede devolver const o no const segun el tipo cbign siempre const
inline const_iterator cbegin() const noexcept{
    return s_;
}
inline const_reverse_iterator crbegin()const noexcept{
    return const_reverse_iterator(end());
}
inline iterator end()noexcept{
    return s_+tam_;
};
inline const_iterator cend()const noexcept{
    return const_iterator(s_+tam_);
}
inline const_iterator end()const noexcept{
    return const_iterator(s_+tam_);
}
inline reverse_iterator rbegin()noexcept{
    return reverse_iterator(s_+tam_);
}//usamos reverse it para convertir de char* a reverser_it
inline reverse_iterator rend()noexcept{
    return reverse_iterator(s_);
}
inline const_reverse_iterator rend()const noexcept{
    return const_reverse_iterator(s_);
}
inline const_reverse_iterator crend()const noexcept{
    return const_reverse_iterator(s_);
}
//P1 OPERADORES DE SALIDA/ENTRADA
friend ostream& operator<<(std::ostream& salida,const Cadena& cad)noexcept{
    salida<<cad.c_str();
    return salida;
}
friend istream& operator >> (std::istream& sal, Cadena& cad)noexcept{
    char str[33]="";
    sal.width(33);
    sal>> str;
    cad = str;
    return sal;
}

};
//Funciones y operadores
Cadena operator+(const Cadena& a,const Cadena& b);
inline bool operator ==(Cadena a,Cadena b){
        return !strcmp(a.c_str(),b.c_str());
    }
    inline bool operator!=(Cadena a,Cadena b){
        return !(a.c_str(),b.c_str());
    }
inline bool operator >(const Cadena& a,const Cadena& b){
        //Si una cadena tiene sus caracteres mas grandes que otra==> suma de sus caracteres en ascii sera mayor que la otra
        int car_a=0,car_b=0;
        for (size_t i = 0; i < a.length(); i++)
        {
            car_a+=int(a.at(i));
        }
        for (size_t i = 0; i < b.length(); i++)
        {
            car_b+=int(b.at(i));
        }
        if (car_a> car_b)
            return true;
        else
            return false;
}


inline bool operator >=(Cadena a,Cadena b){
    return (a > b)||(a==b);
}
inline bool operator <(Cadena a,Cadena b){
        return !(a >= b);
}
inline bool operator <=(Cadena a, Cadena b){
        return !(a>b);
    } 

#endif