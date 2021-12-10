#pragma once
#include "Polynomial.h"

class PolWithDegree : public Polynomial {
public:
	PolWithDegree() : Polynomial() {
		this->degree = new int[1];
		this->degree[0] = 0;
		this->maxorder = 0;
	}

	PolWithDegree(int order, float* coefficient) : Polynomial(order, coefficient) {
		this->degree = new int[order + 1];
		for (int i = 0; i <= order; i++) {
			this->degree[i] = i;
		}
		this->maxorder = order;
	}

	PolWithDegree(PolWithDegree& pol) : Polynomial(pol) {
		this->degree = new int[((Polynomial*)this)->getOrder() + 1];
		for (int i = 0; i <= ((Polynomial*)this)->getOrder(); i++) {
			this->degree[i] = pol.degree[i];
		}
		this->maxorder = pol.maxorder;
	}

	~PolWithDegree() {
		delete this->degree;
	}

	void setCoefficient(int order, float x) {
		bool is_exist = false;
		int p;
		for (int i = 0; i <= order; i++) {
			if (this->degree[i] == order) {
				p = i;
				is_exist = true;
				break;
			}
		}
		if (is_exist) {
			this->editCoefficient(p, x);
		}
		else {
			this->editCoefficient(((Polynomial*)this)->getOrder() + 1, x);
			int* temp = new int[((Polynomial*)this)->getOrder()];
			for (int i = 0; i < ((Polynomial*)this)->getOrder(); i++) {
				temp[i] = this->degree[i];
			}
			delete this->degree;
			this->degree = new int[((Polynomial*)this)->getOrder() + 1];
			for (int i = 0; i < ((Polynomial*)this)->getOrder(); i++) {
				this->degree[i] = temp[i];
			}
			this->degree[((Polynomial*)this)->getOrder()] = order;
			if (this->maxorder < order) {
				this->maxorder = order;
			}
		}
	}

	char* getString() {
		//расчет длинны
		int length = 1;
		bool isFirst = 1;
		for (int i = 0; i <= ((Polynomial*)this)->getOrder(); i++)
		{
			if ((this->getCoefficient(i) < 0) && isFirst) {
				isFirst = 0;
			}
			else if ((this->getCoefficient(i) > 0) && isFirst) {
				length--;
				isFirst = 0;
			}
			if (i == 0 || abs(this->getCoefficient(i)) != 1) {
				length += getLengthOfFloat(this->getCoefficient(i));
			}
			if ((getLengthOfFloat(this->getCoefficient(i)) > 0) && this->degree[i] > 0) {
				length += 3 + getLengthOfInt(this->degree[i]);
				if (this->degree[i] == 1) {
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
			for (int i = 0; i <= ((Polynomial*)this)->getOrder(); i++)
			{
				//Запись знака
				if ((this->getCoefficient(i) > 0) && isFirst) {
					isFirst = 0;
				}
				else if (this->getCoefficient(i) > 0) {
					str[len++] = '+';
				}
				else  if (this->getCoefficient(i) < 0 && isFirst) {
					str[len++] = '-';
					isFirst = 0;
				}
				else if (this->getCoefficient(i) < 0) {
					str[len++] = '-';
				}

				if (this->getCoefficient(i) != 0)
				{
					//Запись целых чисел
					if (this->getCoefficient(i) - (int)this->getCoefficient(i) == 0 && (abs(this->getCoefficient(i)) != 1 || i == 0)) {
						for (int j = getLengthOfInt((int)this->getCoefficient(i)) - 1; j >= 0; j--) {
							str[len++] = (abs((int)this->getCoefficient(i)) / (int)pow(10, j)) % (int)pow(10, j + 1) + '0';
						}
					}
					//Запись вещественных чисел
					else if (this->getCoefficient(i) - (int)this->getCoefficient(i) != 0) {
						char* temp = new char[getLengthOfFloat(this->getCoefficient(i))];
						int reg = snprintf(temp, getLengthOfFloat(this->getCoefficient(i)), "%f", abs(this->getCoefficient(i)));
						for (int j = 0; j < getLengthOfFloat(this->getCoefficient(i)) - 1; j++)
						{
							str[len++] = temp[j];
						}
						delete temp;
					}
					//Запись иксов и их степени
					if (this->degree[i] > 0) {
						str[len++] = 'x';
						if (this->degree[i] > 1) {
							str[len++] = '^';
							for (int j = getLengthOfInt(this->degree[i]) - 1; j >= 0; j--) {
								str[len++] = this->degree[i] / pow(10, j) + '0';
							}
						}
					}
				}
			}
			str[len++] = '\0';
			return str;
		}

	}

	float calculate(float x) {
		float sum = 0;
		for (int i = 0; i <= ((Polynomial*)this)->getOrder(); i++) {
			float term = 1;
			for (int j = 0; j < this->degree[i]; j++) {
				term *= x;
			}
			sum += term * this->getCoefficient(i);
		}
		return sum;
	}

	int getDegree(int order) {
		try {
			if (((Polynomial*)this)->getOrder() < order) {
				throw exception("Out of array");
			}
			return this->degree[order];
		}
		catch (const exception ex) {
			cerr << ex.what() << endl;
			exit(1);
		}
	}

	int getOrder() {
		return this->maxorder;
	}

	virtual char* toString() {
		char* str = new char[strlen(this->getString()) + 15];
		sprintf(str, "%s%s", "PolWithDegree:\n", this->getString());
		return str;
	}

private:
	int* degree;
	int maxorder;
};