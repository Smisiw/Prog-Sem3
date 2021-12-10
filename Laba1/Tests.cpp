#define CATCH_CONFIG_MAIN
#define _CRT_SECURE_NO_WARNINGS

#pragma once
#include <iostream>
#include <fstream>
#include "catch.hpp"
#include "Polynomial.h"
#include "PolWithDegree.h"
#include "PolWithString.h"
#include "QueueClass.hpp"
#include "TQueueClass.h"

using namespace std;


//Тесты к первой лабе
TEST_CASE("Testing getOrder() and setCoefficient()") {
	float n[4] = { -4, 3, -13, 53 };
	Polynomial pol(3, n);
	REQUIRE(pol.getOrder() == 3);
	pol.setCoefficient(3, 0);
	REQUIRE(pol.getOrder() == 2);
	pol.setCoefficient(4, 2);
	REQUIRE(pol.getOrder() == 4);
}

TEST_CASE("Testing getCoefficient() and setCoefficient()") {
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

//Тесты ко второй лабе
TEST_CASE("Testing ++") {
	float n[3] = {1, 2, 3};
	Polynomial pol(2, n);
	++pol;
	REQUIRE(pol.getOrder()==3);
	REQUIRE(pol.getCoefficient(0) == 0);
	REQUIRE(pol.getCoefficient(1) == 1);
	REQUIRE(pol.getCoefficient(2) == 2);
	REQUIRE(pol.getCoefficient(3) == 3);
}

TEST_CASE("Testing --") {
	float n[3] = { 1, 2, 3 };
	Polynomial pol(2, n);
	--pol;
	REQUIRE(pol.getOrder() == 1);
	REQUIRE(pol.getCoefficient(0) == 2);
	REQUIRE(pol.getCoefficient(1) == 3);
}

TEST_CASE("Testing =") {
	float n1[3] = { 1, 2, 3 };
	Polynomial pol1(2, n1);
	float n2[2] = { 6, 5 };
	Polynomial pol2(1, n2);
	pol2 = pol1;
	REQUIRE(pol2.getOrder() == 2);
	REQUIRE(pol2.getCoefficient(0) == 1);
	REQUIRE(pol2.getCoefficient(1) == 2);
	REQUIRE(pol2.getCoefficient(2) == 3);

}

TEST_CASE("Testing +") {
	float n1[3] = { 1, 2, 3 };
	Polynomial pol1(2, n1);
	float n2[3] = { 4, 5, 6 };
	Polynomial pol2(2, n2);
	Polynomial pol = pol1 + pol2;
	REQUIRE(pol.getOrder() == 2);
	REQUIRE(pol.getCoefficient(0) == 5);
	REQUIRE(pol.getCoefficient(1) == 7);
	REQUIRE(pol.getCoefficient(2) == 9);
	float n3[5] = { 14.1f, 22, 3, 4, 5 };
	pol1 = Polynomial(4, n3);
	float n4[5] = { 1, 2, -3, -4, -5 };
	pol2 = Polynomial(4, n4);
	pol = pol1 + pol2;
	REQUIRE(pol.getOrder() == 1);
	REQUIRE(pol.getCoefficient(0) == 15.1f);
	REQUIRE(pol.getCoefficient(1) == 24);
}

TEST_CASE("Testing -") {
	float n1[3] = { 1, 2, 3 };
	Polynomial pol1(2, n1);
	float n2[3] = { 6, 5, 4 };
	Polynomial pol2(2, n2);
	Polynomial pol = pol1 - pol2;
	REQUIRE(pol.getOrder() == 2);
	REQUIRE(pol.getCoefficient(0) == -5);
	REQUIRE(pol.getCoefficient(1) == -3);
	REQUIRE(pol.getCoefficient(2) == -1);
	float n3[5] = { 35.4f, 12, 3, 4, 5 };
	pol1 = Polynomial(4, n3);
	float n4[5] = { 1, 2, 3, 4, 5 };
	pol2 = Polynomial(4, n4);
	pol = pol1 - pol2;
	REQUIRE(pol.getOrder() == 1);
	REQUIRE(pol.getCoefficient(0) == 34.4f);
	REQUIRE(pol.getCoefficient(1) == 10);
}

TEST_CASE("Testing ()") {
	float n[3] = { 1, 2, 3 };
	Polynomial pol(2, n);
	REQUIRE(pol(2)==17);
}

TEST_CASE("Testing []") {
	float n[3] = { 1, 2, 3 };
	Polynomial pol(2, n);
	REQUIRE(pol[0]==1);
	REQUIRE(pol[1]==2);
	REQUIRE(pol[2]==3);
}

//Тесты к третьей лабе

TEST_CASE("Testig binary input, output") {
	float n1[3] = { 1, 2, 3 };
	Polynomial pol1(2, n1), pol2;
	ofstream fout("Polynomial.dat", ios::out | ios::binary);
	pol1.writeToBin(fout, pol1);
	fout.close();
	ifstream fin("Polynomial.dat", ios::in | ios::binary);
	pol2.readFromBin(fin, pol2);
	fin.close();
	REQUIRE(pol2.getOrder() == 2);
	REQUIRE(pol2[0]==1);
	REQUIRE(pol2[1]==2);
	REQUIRE(pol2[2]==3);
}

TEST_CASE("Testing input, output") {
	float n1[5] = { -3, -1, 0, 0, 3.5 };
	Polynomial pol1(4, n1), pol2;
	fstream fout("Polynomial.txt", ios::out);
	fout << pol1;
	fout.close();
	fstream fin("Polynomial.txt", ios::in);
	fin >> pol2;
	fin.close();
	REQUIRE(pol2.getOrder() == 4);
	REQUIRE(pol2[0]==-3);
	REQUIRE(pol2[1]==-1);
	REQUIRE(pol2[2]==0);
	REQUIRE(pol2[3]==0);
	REQUIRE(pol2[4]==3.5);
}

//Тесты к четвертой лабе

TEST_CASE("Testing PolWithString") {
	float n[4] = { -4, 3, -13, 53 };
	PolWithString pol(3, n);
	REQUIRE(pol.getOrder() == 3);
	REQUIRE(pol[0] == -4);
	REQUIRE(pol[1] == 3);
	REQUIRE(pol[2] == -13);
	REQUIRE(pol[3] == 53);
	pol.setCoefficient(3, 0);
	REQUIRE(pol.getOrder() == 2);
	REQUIRE(pol[0] == -4);
	REQUIRE(pol[1] == 3);
	REQUIRE(pol[2] == -13);
	REQUIRE(pol.calculate(2) == -50);
	char req[] = "-4+3x-13x^2";
	REQUIRE(!memcmp(pol.getStr(), req, 12));
}

TEST_CASE("Testing PolWithDegree") {
	float n[4] = { -4, 3, -13, 5 };
	PolWithDegree pol(3, n);
	REQUIRE(pol.getOrder() == 3);
	REQUIRE(pol[0] == -4);
	REQUIRE(pol[1] == 3);
	REQUIRE(pol[2] == -13);
	REQUIRE(pol[3] == 5);
	pol.setCoefficient(2, 1);
	REQUIRE(pol.getOrder() == 3);
	REQUIRE(pol[0] == -4);
	REQUIRE(pol[1] == 3);
	REQUIRE(pol[2] == 1);
	REQUIRE(pol[3] == 5);
	pol.setCoefficient(6, 2);
	REQUIRE(pol.getOrder() == 6);
	REQUIRE(pol[0] == -4);
	REQUIRE(pol[1] == 3);
	REQUIRE(pol[2] == 1);
	REQUIRE(pol[3] == 5);
	REQUIRE(pol[4] == 2);
	REQUIRE(pol.calculate(2) == 174);
	char req[] = "-4+3x+x^2+5x^3+2x^6";
	REQUIRE(!memcmp(pol.getString(), req, 20));
	REQUIRE(pol.getDegree(4) == 6);
}

//Тесты к пятой лабе

TEST_CASE("Testing Queue") {
	Queue q;
	float n1[3] = { 1, 4 ,5 };
	float n2[4] = { 1, 2, 3, 4 };
	float n3[2] = { 5, 1 };
	Polynomial pol1(2, n1);
	PolWithDegree pol2(3, n2);
	PolWithString pol3(1, n3);
	REQUIRE(q.empty() == true);
	REQUIRE(q.size() == 0);
	q.push(pol1);
	REQUIRE(q.empty() == false);
	REQUIRE(q.size() == 1);
	q.push(pol2);
	REQUIRE(q.empty() == false);
	REQUIRE(q.size() == 2);
	q.push(pol3);
	REQUIRE(q.empty() == false);
	REQUIRE(q.size() == 3);
	Polynomial pol11(*q.pop());
	REQUIRE(q.empty() == false);
	REQUIRE(q.size() == 2);
	Polynomial* pol22;
	pol22 = q.pop();
	REQUIRE(q.empty() == false);
	REQUIRE(q.size() == 1);
	Polynomial* pol33;
	pol33 = q.pop();
	REQUIRE(q.empty() == true);
	REQUIRE(q.size() == 0);
	REQUIRE(pol11.getOrder() == 2);
	REQUIRE(pol11.getCoefficient(0) == 1);
	REQUIRE(pol11.getCoefficient(1) == 4);
	REQUIRE(pol11.getCoefficient(2) == 5);
	REQUIRE(pol22->getOrder() == 3);
	REQUIRE(pol22->getCoefficient(0) == 1);
	REQUIRE(pol22->getCoefficient(1) == 2);
	REQUIRE(pol22->getCoefficient(2) == 3);
	REQUIRE(pol22->getCoefficient(3) == 4);
	REQUIRE(pol33->getOrder() == 1);
	REQUIRE(pol33->getCoefficient(0) == 5);
	REQUIRE(pol33->getCoefficient(1) == 1);
	REQUIRE(!memcmp(pol1.toString(), pol11.toString(), pol1.getSize()));
	REQUIRE(!memcmp(pol2.toString(), pol22->toString(), pol2.getSize()));
	REQUIRE(!memcmp(pol3.toString(), pol33->toString(), pol3.getSize()));
}

//Тесты к седьмой лабе

TEST_CASE("Testing QueueT") {
	QueueT<Polynomial> q;
	float n1[3] = { 1, 4 ,5 };
	float n2[4] = { 1, 2, 3, 4 };
	float n3[2] = { 5, 1 };
	Polynomial pol1(2, n1);
	Polynomial pol2(3, n2);
	Polynomial pol3(1, n3);
	REQUIRE(q.empty() == true);
	REQUIRE(q.size() == 0);
	q.push(pol1);
	REQUIRE(q.empty() == false);
	REQUIRE(q.size() == 1);
	q.push(pol2);
	REQUIRE(q.empty() == false);
	REQUIRE(q.size() == 2);
	q.push(pol3);
	REQUIRE(q.empty() == false);
	REQUIRE(q.size() == 3);
	Polynomial pol11(*q.pop());
	REQUIRE(q.empty() == false);
	REQUIRE(q.size() == 2);
	Polynomial* pol22;
	pol22 = q.pop();
	REQUIRE(q.empty() == false);
	REQUIRE(q.size() == 1);
	Polynomial* pol33;
	pol33 = q.pop();
	REQUIRE(q.empty() == true);
	REQUIRE(q.size() == 0);
	REQUIRE(pol11.getOrder() == 2);
	REQUIRE(pol11.getCoefficient(0) == 1);
	REQUIRE(pol11.getCoefficient(1) == 4);
	REQUIRE(pol11.getCoefficient(2) == 5);
	REQUIRE(pol22->getOrder() == 3);
	REQUIRE(pol22->getCoefficient(0) == 1);
	REQUIRE(pol22->getCoefficient(1) == 2);
	REQUIRE(pol22->getCoefficient(2) == 3);
	REQUIRE(pol22->getCoefficient(3) == 4);
	REQUIRE(pol33->getOrder() == 1);
	REQUIRE(pol33->getCoefficient(0) == 5);
	REQUIRE(pol33->getCoefficient(1) == 1);
	REQUIRE(!memcmp(pol1.toString(), pol11.toString(), pol1.getSize()));
	REQUIRE(!memcmp(pol2.toString(), pol22->toString(), pol2.getSize()));
	REQUIRE(!memcmp(pol3.toString(), pol33->toString(), pol3.getSize()));
	QueueT<int> q2;
	REQUIRE(q2.empty() == true);
	REQUIRE(q2.size() == 0);
	q2.push(10);
	REQUIRE(q2.empty() == false);
	REQUIRE(q2.size() == 1);
	q2.push(13);
	REQUIRE(q2.empty() == false);
	REQUIRE(q2.size() == 2);
	REQUIRE(!memcmp(q2.show(), "10\n13\n", 7));
}

