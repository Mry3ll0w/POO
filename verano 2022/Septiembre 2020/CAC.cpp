#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;//Avoid using std:: ....

int main(){
    
return 0;
}
class Llamada;

struct AtrLLamada{
    string HoraInicio, Fecha;
    AtrLLamada(string h, string f):HoraInicio(h), Fecha(f) {}
    bool operator==(const AtrLLamada& lhs){return lhs.HoraInicio == HoraInicio && lhs.Fecha == Fecha;}
};

class Operador{};
class Llamada{};

class CAC{
    map<Llamada*, map<AtrLLamada, Operador*>> lo;
    map<Operador*, map < AtrLLamada, Llamada*>> ol;
public:
    void asignar (Llamada* l, Operador* o, const string& f, const string& h){
        
        //Enlace directo
        if(lo.find(l) == lo.end()){
            map<AtrLLamada,Operador*> t;
            t.insert(make_pair(AtrLLamada(f,h),o));
            lo.insert(make_pair(l,t));
        }
        else{//Existe el enlace, insetamos en el map
            lo[l].insert(make_pair(AtrLLamada(f,h),o));
        }

        //Enlace indirecto
        if(ol.find(o) == ol.end()) {
            map<AtrLLamada, Llamada*> t;
            t.insert(make_pair(AtrLLamada(f,h),l));
            ol.insert(make_pair(o, t));
        }
        else{
            ol[o].insert(make_pair(AtrLLamada(f,h),l));
        }
    }

    void recibir(Llamada* l, Operador* o,const string& f, const string& h){
        asignar(l,o,f,h);
    }

    map<AtrLLamada, Operador*> asistentes(Llamada* l){
        if(lo.find(l)==lo.end()){
            return map<AtrLLamada, Operador*>();
        }
        else
            return lo[l];
    }

    map<AtrLLamada,Llamada*> atendidas(Operador* o){
        if(ol.find(o)==ol.end()){
            return map<AtrLLamada, Llamada*>();
        }
        else
            return ol[o];
    }
};