#include <iostream>
using namespace std;
class doble
{
public:
	doble(double a_):a(a_){}
	operator double(){
		return a;
	}
private:
	double a;	
};
int main(){
	double a = 1.5, b= 10.5;
	doble c = 5.25, d=c;
	std::cout << c / d * b + b * c-c* c / b + b / c << std::endl; //65
	d = a = b += c;
	std::cout << d << ' ' << a << ' ' << b << ' '<< c << std::endl; // 15,75 15,75 15,75 5,25

}