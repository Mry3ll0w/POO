#include <iostream>
#include <set>
#include <map>
#include <list>
#include <algorithm>
using namespace std;//Avoid using std:: ....
class a;class b; class c;class d;
int main(){

    return 0;
}
class a{
    private:
        c* C;
};
class b{
    private:
    //Si se add atributp de enlace 
    std::map<int,d*>rel3_b;
    std::set<d*>rel3;
};
class c{
    private:
        std::map<c*,int>rel1;
        b B;//Composicion
        std::set<d*>rel4_c_d; 
        int c1;
    public:
        int const c1_()const{return c1;}  
};
class d{
    private:
        c* C;
};

class rel4{
    private:
        std::map<c*,set<d*>>r_c_d;
        std::map<d*,c*>r_d_c;
    public:
        void asocia(c& c1,d& d1){
            //RELACION DIRECTA
            if (r_c_d.find(&c1)!=r_c_d.end())
            {//Si lo encuentra inserta en el set
               r_c_d[&c1].insert(&d1); 
            }
            else{
                std::set<d*> temp;
                temp.insert(&d1);
                r_c_d.insert(make_pair(&c1,temp));
            }
            //Relacion indirecta
            if (r_d_c.find(&d1)!=r_d_c.end())
            {
                r_d_c.erase(&d1);//SI lo encuentra lo desvincula
                r_d_c.insert(make_pair(&d1,&c1));
            }
            else{
                r_d_c.insert(make_pair(&d1,&c1));
            }
            
        }
        void asocia(d& d1,c& c1){
            asocia(c1,d1);
        }

        std::set<d*> asociados(c& c1){
            if (r_c_d.find(&c1)!=r_c_d.end())
            {
                return r_c_d[&c1];
            }
            else{
                std::set<d*>t;
                return t;
            }
        }

        c* asociados(d& d1){
            if (r_d_c.find(&d1)!=r_d_c.end())
            {
                return r_d_c[&d1];
            }
            else{
                c* t;
                return t;
            }
        }

};

/* ------------------------------- EJERCICIO 3 ------------------------------ */

class ListaOrdenada{
    private:
   
    public:
        typedef list<double>::const_iterator iterator;
        ListaOrdenada();
        void insertar(double e){
            l.push_back(e);
            l.sort();//Se inserta y se ordena la lista
        }
        iterator buscar (double e){
            return find(l.begin(),l.end(),e);//devuelve la posicion de e
        }
        iterator begin()const{return l.begin();}
        iterator end()const{return l.end();}
        size_t contar(double e)const{
            return count_if(l.begin(),l.end(),[e](double x)->size_t{return e==x;});
            /*
            [ e ](parametros entrada)->int/float... {
                cuerpo
            }
            */
        }
    private:
        list<double> l;
    
};

