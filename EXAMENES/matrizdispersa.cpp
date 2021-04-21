#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;
class matrizdispersa
{
public:
	matrizdispersa(const size_t f_,const size_t c_):f(f_),c(c_){}

	void asignar(const size_t f_,const size_t c_, const double v_){
		if ()
		{
			/* code */
		}
	}

	double valor(const size_t f_, const size_t c_){
		assert(f_<f || c_<c); 
		size_t indice;
		if (buscar(f_,c_, indice))
		{
			return v[indice];//Indice contiene el valor ya modificado
		}
		else{
			return 0;
		}
	}
	int n_valores(){return v.size();}

	

private:
	bool buscar(const size_t f_, const size_t c_, size_t& indice);//Suponemos que hace lo que dice el enunciado
	size_t f;
	size_t c;
	vector<size_t> v;
	std::vector<size_t> fila;
	std::vector<size_t> col;
};



int main(int argc, char const *argv[])
{
	
	return 0;
}