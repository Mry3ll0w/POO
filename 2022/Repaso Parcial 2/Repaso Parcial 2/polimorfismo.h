#ifndef polimorfismo_h
#define polimorfismo_h

#include <vector>
#include <list>
#include <string>

//Cada uno de los problemas se mete dentro de un void para evitar tener que que hacer muchas bibliotecas
void examen_2015 (){
    
    class forma{
        
    private:
        double lado;
    public:
        forma(const double l):lado(l){}
        virtual double area()=0;
        double lado_figura() const {return lado;}
        virtual ~forma();
    };
    
    class circulo : public forma{
    public:
        
        circulo(double d):forma(d){}
        double area(){
            return 3.14 * circulo::lado_figura();
        }
    };
    
    class cuadrado : public forma{
    public:
        cuadrado(const double & l):forma(l){}
                double area(){return forma::lado_figura()*forma::lado_figura();}
    };
    
    //Inicio de la rutina
    circulo c(1);
    cuadrado cua(2);
    
    forma * v[] = {&c,&cua};
    
    for (int i =0 ; i < 2 ; i++){
        std::cout << "El area de la figura  es: "<< v[i]->area()<<std::endl;
    }
    
}

//implementar la clase eclipse y circunferencia
void elipse_circunferencia(){
    
    class base {
    private:
        double r_x, r_y;
        
    public:
        base(double r1,double r2):r_x(r1),r_y(r2){}
        const double radio_x()const {return r_x;}
        const double radio_y()const {return r_y;}
        double& radio_x(){return r_x;}
        double& radio_y(){return r_y;}
        //Recibe un numero que escala la figura geometrica
        virtual void escala()=0;
        virtual ~base()=default;
    };
    
    class circulo : public base{
    public:
        
        circulo(const double r):base(r,r){}
        
        void escala(const double e){
            radio_x()= radio_x() * e;
            radio_y()= radio_y() * e;
        }
        
        double radio(){return radio_x();}

    };
    
    class elipse : public base {
        
    public:
        
        elipse(const double x, const double y):base(x,y){}
        
        void escala(const double ex, const double ey){
            radio_x() = radio_x() * ex;
            radio_y() = radio_y() * ey;
        }
        
    };
    
}




#endif /* polimorfismo_h */
