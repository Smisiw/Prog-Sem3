#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <fstream>
#include "MyFunctions.hpp"

class Polynomial {
public:
	//Конструктор по умолчанию
	Polynomial() {
		this->order = 0;
		this->coefficient = new float[1];
		this->coefficient[0] = 0;
		count += 1;
	}
	//Конструктор с параметрами
	Polynomial(int order, float* coefficient) {
		try {
			if (order < 0) {
				throw exception("Order < 0");
			}
		}
		catch(const exception ex) {
			cerr << ex.what() << endl;
			exit(1);
		}
		this->order = order;
		this->coefficient = new float[order + 1];
		for (int i = 0; i <= order; i++) {
			this->coefficient[i] = coefficient[i];
		}
		count += 1;
	}
	//Конструктор копирования
	Polynomial(const Polynomial& pol) {
		this->order = pol.order;
		this->coefficient = new float[this->order + 1];
		for (int i = 0; i <= this->order; i++) {
			this->coefficient[i] = pol.coefficient[i];
		}
		count += 1;
	}
	//Деструктор
	~Polynomial() {
		delete this->coefficient;
		count -= 1;
	}

	float calculate(float x) {
		float sum = 0;
		for (int i = 0; i <= this->order; i++) {
			float term = 1;
			for (int j = 0; j < i; j++) {
				term *= x;
			}
			sum += term * coefficient[i];
		}
		return sum;
	}

	void setCoefficient(int order, float x) {
		try {
			if (order < 0) {
				throw exception("Order < 0");
			}
		}
		catch (const exception ex) {
			cerr << ex.what() << endl;
			exit(1);
		}
		//Замена коэффициента до высшего порядка
		if ((this->order > order) && (order >= 0) || (this->order == order) && (x != 0)) {
			this->coefficient[order] = x;
		}
		//Добавление нового порядка
		else if ((this->order < order) && (order > 0) && (x != 0)) {
			float* temp = new float[this->order + 1];
			for (int i = 0; i <= this->order; i++) {
				temp[i] = this->coefficient[i];
			}
			delete this->coefficient;
			this->coefficient = new float[order + 1];
			for (int i = 0; i <= this->order; i++)
			{
				this->coefficient[i] = temp[i];
			}
			for (int i = this->order + 1; i < order; i++)
			{
				this->coefficient[i] = 0;
			}
			this->coefficient[order] = x;
			this->order = order;
			delete temp;
		}
		//Удаление высшего порядка
		else if ((this->order = order) && (x == 0) && (order != 0)) {
			//Если перед высшим порядком отсутствовал один или больше порядков удаляем и их
			for (order--; (this->coefficient[order] == 0) && (order > 0); order--);
			float* temp = new float[order + 1];
			for (int i = 0; i <= order; i++) {
				temp[i] = this->coefficient[i];
			}
			delete this->coefficient;
			this->coefficient = new float[order + 1];
			for (int i = 0; i <= order; i++)
			{
				this->coefficient[i] = temp[i];
			}
			this->order = order;
			delete temp;
		}
	}

	char* getString() {
		//расчет длинны
		int length = 1;
		bool isFirst = 1;
		for (int i = 0; i <= this->order; i++)
		{
			if ((this->coefficient[i] < 0) && isFirst) {
				isFirst = 0;
			}
			else if ((this->coefficient[i] > 0) && isFirst) {
				length--;
				isFirst = 0;
			}
			if (i == 0 || abs(this->coefficient[i]) != 1) {
				length += getLengthOfFloat(this->coefficient[i]);
			}
			if ((getLengthOfFloat(this->coefficient[i]) > 0) && i > 0) {
				length += 3 + getLengthOfInt(i);
				if (i == 1) {
					length -= 2;
				}
			}
		}
		//запись в массив символов
		isFirst = 1;
		if (length == 1) {
			char* str = new char[2];
			str[0] = '0';
			str[1] = '\0';
			return str;
		}
		else {
			char* str = new char[length];
			int len = 0;
			for (int i = 0; i <= this->order; i++)
			{
				//Запись знака
				if ((this->coefficient[i] > 0) && isFirst) {
					isFirst = 0;
				}
				else if (this->coefficient[i] > 0) {
					str[len++] = '+';
				}
				else  if (this->coefficient[i] < 0 && isFirst) {
					str[len++] = '-';
					isFirst = 0;
				}
				else if (this->coefficient[i] < 0) {
					str[len++] = '-';
				}

				if (this->coefficient[i] != 0)
				{
					//Запись целых чисел
					if (this->coefficient[i] - (int)this->coefficient[i] == 0 && (abs(this->coefficient[i]) != 1 || i == 0)) {
						for (int j = getLengthOfInt((int)this->coefficient[i]) - 1; j >= 0; j--) {
							str[len++] = (abs((int)this->coefficient[i]) / (int)pow(10, j)) % (int)pow(10, j + 1) + '0';
						}
					}
					//Запись вещественных чисел
					else if (this->coefficient[i] - (int)this->coefficient[i] != 0) {
						char* temp = new char[getLengthOfFloat(this->coefficient[i])];
						int reg = snprintf(temp, getLengthOfFloat(this->coefficient[i]), "%f", abs(this->coefficient[i]));
						for (int j = 0; j < getLengthOfFloat(this->coefficient[i]) - 1; j++)
						{
							str[len++] = temp[j];
						}
						delete temp;
					}
					//Запись иксов и их степени
					if (i > 0) {
						str[len++] = 'x';
						if (i > 1) {
							str[len++] = '^';
							for (int j = getLengthOfInt(i) - 1; j >= 0; j--) {
								str[len++] = i / pow(10, j) + '0';
							}
						}
					}
				}
			}
			str[len++] = '\0';
			return str;
		}

	}

