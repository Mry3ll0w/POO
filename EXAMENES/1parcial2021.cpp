#include <iostream>
#include <vector>
class MatrizDispersa{
	struct terna{
		size_t f,c;
		double v;
		terna(size_t a, size_t b,double v_):f(a),c(b),v(v_){}
		bool operator < (const terna& t){
           		 return (f<t.f || (f==t.f && c<t.c));
           	 	/* Si la fila es menor ==> return bool , si son iguales pasa a columnas */
        	}
	};
	std::vector<terna>m;
	size_t f,c;
	bool buscar(size_t m,size_t n, size_t& pos);
public:
	MatrizDispersa(size_t m_=1, size_t n_=1):f(m_),c(n_){}
	MatrizDispersa(std::initializer_list<terna>);
	void asignar(size_t m, size_t n, double v);
	double valor(size_t m,size_t n);
	size_t filas(){return f;}
	size_t columnas(){return c;}
	size_t n_valores(){return m.size();}
};

int main(){
	return 0;
}

bool MatrizDispersa::buscar(size_t f, size_t c, size_t& pos){
	size_t it;terna t(f,c,0.);bool control;
	for(it=0;it<m.size()||m[it]<t;it++);
	if(it>=m.size()){
		control =false;
	}
	else{
		pos=it;
		if (!(t<m[it])){
/*Si la terna buscada no es mas small que la dada es igual, no puede ser mas grande */
            control= true;
       	}	
	}
	return control;
}

void MatrizDispersa::asignar(size_t m_, size_t n_, double v){
	if (m_ >= f || n_ >=c || m_ <0 || c<0)
	{
		throw std::out_of_range("La posicion dada en la matriz es incorrecta");
	}
	size_t pos;
	if (buscar(m_,n_,pos))
	{
		if (v!=0)
		{
			m[pos].v=v;
		}
		else{
			m.erase(m.begin()+pos);
		}
		
	}
	else{
		m.insert(m.begin()+pos,terna(m_,n_,v));
		// si no inserta la terna nueva
	}
	

}

double MatrizDispersa::valor(size_t a, size_t b){
	size_t pos;
	if (buscar(a,b,pos))
	{
		return m[pos].v;
	}
	else
		return 0;// si no esta en la lista entonces devuelve 0.00
}

MatrizDispersa::MatrizDispersa(std::initializer_list<terna>t){
	for(auto i: t){ // Recorro la lista inicializadora e inserto en la matriz
		asignar(i.f,i.c,i.v);
	}
}
