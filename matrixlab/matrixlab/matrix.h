#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <fstream>
#include <type_traits>
#include <algorithm>
#include <math.h>
using namespace std;

#ifdef	MATRIXLAB_EXPORTS
#define MATRIX_API __declspec(dllexport)
#else
#define MATRIX_API __declspec(dllimport)
#endif
class MATRIX_API matrix {
protected:
	unsigned int row;
	unsigned int col;
	vector<double> vec;
public:
	matrix() {
		row = 0;
		col = 0;
	}
	matrix(const unsigned int m, const unsigned int n, vector<double> v1);
	matrix(const char* filename);
	matrix(initializer_list<double> l);
	void center();
	void scale();
	friend MATRIX_API matrix hadamard(matrix& m1, matrix& m2);
	friend MATRIX_API ostream& operator <<(ostream& s, const matrix& c);
	friend MATRIX_API matrix operator +(matrix& m1, matrix& m2);
	friend MATRIX_API matrix operator -(matrix& m1, matrix& m2);
	friend MATRIX_API matrix operator *(matrix& m1, const double a);
	friend MATRIX_API matrix operator*(matrix& m1, matrix& m2);
	void writebinmatrix(const char* name);
	double matrixnorm();
	double matrixdet();
	int matrixrank();
	matrix transpose();
	friend class PCA;
	double trace();
	void settrows(unsigned int m) {
		row = m;
	}
	void setcols(unsigned int m) {
		col = m;
	}
};
class MATRIX_API idmatrix : public matrix {
private:
	int d;
public:
	idmatrix(const unsigned int a);
	idmatrix transpose();
	double matrixdet();
};
class MATRIX_API diagmatrix : public matrix {
private:
	int d;
public:
	diagmatrix(const unsigned int a, vector<double> v1);
	double matrixdet();
	diagmatrix transpose();
};
class MATRIX_API lowtriangmatrix : public matrix {
private:
	int d;
public:
	lowtriangmatrix(const unsigned int a, vector<double> v1);
	double matrixdet();
	friend class uptriangmatrix;
	uptriangmatrix transpose();
};
class MATRIX_API uptriangmatrix : public matrix {
private:
	int d;
public:
	uptriangmatrix(const unsigned int a, vector<double> v1);
	double matrixdet();
	friend class lowtriangmatrix;
};

class MATRIX_API symmatrix : public matrix {
private:
	int d;
public:
	symmatrix(const unsigned int a, vector<double> v1);
	symmatrix transpose();
};
class MATRIX_API vect : public matrix {
private:
	int d;
public:
	vect(const unsigned int a, vector<double> v1);
	double maxnorm();
	friend MATRIX_API double scalar(vect v1, vect v2);
	double euclidnorm();
	friend MATRIX_API double cosvec(vect v1, vect v2);
	friend MATRIX_API double angle(vect v1, vect v2);
};
void writematrix(const char* filename, matrix& m);
matrix readbinmatrix(const char* filename);
