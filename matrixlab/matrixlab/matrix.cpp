#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "matrix.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <fstream>
#include <type_traits>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <iterator>
using namespace std;
//Обработка исключений
class MATRIX_API FileErr : public exception {
public:
	char const* what() const noexcept {
		return "ERROR! Unable to open the file";
	}
};
class MATRIX_API ReadErr : public exception {
public:
	char const* what() const noexcept {
		return "ERROR! The file data is damaged";
	}
};
class MATRIX_API NotASquare : public exception {
public:
	char const* what() const noexcept {
		return "ERROR! The matrix must be square";
	}
};
class MATRIX_API DiffSize : public exception {
public:
	char const* what() const noexcept {
		return "ERROR! Matrices must be the same size";
	}
};
class MATRIX_API Multipl : public exception {
public:
	char const* what() const noexcept {
		return "ERROR! Matrices must be m*n and n*l";
	}
};
class MATRIX_API BuildErr : public exception {
public:
	char const* what() const noexcept {
		return "ERROR! Impossible to build a matrix. Inapropriate vector size";
	}
};
//конструкторы
matrix::matrix(const unsigned int m, const unsigned int n, vector<double> v1) {
	row = m;
	col = n;
	vec = v1;
}
matrix::matrix(initializer_list<double> l) : vec{ l } {
	for (int i = l.size() - 1; i > 0; i--) {
		if (l.size() % i == 0) {
			if (i >= l.size() / i) {
				row = i;
				col = l.size() / i;
			}
		}
	}
}
idmatrix::idmatrix(const unsigned int a) {
	row = a;
	col = a;
	for (int i = 0; i < a; i++)
		for (int j = 0; j < a; j++) {
			if (i == j) {
				vec.insert(vec.begin(), 1);
			}
			else {
				vec.insert(vec.begin(), 0);
			}
		}
}
diagmatrix::diagmatrix(const unsigned int a, vector<double> v1) {
	if (v1.size() != a)
		throw BuildErr();
	row = a;
	col = a;
	double x;
	for (int i = 0; i < a; i++)
		for (int j = 0; j < a; j++) {
			if (i == j) {
				x = v1.back();
				v1.pop_back();
				vec.insert(vec.begin(), x);
			}
			else {
				vec.insert(vec.begin(), 0);
			}
		}
}
uptriangmatrix::uptriangmatrix(const unsigned int a, vector<double> v1) {
	if (v1.size() == (a + 1) * a / 2) {
		row = a;
		col = a;
		double x;
		for (int i = 0; i < a; i++)
			for (int j = 0; j < a; j++) {
				if (i >= j) {
					x = v1.back();
					v1.pop_back();
					vec.insert(vec.begin(), x);
				}
				else {
					vec.insert(vec.begin(), 0);
				}
			}
	}
	else if (v1.size() == a * a) {
		row = a;
		col = a;
		vec = v1;
	}
	else {
		throw BuildErr();
	}
}
lowtriangmatrix::lowtriangmatrix(const unsigned int a, vector<double> v1) {
	if (v1.size() == (a + 1) * a / 2) {

		row = a;
		col = a;
		double x;
		for (int i = 0; i < a; i++)
			for (int j = 0; j < a; j++) {
				if (i <= j) {
					x = v1.back();
					v1.pop_back();
					vec.insert(vec.begin(), x);
				}
				else {
					vec.insert(vec.begin(), 0);
				}
			}
	}
	else if (v1.size() == a * a) {
		row = a;
		col = a;
		vec = v1;
	}
	else {
		throw BuildErr();
	}

}
symmatrix::symmatrix(const unsigned int a, vector<double> v1) {
	if (v1.size() != (a + 1) * a / 2)
		throw BuildErr();
	row = a;
	col = a;
	double x;
	for (int i = 0; i < a; i++)
		for (int j = 0; j < a; j++) {
			if (i >= j) {
				x = v1.back();
				v1.pop_back();
				vec.insert(vec.begin(), x);
			}
			else {
				vec.insert(vec.begin(), 0);
			}
		}
	for (int k = 0; k < a; k++)
		for (int l = 0; l < a; l++) {
			if (k < l)
				vec[a * l + k] = vec[a * k + l];
		}
}
vect::vect(const unsigned int a, vector<double> v1) {
	if (a != v1.size())
		throw BuildErr();
	row = 1;
	col = a;
	double x;
	for (int i = 0; i < a; i++) {
		x = v1.back();
		v1.pop_back();
		vec.insert(vec.begin(), x);
	}
}
matrix::matrix(const char* filename) {
	vector<double> v;
	string temp, word = "";
	bool mode = false;
	size_t prev = 0;
	size_t next;
	int columns = 0, rows = 0, wc = 0;
	ifstream file(filename);
	if (file.is_open()) {
		while (getline(file, temp)) {
			rows++;
			for (int i = 0; i < temp.size(); i++) {
				if (!mode) {
					if (temp[i] == ' ' || temp[i] == '\t')
						continue;
					else {
						if (temp[i] == ',')
							temp[i] = '.';
						mode = true;
						word += temp[i];
					}
				}
				else {
					if (temp[i] == ' ' || temp[i] == '\t') {
						v.push_back(atof(word.c_str()));
						wc++;
						mode = false;
						word = "";
					}
					else {
						if (temp[i] == ',')
							temp[i] = '.';
						word += temp[i];
					}
				}
			}
			if (word != "") {
				v.push_back(atof(word.c_str()));
				wc++;
				word = "";
			}

		}
		columns = wc / rows;
		vec = v;
		col = columns;
		row = rows;
	}
	else {
		throw FileErr();
	}
	file.close();
}
//Перегрузка операторов
ostream& operator <<(ostream& s, const matrix& c) {
	for (unsigned int i = 0; i < c.row; i++) {
		for (unsigned int j = 0; j < c.col; j++)
			s << left << setw(6) << c.vec[i * c.col + j] << ' ';
		s << endl;
	}
	s << endl;
	return s;
}

