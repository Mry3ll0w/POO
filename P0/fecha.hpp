#ifndef Fecha_HPP
#define Fecha_HPP

#include <iostream>
#include <cstring>
#include <ctime>
using namespace std;


class Fecha{
    
    public:
        //Constantes
        static const int  AnnoMin=1902;
        static const int AnnoMaximo=2037;
        
        explicit Fecha(int d, int m, int y);
        explicit Fecha(int d,int m);
        explicit Fecha(int d);
        Fecha(string date);//poner Fecha sin anno
        class invalida{
            public:
                    invalida(int a):input(a){};
                    int error(){
                        return input;
                    };
                    inline void what(string e)const{
                        cout<<e<<endl;
                    };
            private:
                int input;
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
        Fecha& operator = (Fecha a);
        Fecha& operator ++();
        Fecha& operator --();
        Fecha& operator +(int);
        Fecha& operator -(int);
        Fecha& operator+=(int);
        Fecha& operator-=(int);
        ~Fecha();

    private:

        int day,month,year;
        string month_selector(int month);
        string Fecha_check(int dd ,int mm,int yy);
       

};
inline bool operator == (Fecha a,Fecha b);
inline bool operator != (Fecha a, Fecha b);
bool operator >(Fecha a, Fecha b);
inline bool operator <(Fecha a, Fecha b);
inline bool operator >=(Fecha a, Fecha b);
inline bool operator <= (Fecha a, Fecha b);

#endif