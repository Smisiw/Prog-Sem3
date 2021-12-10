#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Polynomial.h"
#include "MyFunctions.hpp"

class PolWithString : public Polynomial {
public:
	PolWithString() : Polynomial() {
		this->str = new char[2];
		this->str[0] = 0;
		this->str[1] = '\0';
	}

	PolWithString(int order, float* coefficient) : Polynomial(order, coefficient) {
		this->length = getLength();
		if (this->length == 1) {
			this->str = new char[2];
			this->str[0] = 0;
			this->str[1] = '\0';
		}
		else {
			this->str = new char[this->length];
			this->str = this->getString();
		}
	}

	PolWithString(const PolWithString& pol) : Polynomial(pol) {
		this->length = getLength();
		if (this->length == 1) {
			this->str = new char[2];
			this->str[0] = 0;
			this->str[1] = '\0';
		}
		else {
			this->str = new char[this->length];
			this->str = this->getString();
		}
	}

	int getLength() {
		int length = 1;
		bool isFirst = 1;
		for (int i = 0; i <= this->getOrder(); i++)
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
			if ((getLengthOfFloat(this->getCoefficient(i)) > 0) && i > 0) {
				length += 3 + getLengthOfInt(i);
				if (i == 1) {
					length -= 2;
				}
			}
		}
		return length;
	}

	void setCoefficient(int order, float x) {
		Polynomial::setCoefficient(order, x);
		this->length = getLength();
		this->str = new char[this->length];
		this->str = this->getString();
	}

	char* getStr() {
		char* temp = new char[length];
		sprintf(temp, this->str);
		return temp;
	}

	virtual char* toString() {
		char* str = new char[strlen(this->getString()) + 15];
		sprintf(str, "%s%s", "PolWithString:\n", this->getString());
		return str;
	}

private:
	char* str;
	int length;
};