	float getCoefficient(int order) {
		if (order <= this->order && order >=0) {
			return this->coefficient[order];
		}
		else return 0;
	}

	int getOrder() {
		return this->order;
	}

	static int getCount() {
		return count;
	}

	const Polynomial& operator ++ () {
		float* temp = new float[this->order + 1];
		for (int i = 0; i <= this->order; i++) {
			temp[i] = this->coefficient[i];
		}
		this->order++;
		delete this->coefficient;
		this->coefficient = new float[this->order + 1];
		this->coefficient[0] = 0;
		for (int i = 1; i <= this->order; i++) {
			this->coefficient[i] = temp[i - 1];
		}
		return *this;
	}

	const Polynomial& operator -- () {
		try {
			if (this->order == 0) {
				throw exception("Order = 0");
			}
		}
		catch (const exception ex) {
			cerr << ex.what() << endl;
			return *this;
		}
		float* temp = new float[this->order + 1];
		for (int i = 0; i <= this->order; i++) {
			temp[i] = this->coefficient[i];
		}
		this->order--;
		delete this->coefficient;
		this->coefficient = new float[this->order + 1];
		for (int i = 0; i <= this->order; i++) {
			this->coefficient[i] = temp[i + 1];
		}
		return *this;
	}

	friend const Polynomial& operator + (Polynomial &pol1, Polynomial &pol2) {
		if (pol1.order >= pol2.order) {
			return add(pol1, pol2);
		}
		else {
			return add(pol2, pol1);
		}
	}

	friend const Polynomial& add(Polynomial &pol1, Polynomial &pol2) {
		float* coef = new float[pol1.order];
		int order = pol1.order;
		for (int i = 0; i <= pol1.order; i++)
		{
			coef[i] = pol1.coefficient[i];
			if (i <= pol2.order) {
				coef[i] += pol2.coefficient[i];
			}
		}
		if (coef[pol1.order] == 0) {
			for (order--; (coef[order] == 0) && (order > 0); order--);
			float* temp = new float[order + 1];
			for (int i = 0; i <= order; i++) {
				temp[i] = coef[i];
			}
			Polynomial* result = new Polynomial(order, temp);
			return *result;
		}
		Polynomial* result = new Polynomial(order, coef);
		return *result;
	}

	friend const Polynomial& operator - (Polynomial& pol1, Polynomial& pol2) {
		if (pol1.order >= pol2.order) {
			return subtract(pol1, pol2, false);
		}
		else {
			return subtract(pol2, pol1, true);
		}
	}

	friend const Polynomial& subtract(Polynomial& pol1, Polynomial& pol2, bool isSwapped) {
		float* coef = new float[pol1.order];
		int order = pol1.order;
		for (int i = 0; i <= pol1.order; i++)
		{
			if (isSwapped) {
				coef[i] = -pol1.coefficient[i];
			}
			else {
				coef[i] = pol1.coefficient[i];
			}
			if (i <= pol2.order && isSwapped) {
				coef[i] += pol2.coefficient[i];
			}
			else if (i <= pol2.order && !isSwapped) {
				coef[i] -= pol2.coefficient[i];
			}
		}
		if (coef[pol1.order] == 0) {
			for (order--; (coef[order] == 0) && (order > 0); order--);
			float* temp = new float[order + 1];
			for (int i = 0; i <= order; i++) {
				temp[i] = coef[i];
			}
			Polynomial* result = new Polynomial(order, temp);
			return *result;
		}
		Polynomial* result = new Polynomial(order, coef);
		return *result;
	}

	float operator () (float x) {
		return this->calculate(x);
	}

	float& operator [] (unsigned i) {
		try {
			if (i > this->order) {
				throw exception("Out of array");
			}
		}
		catch (const exception ex) {
			cerr << ex.what() << endl;
			exit(1);
		}
		return this->coefficient[i];
	}

	const Polynomial& operator = (const Polynomial &pol) {
		delete this->coefficient;
		this->order = pol.order;
		this->coefficient = new float[this->order + 1];
		for (int i = 0; i <= order; i++) {
			this->coefficient[i] = pol.coefficient[i];
		}
		return *this;
	}

