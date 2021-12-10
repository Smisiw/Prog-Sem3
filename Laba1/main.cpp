#pragma once;
#include "Polynomial.h"
#include <list>
#include <set>
#include <time.h>
#include <iostream>

using namespace std;

int main() {
	srand(clock());
	list<Polynomial> list_pol;
	set<Polynomial> set_pol;
	Polynomial target_lp, target_sp;
	float start, end;
	start = clock();
	for (int i = 0; i < 1000000; i++) {
		int size = rand() % 6;
		float* coef = new float[size + 1];
		for (int j = 0; j <= size; j++) {
			coef[j] = rand() % 100;
		}
		Polynomial pol(size, coef);
		delete coef;
		list_pol.push_back(pol);
		if (i == 500000) {
			target_lp = pol;
		}
	}
	end = clock();
	cout << "Polynomial list filling: " << (end - start) / 1000 << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++) {
		int size = rand() % 6;
		float* coef = new float[size + 1];
		for (int j = 0; j <= size; j++) {
			coef[j] = rand() % 100;
		}
		Polynomial pol(size, coef);
		delete coef;
		set_pol.insert(pol);
		if (i == 500000) {
			target_sp = pol;
		}
	}
	end = clock();
	cout << "Polynomial set filling: " << (end - start) / 1000 << endl;
	start = clock();
	for (auto iter = list_pol.begin(); iter != list_pol.end(); iter++) {
		if (*iter == target_lp) {
			break;
		}
	}
	end = clock();
	cout << "Polynomial list finding: " << (end - start) / 1000 << endl;
	start = clock();
	set_pol.find(target_sp);
	end = clock();
	cout << "Polynomial set finding: " << (end - start) / 1000 << endl;
	start = clock();
	list_pol.clear();
	end = clock();
	cout << "Polynomial list clearing: " << (end - start) / 1000 << endl;
	start = clock();
	set_pol.clear();
	end = clock();
	cout << "Polynomial set clearing: " << (end - start) / 1000 << endl;

	//Примитивный тип
	list<int> list_int;
	set<int> set_int;
	int target_li, target_si;
	start = clock();
	for (int i = 0; i < 1000000; i++) {
		int num = rand() % 1000000;
		list_int.push_back(num);
		if (i == 500000) {
			target_li = num;
		}
	}
	end = clock();
	cout << "Int list filling: " << (end - start) / 1000 << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++) {
		int num = rand() % 1000000;
		set_int.insert(num);
		if (i == 500000) {
			target_si = num;
		}
	}
	end = clock();
	cout << "Int set filling: " << (end - start) / 1000 << endl;
	start = clock();
	for (auto iter = list_int.begin(); iter != list_int.end(); iter++) {
		if (*iter == target_li) {
			break;
		}
	}
	end = clock();
	cout << "Int list finding: " << (end - start) / 1000 << endl;
	start = clock();
	set_int.find(target_si);
	end = clock();
	cout << "int set finding: " << (end - start) / 1000 << endl;
	start = clock();
	list_int.clear();
	end = clock();
	cout << "int list clearing: " << (end - start) / 1000 << endl;
	start = clock();
	set_int.clear();
	end = clock();
	cout << "int set clearing: " << (end - start) / 1000 << endl;
}