matrix operator +(matrix& m1, matrix& m2) {
	if (!(m1.row == m2.row && m1.col == m2.col)) {
		throw DiffSize();
	}
	vector<double> v;
	for (unsigned int i = 0; i < m1.col; i++) {
		for (unsigned int j = 0; j < m1.row; j++)
			v.push_back(m1.vec[i * m1.row + j] + m2.vec[i * m2.row + j]);
	}
	matrix m3(m1.row, m1.col, v);
	return m3;
}

matrix operator -(matrix& m1, matrix& m2) {
	if (!(m1.row == m2.row && m1.col == m2.col)) {
		throw DiffSize();
	}
	vector<double> v;
	for (unsigned int i = 0; i < m1.col; i++) {
		for (unsigned int j = 0; j < m1.row; j++)
			v.push_back(m1.vec[i * m1.row + j] - m2.vec[i * m2.row + j]);
	}
	matrix m3(m1.row, m1.col, v);
	return m3;
}

matrix operator *(matrix& m1, const double a) {
	vector<double> v;
	for (unsigned int i = 0; i < m1.col; i++) {
		for (unsigned int j = 0; j < m1.row; j++)
			v.push_back(m1.vec[i * m1.row + j] * a);
	}
	matrix m3(m1.row, m1.col, v);
	return m3;
}
matrix operator*(matrix& m1, matrix& m2) {
	if (m1.col != m2.row)
		throw Multipl();
	vector<double> v;
	for (unsigned int i = 0; i < m1.row; i++) {
		for (unsigned int j = 0; j < m2.col; j++) {
			double sum = 0;
			for (unsigned int k = 0; k < m1.col; k++)
				sum += m1.vec[i * (m1.col) + k] * m2.vec[k * (m2.col) + j];
			v.push_back(sum);
		}
	}
	matrix m3(m1.row, m2.col, v);
	return m3;
}
//методы классов
double matrix::matrixdet() {
	double rez = 1;
	if (row != col) {
		throw NotASquare();
	}
	vector<double> vecc = vec;
	int  i, j, k;
	for (i = 0; i < row; i++)
		for (k = i + 1; k < row; k++)
			if (abs(vecc[i * row + i]) < abs(vecc[k * row + i]))
				for (j = 0; j < row; j++)
				{
					double temp = vecc[i * row + j];
					vecc[i * row + j] = vecc[k * row + j];
					vecc[k * row + j] = temp;
				}

	for (i = 0; i < row - 1; i++)
		for (k = i + 1; k < row; k++)
		{
			double t = vecc[k * row + i] / vecc[i * row + i];
			for (j = 0; j < row; j++)
				vecc[k * row + j] = vecc[k * row + j] - t * vecc[i * row + j];
		}

	for (i = 0; i < row; i++) {
		rez *= vecc[i * row + i];
		if (rez == 0)
			break;
	}
	return rez;
}
int matrix::matrixrank() {
	int rez = 0;
	bool check = true;
	if (row != col) {
		throw NotASquare();
	}
	vector<double> vecc = vec;
	int  i, j, k;
	for (i = 0; i < row; i++)
		for (k = i + 1; k < row; k++)
			if (abs(vecc[i * row + i]) < abs(vecc[k * row + i]))
				for (j = 0; j < row; j++)
				{
					double temp = vecc[i * row + j];
					vecc[i * row + j] = vecc[k * row + j];
					vecc[k * row + j] = temp;
				}

	for (i = 0; i < row - 1; i++)
		for (k = i + 1; k < row; k++)
		{
			double t = vecc[k * row + i] / vecc[i * row + i];
			for (j = 0; j < row; j++)
				vecc[k * row + j] = vecc[k * row + j] - t * vecc[i * row + j];
		}
	/*for (i = 0; i < row; i++) {
		for (j = 0; j < row; j++)
			cout << vecc[i*row + j] << " ";
		cout << endl;
	}*/


	for (i = 0; i < row; i++) {
		for (j = 0; j < row; j++) {
			if (vecc[i * row + j] != 0) {
				check = false;
				break;
			}
		}
		if (check)
			rez++;
		check = true;
	}
	rez = row - rez;
	return rez;
}

