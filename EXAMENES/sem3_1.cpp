#include<iostream>
#include <set>
#include <map>
class alumno;class asignatura;class grupo;class profesor;
class alumno{
    std::map<asignatura*,grupo*>rel_al_as;
public:
    void matriculado_en(asignatura&a,grupo&g){
        if (rel_al_as.find(&a)==rel_al_as.end())
        {
            rel_al_as[&a]=&g;
        }
        else{
            rel_al_as.insert(std::make_pair(&a,&g));
        }
    }
    void eliminar(asignatura&a);
};
class asignatura{
    std::map<alumno*,grupo*>rel_al_as;
    std::set<asignatura*>rel_as_g;
public:
    void matriculado_en(alumno&a,grupo&g);
    void eliminar(alumno&a);
};
class grupo{
    asignatura* rel_g_as;
    profesor* p;
public:
    void grupo_asig(asignatura&a);
};
class profesor{
    std::set<grupo*>rel_p_g;
public:
    void imparte(grupo& g){
        if (rel_p_g.find(&g)!=rel_p_g.end())
        {
            rel_p_g.insert(rel_p_g.end(),&g);
        }
        
    }
};
/* Ejercicio 4 */
class Alumno_asignatura{
    std::map<alumno*,std::map<grupo*,asignatura*>>rel_al_as;
    std::map<asignatura*,std::map<grupo*,alumno*>>rel_as_al;
    public:
    void matriculado_en(alumno& al, asignatura&as,grupo& g);
    void matriculado_en(asignatura& as, alumno& al);
    void matriculados(alumno&a);
    void matriculados(asignatura&a);
};
void Alumno_asignatura::matriculado_en(alumno& al, asignatura& as,grupo& g){
    if (rel_al_as.find(&al)==rel_al_as.end())
    {
        rel_al_as[&al].insert(std::make_pair(&g,&as));
    }
    else{
        std::map<grupo*,asignatura*>t;
        t[&g]=&as;
        rel_al_as.insert(std::make_pair(&al,t));
    }
    //relacion inversa
    if (rel_as_al.find(&as)==rel_as_al.end())
    {
        rel_as_al[&as].insert(std::make_pair(&g,&al));
    }
    else{
        std::map<grupo*,alumno*>t;
        rel_as_al.insert(std::make_pair(&as,t));
    }
    
}

class profesor_grupo{
    std::map<grupo*,profesor*>rel_g_p;
    std::map<profesor*,grupo*>rel_p_g;
public:
    void imparte(profesor& p, grupo& g);
    void imparte(grupo& g, profesor& p);
    void impartidos(profesor& p);
    void impartidos(grupo& g);
};
void profesor_grupo::imparte(profesor& p, grupo& g){
    if (rel_p_g.find(&p)== rel_p_g.end())
    {
        rel_p_g[&p]=&g;
    }
    else{
        rel_p_g.insert(std::make_pair(&p,&g));
    }
    
    if (rel_g_p.find(&g)== rel_g_p.end())
    {
        rel_g_p[&g] = &p;
    }
    else{
        rel_g_p.insert(std::make_pair(&g,&p));
    }
}
/* ---------------------------- main para pruebas --------------------------- */
int main(){

}