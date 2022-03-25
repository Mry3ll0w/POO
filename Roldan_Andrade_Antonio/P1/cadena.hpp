#ifndef CADENA_HPP
#define CADENA_HPP
#include<vector>
#include <iostream>
#include <cstring>
#include <string>


class Cadena
{
private:
    int error_parser(const char [],unsigned);
    char *s_;unsigned tam_;
    class error_handler{
        public:
            void por_que(){
                std::cout<<"Contruccion de la cadena es erroneo, revise los datos introducidos"<<std::endl;
            };
        private:
            
    };
public:
    //Constructores
    Cadena(const size_t,char )noexcept;
    Cadena(const char*)noexcept;
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
        std::cout<<s_<<std::endl;
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
typedef char* iterator ; 
typedef const char* const_iterator ; 
typedef std::reverse_iterator<iterator> reverse_iterator ;
typedef std::reverse_iterator<const_iterator> const_reverse_iterator ;


iterator begin() const{ return s_ ;}
const_iterator cbegin() const { return s_;}
reverse_iterator rbegin()const { return reverse_iterator(end()); }

const_reverse_iterator crbegin() const { return const_reverse_iterator(s_ + tam_ ); }

iterator end()const { return s_ + tam_ ; }
const_iterator cend() const { return s_ + tam_ ; }
reverse_iterator rend()const { return reverse_iterator(begin()); }
const_reverse_iterator crend() const { return const_reverse_iterator(s_ ); }



//P1 OPERADORES DE SALIDA/ENTRADA
friend std::ostream& operator<<(std::ostream& salida,const Cadena& cad)noexcept{
    salida<<cad.c_str();
    return salida;
}
friend std::istream& operator >> (std::istream& sal, Cadena& cad)noexcept{
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
        return !(a==b);
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

namespace std {
  template <> struct hash<Cadena> {
    size_t operator()(const Cadena& cad) const
    {return hash<std::string>{}(cad.c_str());}
  };
}

#endif