	ofstream& writeToBin(ofstream& fout, Polynomial& pol) {
		try {
			if (!fout.is_open()) {
				throw exception("Unable to open this file.");
			}
		}
		catch(const exception ex) {
			cerr << ex.what() << endl;
			exit(1);
		}
		fout.write((char*)&pol.order, sizeof(int));
		for (int i = 0; i <= pol.order; i++) {
			fout.write((char*)&pol.coefficient[i], sizeof(float));
		}
		return fout;
	}

	ifstream& readFromBin(ifstream& fin, Polynomial& pol) {
		try {
			if (!fin.is_open()) {
				throw exception("Unable to open this file.");
			}
		}
		catch(const exception ex) {
			cerr << ex.what() << endl;
			exit(1);
		}
		float coef = 0;
		int order;
		fin.read((char*)&order, sizeof(int));
		for (int i = 0; i <= order; i++) {
			fin.read((char*)&coef, sizeof(float));
			pol.setCoefficient(i, coef);
		}
		return fin;
	}

	friend ostream& operator << (ostream& os, Polynomial& pol) {
		os << pol.getString() << endl;
		return os;
	}

	friend istream& operator >> (istream& is, Polynomial& pol) {
		int order, left = 0, right = 0;
		float coef;
		char str[100];
		is >> str;
		if (str[0] == '-') {
			left = 1;
			right = 1;
		}
		do {
			right++;
			if (str[right] == '+' || str[right] == '-' || str[right] == '\0') {
				int i = left;
				while (str[i] != 'x' && i != right)
					i++;
				if (str[i] == 'x') {
					if (i == left) {
						coef = 1;
					}
					else {
						char tempstr[15];
						char* ptr = str;
						ptr += left;
						strncpy_s(tempstr, ptr, i - left);
						coef = atof(tempstr);
					}
					if (right - i == 1) {
						order = 1;
					}
					else {
						i += 2;
						char tempstr[15];
						char* ptr = str;
						ptr += i;
						strncpy_s(tempstr, ptr, right - i);
						order = atoi(tempstr);
					}
				}
				else if (i == right) {
					order = 0;
					char tempstr[15];
					char* ptr = str;
					ptr += left;
					strncpy_s(tempstr, ptr, right - left);
					coef = atof(tempstr);
				}
				if (left != 0 && str[left - 1] == '-') {
					coef *= -1;
				}
				pol.setCoefficient(order, coef);
				left = right + 1;
			}
		} while (str[right] != '\0' && right != 99);
		return is;
	}

	friend bool operator < (const Polynomial& pol1, const Polynomial& pol2) {
		if (pol1.order < pol2.order) {
			return true;
		}
		else if (pol1.order > pol2.order) {
			return false;
		}
		else {
			for (int i = pol1.order; i >= 0; i--) {
				if (pol1.coefficient[i] < pol2.coefficient[i]) {
					return true;
				}
				else if (pol1.coefficient[i] > pol2.coefficient[i]) {
					return false;
				}
			}
			return false;
		}
	}

	friend bool operator > (const Polynomial& pol1, const Polynomial& pol2) {
		if (pol1.order > pol2.order) {
			return true;
		}
		else if (pol1.order < pol2.order) {
			return false;
		}
		else {
			for (int i = pol1.order; i >= 0; i--) {
				if (pol1.coefficient[i] > pol2.coefficient[i]) {
					return true;
				}
				else if (pol1.coefficient[i] < pol2.coefficient[i]) {
					return false;
				}
			}
			return false;
		}
	}

	friend bool operator == (const Polynomial& pol1, const Polynomial& pol2) {
		if (pol1.order == pol2.order) {
			bool equal = true;
			for (int i = 0; i <= pol1.order; i++) {
				if (pol1.coefficient[i] != pol2.coefficient[i]) {
					equal = false;
					break;
				}
			}
			return equal;
		}
		else {
			return false;
		}
	}

	virtual char* toString() {
		char* str = new char[strlen(this->getString()) + 12];
		sprintf(str, "%s%s", "Polynomial:\n", this->getString());
		return str;
	}

	int getSize() {
		return strlen(this->toString());
	}

protected:
	void editCoefficient(int order, float x) {
		if (order < this->order) {
			this->coefficient[order] = x;
		}
		else {
			float* temp = new float[this->order + 1];
			for (int i = 0; i <= this->order; i++) {
				temp[i] = this->coefficient[i];
			}
			delete this->coefficient;
			this->order++;
			this->coefficient = new float[this->order + 1];
			for (int i = 0; i < this->order; i++) {
				this->coefficient[i] = temp[i];
			}
			this->coefficient[this->order] = x;
		}
	}

private:
	int order;
	float* coefficient;
	static int count;
};

int Polynomial::count = 0;
