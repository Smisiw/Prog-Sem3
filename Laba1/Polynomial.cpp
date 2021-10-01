#include "Polynomial.h"

class Polynomial {
public:
	//Конструктор по умолчанию
	Polynomial() {
		this->order = 0;
		this->coefficient = new float[1];
		this->coefficient[0] = 0;
		toString();
		count += 1;
	}
	//Конструктор с параметрами
	Polynomial(int order, float* coefficient) {
		this->order = order;
		this->coefficient = new float[order + 1];
		for (int i = 0; i <= order; i++) {
			this->coefficient[i] = coefficient[i];
		}
		toString();
		count += 1;
	}
	//Конструктор копирования
	Polynomial(const Polynomial& pol) {
		this->order = pol.order;
		this->coefficient = new float[order + 1];
		for (int i = 0; i <= order; i++) {
			this->coefficient[i] = coefficient[i];
		}
		toString();
		count += 1;
	}
	//Деструктор
	~Polynomial() {
		delete this->coefficient;
		//delete this->str;
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
		//Замена коэффициента до высшего порядка
		if ((this->order > order) || (this->order == order) && (x != 0)) {
			this->coefficient[order] = x;
		}
		//Добавление нового порядка
		else if ((this->order < order) && (x != 0)) {
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
		delete this->str;
		toString();
	}

	void toString() {
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
			this->str = new char[2];
			this->str[0] = '0';
			this->str[1] = '\0';
			this->strLength = 2;
		}
		else {
			this->str = new char[length];
			int len = 0;
			for (int i = 0; i <= this->order; i++)
			{
				//Запись знака
				if ((this->coefficient[i] > 0) && isFirst) {
					isFirst = 0;
				}
				else if (this->coefficient[i] > 0) {
					this->str[len++] = '+';
				}
				else  if (this->coefficient[i] < 0) {
					this->str[len++] = '-';
				}

				if (this->coefficient[i] != 0)
				{
					//Запись целых чисел
					if (this->coefficient[i] - (int)this->coefficient[i] == 0 && (abs(this->coefficient[i]) != 1 || i == 0)) {
						for (int j = getLengthOfInt((int)this->coefficient[i]) - 1; j >= 0; j--) {
							this->str[len++] = (abs((int)this->coefficient[i]) / (int)pow(10, j)) % (int)pow(10, j + 1) + '0';
						}
					}
					//Запись вещественных чисел
					else if (this->coefficient[i] - (int)this->coefficient[i] != 0) {
						char* temp = new char[getLengthOfFloat(this->coefficient[i])];
						int reg = snprintf(temp, getLengthOfFloat(this->coefficient[i]), "%f", abs(this->coefficient[i]));
						for (int j = 0; j < getLengthOfFloat(this->coefficient[i]) - 1; j++)
						{
							this->str[len++] = temp[j];
						}
						delete temp;
					}
					//Запись иксов и их степени
					if (i > 0) {
						this->str[len++] = 'x';
						if (i > 1) {
							this->str[len++] = '^';
							for (int j = getLengthOfInt(i) - 1; j >= 0; j--) {
								this->str[len++] = i / pow(10, j) + '0';
							}
						}
					}
				}
			}
			this->str[len++] = '\0';
			this->strLength = len;
		}
	}

	char* getString() {
		char* output = new char[this->strLength];
		for (int i = 0; i < this->strLength; i++) {
			output[i] = this->str[i];
		}
		return output;
	}

	float getCoefficient(int order) {
		if (order <= this->order) {
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

private:
	int order;
	float* coefficient;
	static int count;
	char* str;
	int strLength;
};

int Polynomial::count = 0;
