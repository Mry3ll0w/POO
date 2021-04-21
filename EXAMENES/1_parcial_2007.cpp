#include<iostream>
#include<cstring>
#include <string>
using namespace std;
enum Nucleotido{A,C,G,T};
class ADN{
	public:
		friend ADN operator +(const ADN& a,const ADN& b);
		ADN():c(0),n(0){}
		ADN(const char*str_c_):n(strlen(str_c_)){
			this->c=new Nucleotido[strlen(str_c_)+1];
			for (size_t i = 0; i < n; ++i)
			{
				switch(str_c_[i]){//Necesario ya que se esta usando un tipo enumerado para poder cambiar de char a int
					case 'A':
						c[i]=A;
						break;
					case 'C':
						c[i]=C;
						break;	
					case 'G':
						c[i]=G;
						break;
					case 'T':
						c[i]=T;
						break;
				}
			}
		}
		~ADN(){delete []c;n=0;}
		
	private:
		Nucleotido* c;
		size_t n;
		ADN(Nucleotido* c_, size_t n_):n(n_){
			std::memcpy(c,c_,n*sizeof(Nucleotido));//copiamos el contenido de la entrada c 
		}	
};

ADN operator +(const ADN& a,const ADN& b){
	size_t n=a.n+b.n;
	ADN temp(new Nucleotido[n],n);
	memcpy(temp.c,a.c,a.n*sizeof(Nucleotido));//Copia los elementos de a.c empezando en 0
	memcpy(temp.c+a.n,b.c,b.n*sizeof(Nucleotido));//Copia los elementos de b.c empezando desde a.n
	return temp;
}

int main(int argc, char const *argv[])
{
	
	return 0;
}