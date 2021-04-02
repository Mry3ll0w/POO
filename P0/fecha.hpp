#ifndef Fecha_HPP
#define Fecha_HPP
#include "cadena.hpp"
#include <iostream>
#include <cstring>
#include <ctime>
using namespace std;


class Fecha{
    
    public:
        //Constantes
        static const int  AnnoMinimo=1902;
        static const int AnnoMaximo=2037;
        //Constructs
        explicit Fecha(int d, int m, int y);
        explicit Fecha(int d,int m);
        explicit Fecha(int d);
        Fecha(const char* date);
        operator const char*()const;
        class Invalida{
            public:
                    Invalida(const char* ent ):input(ent){};
                    inline const char* por_que()const{
                        return input;
                    };
            private:
                const char* input;
        };
        Fecha();
        int dia()const noexcept{
            return day;
        }
        int mes()const noexcept{
            return month;
        }
        int anno()const noexcept{
            return year;
        }
        void show_date()noexcept;
        //operator = usando el default
        Fecha& operator ++(){
            *this+=1;
            update_fecha(*this);
            return *this;
        }
        inline Fecha operator ++(int){
            *this+=1;
            update_fecha(*this);
            return  *this;
        }
        Fecha operator --(){
            *this+=-1;
            update_fecha(*this);
            return *this;
        }
        inline Fecha& operator--(int){
            *this+=-1;
            update_fecha(*this);
            return *this;
        }
        Fecha operator +(int)const;
        Fecha operator -(int)const;
        Fecha& operator+=(int);
        Fecha& operator-=(int);
        ~Fecha();

    private:

        int day=0,month=0,year=0;
        const char* month_selector(int month);
        const char* Fecha_check(int dd ,int mm,int yy);
        void update_fecha(Fecha&)const ;

};
inline bool operator == (Fecha a,Fecha b){
    return (a.dia()==b.dia() && a.mes()==b.mes() && a.anno()==b.anno() );
}
inline bool operator != (Fecha a, Fecha b){
    return !(a==b);
}
bool operator >(Fecha a, Fecha b);
inline bool operator <(Fecha a, Fecha b){
    return (b > a);
}
inline bool operator >=(Fecha a, Fecha b){
       return !(a<b);
}
inline bool operator <= (Fecha a, Fecha b){
        return !(b<a);
}

#endif
