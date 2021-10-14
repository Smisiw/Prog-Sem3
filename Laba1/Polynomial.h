
#include <iostream>
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
		if (order < 0) {
			throw exception("Order < 0");
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
		this->coefficient = new float[order + 1];
		for (int i = 0; i <= order; i++) {
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
		if (order < 0) {
			throw exception("Order < 0");
		}
		//Замена коэффициента до высшего порядка
		if ((this->order > order) && (order > 0) || (this->order == order) && (x != 0)) {
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
				else  if (this->coefficient[i] < 0) {
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
			return addition(pol1, pol2);
		}
		else {
			return addition(pol2, pol1);
		}
	}

	friend const Polynomial& addition(Polynomial &pol1, Polynomial &pol2) {
		float* coef = new float[pol1.order];
		for (int i = 0; i <= pol1.order; i++)
		{
			coef[i] = pol1.coefficient[i];
			if (i <= pol2.order) {
				coef[i] += pol2.coefficient[i];
			}
		}
		Polynomial* result = new Polynomial(pol1.order, coef);
		if (coef[pol1.order] == 0) {
			result->setCoefficient(pol1.order, 0); //Костыль для удаления лишних нулей
		}
		return *result;
	}

	friend const Polynomial& operator - (Polynomial& pol1, Polynomial& pol2) {
		if (pol1.order >= pol2.order) {
			return subtraction(pol1, pol2, false);
		}
		else {
			return subtraction(pol2, pol1, true);
		}
	}

	friend const Polynomial& subtraction(Polynomial& pol1, Polynomial& pol2, bool isSwapped) {
		float* coef = new float[pol1.order];
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
		Polynomial* result = new Polynomial(pol1.order, coef);
		if (coef[pol1.order] == 0) {
			result->setCoefficient(pol1.order, 0);
		}
		return *result;
	}

	float operator () (float x) {
		return this->calculate(x);
	}

	float& operator [] (unsigned i) {
		if (i > this->order) {
			throw exception("Out of array");
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

private:
	int order;
	float* coefficient;
	static int count;
};

int Polynomial::count = 0;
