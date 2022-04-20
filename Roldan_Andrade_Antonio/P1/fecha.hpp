#ifndef Fecha_HPP
#define Fecha_HPP
#include <iostream>
#include <cstring>
#include <ctime>
using namespace std;


class Fecha{
    
    public:
        //Constantes
        static const int  AnnoMinimo{1902};
        static const int AnnoMaximo{2037};
        //Constructores
        explicit Fecha(int d=0, int m=0, int y=0);
        Fecha(const char* date);
        const char* cadena()const;

        //Fecha(const Fecha& f)=default;
        //Clase de excepcion
        class Invalida{
            public:
                    Invalida(const char* ent ):input(ent){};
                    inline const char* por_que()const{
                        return input;
                    };
            private:
                const char* input;
        };

/* --------------------------------- METODOS -------------------------------- */

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
    
        Fecha& operator ++(){
            *this+=1;
            return *this;
        }
        inline Fecha operator ++(int){
            Fecha t(*this);
            *this+=(1);
            return  t;
        }
        Fecha& operator --(){
            *this+=-1;
            return *this;
        }
        inline Fecha operator--(int){
            Fecha t(*this);
            *this+=(-1);
            return  t;
        }
        Fecha operator +(int)const;
        Fecha operator -(int)const;
        Fecha& operator+=(int);
        Fecha& operator-=(int);
        ~Fecha()=default;

        //Operadores De E/S
       friend std::ostream& operator << (std::ostream& salida,const Fecha& date);
       friend std::istream& operator >>  (std::istream& , Fecha& );

    private:

        int day,month,year;
        const char* month_selector(int month);
        void Fecha_check(int dd ,int mm,int yy);

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