matrix hadamard(matrix& m1, matrix& m2) {
	if (!(m1.row == m2.row && m1.col == m2.col)) {
		throw DiffSize();
	}
	vector<double> v;
	for (unsigned int i = 0; i < m1.col; i++) {
		for (unsigned int j = 0; j < m1.row; j++)
			v.push_back(m1.vec[i * m1.row + j] * m2.vec[i * m2.row + j]);
	}
	matrix m3(m1.row, m1.col, v);
	return m3;
}

double matrix::trace() {

	if (row != col) {
		throw NotASquare();
	}
	double sum = 0;
	for (int i = 0; i < row; i++) {
		sum += vec[i * row + i];
	}
	return sum;
}

double matrix::matrixnorm() {
	double sum = 0;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			sum += vec[col * i + j] * vec[col * i + j];
	}
	return sqrt(sum);
}
double vect::maxnorm() {
	double max = vec[0];

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			if (vec[col * i + j] > max) {
				max = vec[col * i + j];
			}
	}
	return max;
}

matrix matrix::transpose() {
	vector<double>vecc = vec;
	double temp;
	for (int i = 0; i < col; i++)
		for (int j = 0, z = i; j < row; j++) {
			vecc[i * row + j] = vec[j * col + z];
		}
	matrix m3(col, row, vecc);
	return m3;
}

void writematrix(const char* filename, matrix& m) {
	string temp, p = "0";
	size_t prev = 0;
	size_t next;
	int columns = 0, rows = 0;
	ofstream file(filename);
	if (file.is_open()) {
		file << m;
	}
	else {
		throw FileErr();
	}
	file.close();
}

