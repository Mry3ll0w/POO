#include <iostream>
#include "tarjeta.hpp"

int main(int argc, char const *argv[])
{	
	const Numero n("01234 56789 012   8");
	std::cout<<n.numero()<<endl;
	return 0;
}

