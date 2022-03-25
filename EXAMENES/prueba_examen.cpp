#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	class A{};
	class B{
		B(int i,const char* s=" ",int j=0){}=default;
	}
	return 0;
}