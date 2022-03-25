#include <iostream>
#include <map>
#include <set>
using namespace std;//Avoid using std:: ....

int main(){
    /* ------------------------------- EJERCICIO 1 ------------------------------ */
    class a;class b;class c;class d;
    class a{
       std::pair<int,c*>rel_a_c;
       public:
       a()=default; 
    };
    class b{
        std::set<d*>rel3;//No existe una relacion doble
        std::map<int,d*>rel3_apc;
    };
    class c{
        int c1;
        b B;
        std::set<d*>rel4;
        private:
        int c_get(){return c1;}
    };
    class d{
        c* C;
    };
//EJERCICIO 2
    class ej2{
    private:
        std::map<c*,std::set<d*>>rel_c_d;
        std::map<d*,c*>rel_d_c;
    public:
        void asocia(c& c_, d& d_ ){
            //Relacion directa
            if(rel_c_d.find(&c_)!=rel_c_d.end()){
                //Lo encuentra
                rel_c_d[&c_].insert(&d_);
            }
            else{
                //No lo encuentra
                std::set<d*>temp_d;
                temp_d.insert(&d_);
                rel_c_d.insert(make_pair(&c_,temp_d));
            }
            //Relacion indirecta
            if(rel_d_c.find(&d_)!=rel_d_c.end()){
                rel_d_c[&d_]=&c_;
            }
            else{
                rel_d_c.insert(make_pair(&d_,&c_));
            }

        }
        void asocia(d& d_, c& c_ ){asocia(c_,d_);}
        std::set<d*> asociados( c& c_){
            if(rel_c_d.find(&c_)!=rel_c_d.end()){
                return rel_c_d[&c_];
            }
            else{
                std::set<d*>t;
                return t;//devuelve set vacio
            }
        }   
        c* asociados( d&d_){
            if(rel_d_c.find(&d_)!=rel_d_c.end()){
                return rel_d_c[&d_];
            }
            else{
                c t;
                return &t;//c vacio
            }
        }
    };
    return 0;
}