//ФУНКЦИИ РАБОТЫ С ВЕКТОРАМИ
double scalar(vect v1, vect v2) {
	double sum = 0;
	for (int i = 0; i < v1.col; i++) {
		sum += v1.vec[i] * v2.vec[i];
	}
	return sum;
}
double vect::euclidnorm() {
	double sum = 0;
	for (int i = 0; i < col; i++) {
		sum += vec[i] * vec[i];
	}
	return sqrt(sum);
}

double cosvec(vect v1, vect v2) {
	return scalar(v1, v2) / v1.euclidnorm() / v2.euclidnorm();
}

double angle(vect v1, vect v2) {
	return acos(cosvec(v1, v2));
}
//переопределённые методы для работы с подтипами матриц
double idmatrix::matrixdet() {
	return 1;
}
double diagmatrix::matrixdet() {
	double rez = 1;
	for (int i = 0; i < row; i++) {
		rez *= vec[i * row + i];
		if (rez == 0)
			break;
	}
	return rez;
}
double lowtriangmatrix::matrixdet() {
	double rez = 1;
	for (int i = 0; i < row; i++) {
		rez *= vec[i * row + i];
		if (rez == 0)
			break;
	}
	return rez;
}
double uptriangmatrix::matrixdet() {
	double rez = 1;
	for (int i = 0; i < row; i++) {
		rez *= vec[i * row + i];
		if (rez == 0)
			break;
	}
	return rez;
}
idmatrix idmatrix::transpose() {
	idmatrix m3(d);
	return m3;
}

symmatrix symmatrix::transpose() {
	symmatrix m3(d, vec);
	return m3;
}
diagmatrix diagmatrix::transpose() {
	diagmatrix m3(d, vec);
	return m3;
}
void readVector(std::string path, vector<vector<double> >& myVector)
{

}
void matrix::writebinmatrix(const char* name)
{
	ofstream fout(name, ios::out | ios::binary);
	vector<double> vecc = vec;
	vecc.push_back((double)col);
	vecc.push_back((double)row);
	fout.write((char*)&vecc[0], vecc.size() * sizeof(double));
	fout.close();
}

matrix readbinmatrix(const char* name) {
	ifstream fin;
	fin.open(name, ios::binary);
	if (!fin) cout << endl << " NO DATA! " << endl;
	else
	{
		fin.unsetf(std::ios::skipws);
		streampos size;
		fin.seekg(0, ios::end);
		size = fin.tellg();
		fin.seekg(0, ios::beg);
		vector<double> ve(size / sizeof(double));// reserve space for N/8 doubles
		fin.read(reinterpret_cast<char*>(ve.data()), ve.size() * sizeof(double));
		int r = (int)ve.back();
		ve.pop_back();
		int c = (int)ve.back();
		ve.pop_back();
		matrix m(r, c, ve);
		fin.close();
		return m;
	}



}

void matrix::center() {
	double sum = 0;
	for (int i = 0; i < this->col; i++) {
		for (int j = 0; j < this->row; j++)
			sum += this->vec[j * (this->col) + i];
		sum /= this->row;
		for (int j = 0; j < this->row; j++)
			this->vec[j * (this->col) + i] -= sum;
		sum = 0;
	}
}
void matrix::scale() {
	double sum = 0;
	for (int i = 0; i < this->col; i++) {
		double newsum = 0;
		for (int j = 0; j < this->row; j++)
			sum += this->vec[j * (this->col) + i];
		sum /= this->row;


		for (int j = 0; j < this->row; j++) {
			newsum += pow((this->vec[j * (this->col) + i] - sum), 2);
		}
		for (int j = 0; j < this->row; j++)
			this->vec[j * (this->col) + i] -= sum;

		newsum /= sum;
		newsum = pow(newsum, 0.5);
		for (int j = 0; j < this->row; j++)
			this->vec[j * (this->col) + i] /= newsum;
		sum = 0;
		newsum = 0;
	}
}