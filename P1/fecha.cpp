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
    if (strcmp(Fecha_check(d,m,y),"ok")==0){
        day=d;
        month=m;
        year=y;
    }
    
};

//////////////////////////////////////////////////////////////////////CONSTRUCTOR DE CONVERSION \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/
const char* Fecha::cadena()const{
    static char* salida= new char [45];
    tm date_ctime;
    date_ctime.tm_mday=day;
    date_ctime.tm_mon=month-1; //Corregimos el desfase
    date_ctime.tm_year= year-1900;
    mktime(&date_ctime);
    strftime(salida, 45,"%A %d, de %B del %Y",&date_ctime);
    return salida;
}

Fecha::~Fecha()=default;

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



Fecha::Fecha(const char* date){
    //Verificar que este bien introducido
    std::sscanf(date,"%d/%d/%d",&day,&month,&year);

    if (day == 0 && month ==0 && year==0)
    {
        Fecha aux;
        *this=aux;
    }
    Fecha_check(day,month,year);
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
    time_t aux_ptr;
    tm* ptr;
    time(&aux_ptr);
    ptr=localtime(&aux_ptr);
    ptr->tm_year=year;
    ptr->tm_mon=month;
    ptr->tm_mday=day+n;
    mktime(ptr);
    
    temp_date.year=ptr->tm_year;
    temp_date.month=ptr->tm_mon;
    temp_date.day=ptr->tm_mday;
    update_fecha(temp_date);
    return temp_date;
}

Fecha Fecha::operator -(int n)const{
    Fecha temp_date(*this);
    temp_date+=-n;
    update_fecha(temp_date);
    return temp_date;
}

const char* Fecha:: Fecha_check(int dd,int mm,int yy){
      
      try
    {
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
    catch(Fecha::Invalida error)
    {
        cout<<error.por_que()<<endl;
    }
     return "ok";    
}

 Fecha& Fecha::operator+=(int n){
    *this=*this+n;
    update_fecha(*this);
    return *this;
 }

 Fecha& Fecha::operator-=(int n){
     *this+=-n;
     update_fecha(*this);
     return *this;
 }  
   
void Fecha::update_fecha(Fecha& date )const{
    
    if (date.month == 2 && date.day==31)
    {
        if (date.year %4 &&( date.year % 400 || date.year % 100!=0))
        {
            date.day=28;
        }
        else{
            date.day=29;
        }
    }
    if ((date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11)&&(date.day==31))
    {
        date.day=30;
    }
}

std::ostream& operator << (std::ostream& salida,const Fecha& date){
    setlocale(LC_ALL,"");//Ponemos en default la locale completa usando ""
        salida<<date.dia()<<"/"<<date.mes()<<"/"<<date.anno();
    return salida;
}

std::istream& operator >> (std::istream& input, Fecha& date){
    setlocale(LC_ALL, "");
    char* temp_cad=new char[11];//10+1
    input>>temp_cad;
    Fecha temp_date(temp_cad);
    delete temp_cad;
    if (strcmp(date.Fecha_check(date.dia(),date.mes(),date.anno()),"ok")==0)
    {
        date = temp_date;
    }else{
        exit;
    }
    return input;
}