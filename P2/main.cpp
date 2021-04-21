#include "cadena.cpp"
#include "fecha.cpp"
#include "articulo.hpp"
#include "usuario.hpp"
#include <map>

int main(int argc, char const *argv[])
{
	/* ejemplo uso de mapa
	typedef std::map<int, Cadena> mapa;
	mapa m;
	m.insert(make_pair(1,a));
	m.insert(make_pair(2,Cadena("bec")));
	for (auto i:m)
	{
		cout<<i.first<<" "<<i.second.c_str()<<endl;
	}
	*/

	Articulo a("0001","magia borras","00/00/0000",3.45,1);
	cout<<a<<endl;
	return 0;
}

