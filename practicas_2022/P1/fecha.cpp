#include "fecha.hpp"
#include <ctime>
Fecha::Fecha(int d,int m,int y){
        time_t tt;
        time(&tt);
        tm TM = *localtime(&tt);
        int tday= TM.tm_mday;
        int tmonth = TM.tm_mon+1;
        int tyear = TM.tm_year + 1900;
        if (d==0)
        {
            d =tday;
        }
        if (m==0)
        {
            m = tmonth;
        }
        if (y==0)
        {
            y = tyear;
        }
    Fecha_check(d,m,y);
    day=d;
    month=m;
    year=y;
    
    
}
Fecha::Fecha(const char date[11]){
    
    
    if(sscanf(date, "%d/%d/%d", &day, &month, &year)<3){
        throw Fecha::Invalida(date);
    }
    *this = Fecha(day,month,year);

}

//////////////////////////////////////////////////////////////////////CONSTRUCTOR DE CONVERSION \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/
const char* Fecha::cadena()const{
    setlocale(LC_ALL,"es_ES.UTF-8");//Ponemos en default la locale completa usando ""
    static char* salida= new char [45];
    tm date_ctime={};
    date_ctime.tm_mday=day;
    date_ctime.tm_mon=month-1; //Corregimos el desfase
    date_ctime.tm_year= year-1900;
    mktime(&date_ctime);
    strftime(salida, 45,"%A %d de %B de %Y",&date_ctime);
    return salida;
}



const char* Fecha::month_selector(int m){
        switch(m){
            case 1: 
                return "Enero";
                break;
            case 2:
                return "Febrero";
                break;
            case 3:
                return "Marzo";
                break;
            case 4:
                return "Abril";
                break;
            case 5:
                return "Mayo";
                break;
            case 6:
                return "Junio";
                break;
            case 7:
                return "Julio";
                break;
            case 8:
                return "Agosto";
                break;
            case 9:
                return "Septiembre";
                break;
            case 10:
                return "Octubre";
                break;
            case 11:
                return "Noviembre";
                break;
            case 12:
                return "Diciembre";
                break;
            default:
                return "ERROR";
                break;    
        }
}

void Fecha::show_date()noexcept{
    cout<<day<<" de "<<month_selector(month)<<" de "<<year<<endl;
}




bool operator >(Fecha a, Fecha b){

    if (a.anno() > b.anno())
    {
        return true;
    }
    else if (a.mes()>b.mes() && a.anno()==b.anno())
    {
        return true;
    }
    else if(a.dia() > b.dia() && a.mes() == b.mes() && a.anno()==b.anno() ){
        return true;
    }
    else {
        return false;
    }

}

Fecha Fecha::operator +(int n)const{
    Fecha temp_date(*this);
    temp_date+=n;
    return temp_date;
}

Fecha Fecha::operator -(int n)const{
    Fecha temp_date(*this);
    temp_date+=-n;
    return temp_date;
}

void Fecha:: Fecha_check(int dd,int mm,int yy){
      
        if (dd > 31 || dd <1 )
        {
            throw Fecha::Invalida ("Dia erroneo") ;
        }
        else if (mm > 12 || mm<1)
        {
            throw Fecha::Invalida("Mes erroneo") ; 
        }
        else if(yy < Fecha::AnnoMinimo){
            throw Fecha::Invalida ("anno < AnnoMinimo");
        }
        else if (yy > Fecha::AnnoMaximo)
        {
            throw Fecha::Invalida ("anno > AnnoMaximo");
        }
        else{
                if ((mm==4 || mm==6 || mm==9 || mm==11 )&& (dd >30 ))
                {
                    throw Fecha::Invalida ("este mes no tiene 31 dias"); // no tiene 31 dias 
                }
                else if ((mm==2 && ((yy%4)!=0)) && (dd >28)){ 
                    throw Fecha::Invalida ("Este anno no es bisiesto");//29 dias en no bisisesto
                }
                else if (mm==2 && dd>29)
                    throw Fecha::Invalida ("feb no tiene mas de 29 dias"); //feb no tiene mas de 29 dias
        }  
}

 Fecha& Fecha::operator+=(int n){
    if(n!=0){
        tm parser_date = {};
        parser_date.tm_mday = day + n;
        parser_date.tm_mon = month - 1;
        parser_date.tm_year = year - 1900;

        mktime(&parser_date);

        int tyear = parser_date.tm_year + 1900;
        int tmonth = parser_date.tm_mon + 1;
        int tday = parser_date.tm_mday;
        
        *this=Fecha (tday,tmonth,tyear);
        
 }
    return *this;
 }
 Fecha& Fecha::operator-=(int n){
     *this+=-n;
     return *this;
 }  
   

std::ostream& operator << (std::ostream& salida,const Fecha& date){
        salida<<date.cadena();
    return salida;
}

std::istream& operator >> (std::istream& input, Fecha& date){
    char temp_cad[11];//10+1
    input.width(11);
    input>>temp_cad; 
    try{
        date = Fecha(temp_cad);
    }catch(Fecha::Invalida e)
    {
            input.setstate(std::ios_base::failbit);
            throw e;
    }
    
    return input;
}
