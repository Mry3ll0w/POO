#include "fecha.hpp"
#include <ctime>
Fecha::Fecha(int d,int m,int y):day(d),month(m),year(y){
    
    if (day == 0 && month ==0 && year==0)
    {
        Fecha aux;
        this->day=aux.dia();
        this->month=aux.mes();
        this->year=aux.anno();
    }
    if (strcmp(Fecha_check(d,m,year),"ok")==0){
        day=d;
        month=m;
        year=y;
    }
    
            
};

Fecha::Fecha(int d,int m):day(d),month(m){
    if (day == 0 && month ==0)
    {
        Fecha aux;
        this->day=aux.dia();
        this->month=aux.mes();
        this->year=aux.anno();
    }
    time_t tt;
    time(&tt);
    tm TM = *localtime(&tt);
    year = TM.tm_year + 1900;
    if (strcmp(Fecha_check(d,m,year),"ok")==0)
    {
        day=d;
        month = m;
    }
    
    
}

Fecha::Fecha(int d):day(d){
    if (day == 0 )
    {
        Fecha aux;
        this->day=aux.dia();
        this->month=aux.mes();
        this->year=aux.anno();
    }
    
    time_t tt;
    time(&tt);
    tm TM = *localtime(&tt);
    month = TM.tm_mon+1;
    year = TM.tm_year + 1900;
    if (strcmp(Fecha_check(d,month,year),"ok")==0)
    {
        day=d;
    }
    
    
}

Fecha::Fecha(){
    time_t tt;
    time(&tt);
    tm TM = *localtime(&tt);
    day= TM.tm_mday;
    month = TM.tm_mon+1;
    year = TM.tm_year + 1900;
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
    else{ 
        if (strcmp(Fecha_check(day,month,year),"ok")!=0)
        {
            exit;
        }
    }
 }

Fecha& Fecha::operator ++(){
    *this+=1;
    return *this;
}

Fecha& Fecha::operator --(){
    *this-=1;
    return *this;
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
            throw 1 ;
        }
        else if (mm > 12 || mm<1)
        {
            throw 2;
        }
        else if(yy < Fecha::AnnoMinimo){
            throw 3;
        }
        else if (yy > Fecha::AnnoMaximo)
        {
            throw 4;
        }
        else{
                if (mm==4 || mm==6 || mm==9 || mm==11 && dd >30 )
                {
                    throw 5; // no tiene 31 dias 
                }
                else if (mm==2 && (yy%4)!=0 && dd >28){ 
                    throw 6;//29 dias en no bisisesto
                }
                else if (mm==2 && dd>29)
                    throw 7; //feb no tiene mas de 29 dias
        }  
        
    }
    catch(int e)
    {
        Invalida er(e);
        switch(er.error()){
            case 1:
                er.what("Se ha introducido un dia erroneo ") ; 
                break;
            case 2:
                er.what("Se ha introducido un mes no valido");
                break;
            case 3:
                er.what("Se ha introducido un anno menor al anno minimo");
                break;
            case 4:
                er.what("Se ha introducido un anno mayor al anno maximo");
                break;
            case 5:
                er.what("Se ha introducido un mes con 31 dias cuando solo tiene 30");
                break;  
            case 6: 
                er.what("Se ha introducido mas de 28 dias en febrero y el anno no es bisiesto");
                break;
            case 7: 
                er.what("febrero no tiene mas de 29 dias");
                break;
            default:
                break;                      
        }
        exit(e);
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

Fecha::operator const char *()const{
    char* aux = new char[40];
    tm fecha={};
    fecha.tm_mday=day;
    fecha.tm_mon = month-1;
    fecha.tm_year= year -1900;

    mktime(&fecha);
    strftime(aux,40,"%A %d de %B de %Y",&fecha);
    return aux;    
}