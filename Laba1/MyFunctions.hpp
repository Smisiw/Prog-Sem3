#pragma once
#include <iostream>

using namespace std;

int getLengthOfInt(int value) {
	int length = 0;
	while (value != 0) {
		value /= 10;
		length++;
	}
	return length;
}

int getLengthOfFloat(float value) {
	int length = 0;
	if (value - (int)value != 0) {
		int val_i = abs((int)value);
		float val_f = abs(value - (int)value);
		length += 2;
		if (val_i == 0) {
			length++;
		}
		while (val_i > 0) {
			val_i /= 10;
			length++;
		}
		for (int i = 0; (val_f > 0) && (i < 1); i++) {
			val_f *= 10;
			val_f -= (int)val_f;
			length++;
		}
	}
	else {
		int val = abs((int)value);
		while (val > 0) {
			val /= 10;
			length++;
		}
	}
	return length;
}
