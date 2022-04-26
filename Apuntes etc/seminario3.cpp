Seminario 3.1

Ejercicio 4: clase de asociación entre Alumno y Asignatura, además se pide implementarlos en otro Ejercicio
asi que lo hago ahora, soy un capo

class Alumno_Asignatura{
private:

	std::map<Alumno*, std::set<Asignatura*>>al_asig;
	std::map<Asignatura*, std::set<Alumno*>>asig_al;

public:

	void registra(Alumno& a, Asignatura& as);
	void registra(Asignatura &as , Alumno& a);
	std::set<Asignatura*> matriculado(const Alumno & a);
	std::set<Alumno*> matriculado(const Asignatura & as);
};

// -------------------------------------------REGISTRA---------------------------------------
void Alumno_Asignatura::registra(Alumno& a, Asignatura& as){

	//¿Existe el alumno?
	if (al_asig.find(&a) == al_asig.end())//Si no existe se insertan los dos
	{
		al_asig.insert(std::make_pair(&a,&as));
	}
	else{//El alumno existe, en consecuencia actualizamos el pair del map

		al_asig[&a]=&as;
	}

	//Hacemos lo mismo de forma inversa, ya que debemos hacer la relacion en ambos sentidos
	
	if(asig_al.find(&as) == asig_al.end()){
		asig_al.insert(std::make_pair(&as,&a));
	}
	else{
		asig_al[&as]=&a;
	}

}

void Alumno_Asignatura::registra(Asignatura& as, Alumno& a){
	registra(a,as);
}

//-----------------------------------------MATRICULADO ---------------------------------------

std::set<Asignatura*> matriculado(const Alumno& a){

	//No encuentra el alumno, devuelve un set vacio
	if (al_asig.find(&a) == al_asig.end())
	{
		return std::set<Asignatura*>();
	}
	else{
		return al_asig[&a];
	}

}

std::set<Alumno*> matriculado(const Asignatura& as){

	if (asig_al.find(&as) == asig_al.end())
	{
		return std::set<Alumno*>();
	}
	else{
		return asig_al[&as];
	}

}



Ejercicio 5: clase de asociación entre Profesor y grupo

class Profesor_Grupo{
private:

	std::map<Profesor*, std::set<Grupo*>>prof_grupo;
	std::map<Grupo*, Profesor*> grupo_prof;

public:
	
	void imparte(Grupo& g, Profesor& P);
	void imparte(Profesor& P, Grupo& G){
		imparte(G,P);
	}

	std::set<Grupo*> impartidos(Profesor& P);
	Profesor* impartidos(Grupo& G);
};

//--------------------------------------------IMPARTE-------------------------------------------------

void Profesor_Grupo::imparte(const Profesor& p,const Grupo& g)
{

	if (asig_al.find(&p) == asig_al.end())
	{
		asig_al.insert(std::make_pair(&p, &g));
	}
	else
	{

		if (asig_al[&p]==nullptr)
		{
			asig_al[&p]=&g;
		}
		else
		{
			//Eliminamos el set y metemos el nuevo
			asig_al.erase(&p);
			std::set<Grupo*>t();
			t.insert(&g);
			asig_al.insert(std::make_pair(&p,t);
		}

	}

}

//--------------------------------------------IMPARTIDOS---------------------------------------------


