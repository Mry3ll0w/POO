
#ifndef asociaciones_h
#define asociaciones_h

#include <iostream>
#include <map>
#include <set>
#include <string>

void ejercicio_septiembre(){
    
    //No tiene mucho sentido como tal pero se pide por parte del profesorado.
    //Una clase para almacenar los datos de la clase de asociación
    class datos_llamada{
    private:
        std::string duracion, hora_inicio;
    public:
        datos_llamada()=default;
        
        //modificadores
        std::string& duracion_llamada(){return duracion;}
        std::string& hora_inicio_llamada(){return hora_inicio;}
        
        //observadores
        const std::string& duracion_llamada()const {return duracion;}
        const std::string& hora_inicio_llamada()const {return hora_inicio;}
        
        
        ~datos_llamada()=default;
    };
    
    class llamada{};
    class operador{};
    
    //Clase de asociación para la gestion de llamadas y operadores
    class CAC{
        
        void recibir(llamada l,  operador o, datos_llamada d){
            
            //No existe en la asociación
            if(llamada_operador.find(&l) == llamada_operador.end() ){
                
                std::map<operador*, datos_llamada*> t;
                t.insert(std::make_pair(&o,&d));
                llamada_operador.insert(std::make_pair(&l, t));
                
            }
            else{//Existe dentro de la asociación
                
                //Comprobamos que no exista dentro del segundo map
                auto m = llamada_operador[&l];
                
                if(m.find(&o)==m.end()){
                    m.insert(std::make_pair(&o, &d));
                }
                else{
                    m.erase(&o);
                    m.insert(std::make_pair(&o, &d));
                }
                
            }
            
            //Asociación inversa
            if (operador_llamada.find(&o) == operador_llamada.end()) {
                
                std::map<llamada*, datos_llamada*> t;
                t.insert(std::make_pair(&l, &d));
                operador_llamada.insert(std::make_pair(&o, t));
            }
            else{
                auto m = operador_llamada[&o];
                //Comprobación interna del segundo map
                if(m.find(&l)==m.end()){
                    m.insert(std::make_pair(&l, &d));
                }
                else{
                    
                    m.erase(&l);
                    m.insert(std::make_pair(&l, &d));
                    
                }
                
            }
            
        }
        
        void asignar(const operador o, const llamada l, const datos_llamada d){
            recibir(l, o, d);
        }
        
        std::map<operador*, datos_llamada*> asignados(llamada l){
            if (llamada_operador.find(&l)==llamada_operador.end()) {
                return std::map<operador*,datos_llamada*>();
            }
            else{
                return llamada_operador[&l];
            }
        }
        std::map<llamada*, datos_llamada*> recibidos(operador o){
            
            if (operador_llamada.find(&o) == operador_llamada.end()){
                return std::map<llamada*, datos_llamada*>();
            }
            else
                return operador_llamada[&o];
        }
        
    private:
        
        //Cada llamada es atendida por uno o mas operadores con x duración
        std::map<llamada*, std::map<operador*,datos_llamada*>> llamada_operador;
        std::map<operador*, std::map<llamada*, datos_llamada*>> operador_llamada;
        
    };
    
    
    
}


void septiembre_2021(){
    
    class operador; class llamada;
    
    class llamada{
      
    private:
        std::string hora_inicio, duracion;
        operador * op; //Representamos la relación 0..1, ya que cada llamada es atendida por un operador
    public:
        void asignar(operador* o){
            op = o;
        }
        operador* asistente(){
            return op;
        }
        
    };
    
    class operador{
    private:
        std::map<std::string, llamada*> llamadas;
    public:
        void atender(std::string c, llamada l){
            if (llamadas.find(c) == llamadas.end()) {
                llamadas.insert(std::make_pair(c,&l));
            }
            else{
                llamadas.erase(c);
                llamadas.insert(std::make_pair(c,&l));
            }
        }
        
        //Falta el que devuelve la llamada y tal, alta pereza
        
    };
    
   
    
}



#endif /* asociaciones_h */
