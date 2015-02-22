#ifndef _MATRIZ_HPP_
#define _MATRIZ_HPP_

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

void Dimensionar(int&,int&);

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
#endif