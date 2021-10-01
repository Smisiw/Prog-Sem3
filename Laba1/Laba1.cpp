#define CATCH_CONFIG_MAIN

#include <iostream>
#include "catch.hpp"
#include "Polynomial.h"

using namespace std;

TEST_CASE("Testing getOrder() and setCoefficient") {
	float n[4] = { -4, 3, -13, 53 };
	Polynomial pol(3, n);
	REQUIRE(pol.getOrder() == 3);
	pol.setCoefficient(3, 0);
	REQUIRE(pol.getOrder() == 2);
	pol.setCoefficient(4, 2);
	REQUIRE(pol.getOrder() == 4);
}

TEST_CASE("Testing getCoefficient() and setCoefficient") {
	float n[4] = { -17, 0, 15.5, 3 };
	Polynomial pol(3, n);
	REQUIRE(pol.getCoefficient(0) == -17);
	REQUIRE(pol.getCoefficient(1) == 0);
	REQUIRE(pol.getCoefficient(2) == 15.5f);
	REQUIRE(pol.getCoefficient(3) == 3);
	pol.setCoefficient(3, 0);
	REQUIRE(pol.getCoefficient(0) == -17);
	REQUIRE(pol.getCoefficient(1) == 0);
	REQUIRE(pol.getCoefficient(2) == 15.5f);
	pol.setCoefficient(4, 2);
	REQUIRE(pol.getCoefficient(0) == -17);
	REQUIRE(pol.getCoefficient(1) == 0);
	REQUIRE(pol.getCoefficient(2) == 15.5f);
	REQUIRE(pol.getCoefficient(3) == 0);
	REQUIRE(pol.getCoefficient(4) == 2);
}

TEST_CASE("Testing Calculation") {
	float n1[4] = { 5, 3, 1, 2 };
	Polynomial pol1(3, n1);
	REQUIRE(pol1.calculate(0) == 5);
	REQUIRE(pol1.calculate(1) == 11);
	REQUIRE(pol1.calculate(2) == 31);
	REQUIRE(pol1.calculate(3) == 77);
	float n2[4] = { 0, 3.5, -1.1, 2 };
	Polynomial pol2(3, n2);
	REQUIRE(pol2.calculate(0) == 0);
	REQUIRE(pol2.calculate(1) == 4.4f);
	REQUIRE(pol2.calculate(2) == 18.6f);
	REQUIRE(pol2.calculate(3) == 54.6f);
}

TEST_CASE("Testing Output") {
	float n1[4] = { 5, 3, 1, 2 };
	Polynomial pol1(3, n1);
	char req1[14] = "5+3x+x^2+2x^3";
	REQUIRE(!memcmp(pol1.getString(), req1, 14));
	float n2[4] = { 1, 0, 3, -5 };
	Polynomial pol2(3, n2);
	char req2[12] = "1+3x^2-5x^3";
	REQUIRE(!memcmp(pol2.getString(), req2, 12));
	float n3[4] = { 0, 0, -13, -1 };
	Polynomial pol3(3, n3);
	char req3[11] = "-13x^2-x^3";
	REQUIRE(!memcmp(pol3.getString(), req3, 11));
	float n4[4] = { 0.3, 0, -3, -11.6 };
	Polynomial pol4(3, n4);
	char req4[17] = "0.3-3x^2-11.6x^3";
	REQUIRE(!memcmp(pol4.getString(), req4, 17));
	Polynomial pol5;
	char req5[2] = "0";
	REQUIRE(!memcmp(pol5.getString(), req5, 2));
}
