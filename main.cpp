#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Utility.hpp"
#include <iomanip>

using namespace std;
using namespace utility;

#define MAXREN 10
#define MAXCOL 10

//CLASE MATRIZ
class Matriz{
	friend ostream & operator<<(ostream&,const Matriz &);
	friend istream & operator>>(istream &, Matriz &);
	friend Matriz operator*(float escalar, Matriz &A){return A*escalar;}
	
	
	public:
		explicit Matriz(int=1,int=1);
		explicit Matriz(int);
		Matriz(const Matriz &A);
		~Matriz();

		int getN();
		int getM();

		Matriz & operator=(const Matriz &);
		Matriz operator+(const Matriz &) const;
		Matriz operator-(const Matriz &) const;
      	Matriz operator*(const Matriz &) const;
      	Matriz operator*(float escalar) const;
      	void Transponer() const;
      	void Invertir();
    private:
    	int n,m;
    	float **array;
    	void ceros_arriba(int, int, Matriz &);
    	void ceros_abajo(int, int, Matriz &);
    	void GenerarIdentidad();
};

// Función auxiliar, con tal de separar todo en módulos para posibles usos futuros :D
void Dimensionar(int&,int&);

int main(){
	int m,n,opc,opc1;
	float escalar;
	do{
		try{
			cout<<"Programa para operar matrices de mxn\n\n";

			cout<<"Qu\x82 operaci\xa2n desea realizar?"<<endl;
			cout<<"0) Salir"<<endl;
			cout<<"1) Suma"<<endl;
			cout<<"2) Resta"<<endl;
			cout<<"3) Multiplicaci\xa2n entre matrices"<<endl;
			cout<<"4) Multiplicac\xa2n por escalar"<<endl;
			cout<<"5) Transpuesta de la Matriz"<<endl;
			cout<<"6) Invertir una Matriz"<<endl;
			

			do{
				cin>>opc;
				if(opc<0 || opc>7) cout<<"Opci\xa2n no disponible, elija otra."<<endl;
			}while(opc<0 || opc>7);

			if(opc!=0){
				Dimensionar(m,n);
			}

			
				Matriz A(m,n);
				Matriz B(m,n);
				Matriz C(m,n);


			switch(opc){
				case 0:
					break;
				case 1:
					cout<<"Valores de la primera Matriz:\n\n";
					cin>>A;
					cout<<"Valores de la segunda Matriz:\n\n";
					cin>>B;
					C = A + B;
					cout<<"Resultado:\n\n";
					cout<<C;
					break;
				case 2:
					cout<<"Valores de la primera Matriz:\n\n";
					cin>>A;
					cout<<"Valores de la segunda Matriz:\n\n";
					cin>>B;
					C = A - B;
					cout<<"Resultado:\n\n";
					cout<<C;
					break;
				case 3:
					cout<<"Valores de la primera Matriz:\n\n";
					cin>>A;
					cout<<"Valores de la segunda Matriz:\n\n";
					cin>>B;
					C = A * B;
					cout<<"Resultado:\n\n";
					cout<<C;
					break;
				case 4:
					cout<<"Valores de la Matriz:\n\n";
					cin>>A;
					cout<<"Valor del escalar a utilizar: ";
					cin>>escalar;
					C = A*escalar;
					cout<<"Resultado:\n\n";
					cout<<C;
					break;
				case 5:
					cout<<"Valores de la Matriz:\n\n";
					cin>>A;
					A.Transponer();
					break;
				case 6:
					if(A.getN() != A.getM()){
						cout<<"Matriz no cuadrada";
						break;
					}
					cout<<"Valores de la Matriz:\n\n";
					cin>>A;
					A.Invertir();
					break;
			}

			do{
				cout<<"\n\nQuiere realizar otra operaci\xa2n?(0: No || 1: Si): ";
				cin>>opc1;
				if(opc1<0 || opc1>1) cout<<"Opci\x2an no disponible\n";
			}while(opc1<=-1 || opc1>=2);

			if(opc1==0) break;
		}catch(bool sePudo){
			if(!sePudo) cout<<"meh";
		}
	}while(opc!=0);


	pause();
}

Matriz::Matriz(int x, int y){
	m = x;
	n = y;
	array = new (nothrow) float *[m];
	for(int i=0;i<n;++i){
		array[i] = new (nothrow) float [n*n];
	}
	if(array == NULL) throw false;
}

Matriz::Matriz(int x){
	m = x;
	n = 1;
	array = new (nothrow) float *[m];
}

Matriz::~Matriz(){
	for(int i=0;i<n;++i){
		delete[] array[i];
	}
	delete[] array;
}

Matriz::Matriz(const Matriz &A): m(-1),n(-1),array(NULL){
	*this = A;
}

void Dimensionar(int &m, int &n){
	do{
		cout<<"m: ";
		cin>>m;
	}while(m<1 || m>MAXREN);

	do{
		cout<<"n: ";
		cin>>n;
	}while(n<1 || n>MAXCOL);
}

