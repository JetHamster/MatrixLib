#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "PCA.h"
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
#include <cmath>
using namespace std;

void PCA::showdata() {
	cout << this->data;
}
void PCA::scale() {
	this->data.scale();
}
void PCA::center() {
	this->data.center();
}

void PCA::nip() {
	this->center();
	matrix E = this->data;
	vector<double> t, tvec, pvec;
	for (int k = 0; k < this->data.col; k++) {
		for (int i = 0; i < this->data.row; i++) {
			t.push_back(this->data.vec[i * (this->data.col) + k]);
		}
		matrix tm(1, this->data.row, t);
		double sum = 0;
		for (int i = 0; i < t.size(); i++) {
			sum += t[i] * t[i];
		}
		matrix p = tm * E;
		p = p * (1 / sum);
		sum = 0;

		for (int i = 0; i < p.col; i++) {
			sum += p.vec[i] * p.vec[i];
		}

		p = p * pow((1 / sum), 0.5);
		p = p.transpose();
		matrix tt = E * p;
		tt = tt * (1 / sum);
		p = p.transpose();
		matrix l = tt * p;
		E = E - l;
		for (int i = 0; i < tt.vec.size(); i++) {
			tvec.push_back(tt.vec[i]);
		}
		for (int i = 0; i < p.vec.size(); i++) {
			pvec.push_back(p.vec[i]);
		}
	}
	matrix T(this->data.row, this->data.col, tvec);
	matrix P(this->data.col, this->data.col, pvec);
	this->P = P;
	this->T = T;
}