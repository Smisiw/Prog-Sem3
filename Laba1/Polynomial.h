
#include <iostream>
#include "MyFunctions.hpp"

class Polynomial {
public:
	//����������� �� ���������
	Polynomial() {
		this->order = 0;
		this->coefficient = new float[1];
		this->coefficient[0] = 0;
		count += 1;
	}
	//����������� � �����������
	Polynomial(int order, float* coefficient) {
		this->order = order;
		this->coefficient = new float[order + 1];
		for (int i = 0; i <= order; i++) {
			this->coefficient[i] = coefficient[i];
		}
		count += 1;
	}
	//����������� �����������
	Polynomial(const Polynomial& pol) {
		this->order = pol.order;
		this->coefficient = new float[order + 1];
		for (int i = 0; i <= order; i++) {
			this->coefficient[i] = coefficient[i];
		}
		count += 1;
	}
	//����������
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
		//������ ������������ �� ������� �������
		if ((this->order > order) && (order > 0) || (this->order == order) && (x != 0)) {
			this->coefficient[order] = x;
		}
		//���������� ������ �������
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
		//�������� ������� �������
		else if ((this->order = order) && (x == 0) && (order != 0)) {
			//���� ����� ������ �������� ������������ ���� ��� ������ �������� ������� � ��
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
		//������ ������
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
		//������ � ������ ��������
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
				//������ �����
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
					//������ ����� �����
					if (this->coefficient[i] - (int)this->coefficient[i] == 0 && (abs(this->coefficient[i]) != 1 || i == 0)) {
						for (int j = getLengthOfInt((int)this->coefficient[i]) - 1; j >= 0; j--) {
							str[len++] = (abs((int)this->coefficient[i]) / (int)pow(10, j)) % (int)pow(10, j + 1) + '0';
						}
					}
					//������ ������������ �����
					else if (this->coefficient[i] - (int)this->coefficient[i] != 0) {
						char* temp = new char[getLengthOfFloat(this->coefficient[i])];
						int reg = snprintf(temp, getLengthOfFloat(this->coefficient[i]), "%f", abs(this->coefficient[i]));
						for (int j = 0; j < getLengthOfFloat(this->coefficient[i]) - 1; j++)
						{
							str[len++] = temp[j];
						}
						delete temp;
					}
					//������ ����� � �� �������
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

private:
	int order;
	float* coefficient;
	static int count;
};

int Polynomial::count = 0;