int Matriz::getN(){
	return n;
}

int Matriz::getM(){
	return m;
}

ostream & operator<<(ostream&,const Matriz &A){
	for(int i=0;i<A.m;++i){
		for(int j=0;j<A.n;++j) 
			cout<<setw(15)<<A.array[i][j];
	cout<<endl;
    }
}

istream & operator>>(istream &, Matriz &A){
	for(int i=0;i<A.m;++i){
		for(int j=0;j<A.n;++j){
	    	cout<<"Introduce el n\xa3mero ("<<i+1<<","<<j+1<<"): ";
	    	cin>>A.array[i][j];
		}
		cout<<endl;
    }
}


Matriz & Matriz::operator=(const Matriz &A){
	if(this != &A){
		if(n!= A.n || m!=A.m){
			if(!array){
				for(int i=0;i<n;++i){
					delete[] array[i];
				}
				delete[] array;
			}
			m = A.m;
			n = A.n;
			array = new (nothrow) float *[m];
			for(int i=0;i<n;++i){
				array[i] = new (nothrow) float [n*n];
			}
		}
		for(int i=0;i<m;++i){
			for(int j=0;j<n;++j){
				array[i][j]=A.array[i][j];
			}
		}
	}
}

Matriz Matriz::operator+(const Matriz &A)const{
	Matriz X(m,n);
	for(int i=0;i<m;++i){
		for(int j=0;j<n;++j){
			X.array[i][j] = array[i][j]+A.array[i][j];
		}
	}
	return X;
}

Matriz Matriz::operator-(const Matriz &A)const{
	Matriz X(m,n);
	for(int i=0;i<m;++i){
		for(int j=0;j<n;++j){
			X.array[i][j] = array[i][j]-A.array[i][j];
		}
	}
	return X;
}

Matriz Matriz::operator*(const Matriz &A)const{
	Matriz X(m,n);
	for(int i=0;i<m;++i){
		for(int j=0;j<n;++j){
			X.array[i][j]=0;
			for(int k=0;k<n;k++){
				X.array[i][j]=X.array[i][j]+array[i][k]*A.array[k][j];
			}
		}
	}
	return X;
}

Matriz Matriz::operator*(float escalar)const{
	Matriz X(m,n);
	for(int i=0;i<m;++i){
		for(int j=0;j<n;++j){
			X.array[i][j] = escalar*array[i][j];
		}
	}
	return X;
}

void Matriz::Transponer()const{
	for(int i=0;i<n;++i){
		for(int j=0;j<m;++j){
			cout<<setw(10)<<array[j][i];
		}
	}
}

void Matriz::GenerarIdentidad(){
	for(int i=0;i<m;++i){
		for(int j=0;j<n;++j){
			if(i==j){
				array[i][j] = 1;
			}else{
				array[i][j] = 0;
			}
		}
	}
}

void Matriz::Invertir(){
	Matriz B(m,n);
	int i,j,k;
    int aux1=0,aux2=0;
    float aux3;
    float aux[n];

    B.GenerarIdentidad();

    j=1;
    while (array[0][0]==0){

		for(i=0;i<n;i++){
	    	aux[i]=array[0][i];
	    	array[0][i]=array[j][i];
	    	array[j][i]=aux[i];
		}
		j++;
    }

    for(i=0;i<n;i++) {
		aux1=0;
		j=0;
		while(aux1==0) {
		    if(array[i][j]!=0) {
				if(array[i][j]!=1) {
				    aux3=pow(array[i][j],-1);
				    for(k=0;k<n;k++){
						array[i][k]=(array[i][k])*aux3;
						B.array[i][k]=(B.array[i][k])*aux3;
				    }

				}
				ceros_arriba(i,j,B);
				ceros_abajo(i,j,B);
				aux1=1;
		    }
		    j++;
		}
    }

    for(i=0;i<n;i++)
		for(j=0;j<n;j++){
	    	if(i==j){
				if(array[i][j]!=1) aux2=1;
	    	}
	    	else{
				if(array[i][j]!=0) aux2=1;
	    	}
	}

    if(aux2==1){
    	 cout<<"La Matriz no tiene inversa";
    }else{
    	cout<<"Resultado:\n\n";
    	cout<<B;
    }
}

void Matriz::ceros_abajo(int i,int j, Matriz &B){
	int k,l;
    float aux=0;

    for(k=n-1;k>i;k--){
		aux=array[k][j]*-1;
		for(l=0;l<n;l++){
		    array[k][l]=(array[k][l])+array[i][l]*aux;
		    B.array[k][l]=(B.array[k][l])+B.array[i][l]*aux;
		}
    }
}

void Matriz::ceros_arriba(int i,int j,Matriz &B){
	int k,l;
    float aux=0;

    for(k=0;k<i;k++){
		aux=array[k][j]*-1;
		for(l=0;l<n;l++){
		    array[k][l]=(array[k][l])+array[i][l]*aux;
		    B.array[k][l]=(B.array[k][l])+B.array[i][l]*aux;
		}
    }
}
