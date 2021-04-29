#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include "articulo.hpp"
#include "usuario.hpp"
#include "tarjeta.hpp"
#include <map>

int main(int argc, char const *argv[])
{	
	const Numero n("01234 56789 012   8");
	cout<<n.numero()<<endl;
	return 0;
}

