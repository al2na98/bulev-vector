#include "boolvector.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <iostream>
using namespace std;

// ����������� �� ���������
boolvector::boolvector() {
	n = 0;
	m = 0;
	bv = nullptr; // ������������� ���������
}
// // ����������� �� ������
boolvector::boolvector(char* s) {
	n = strlen(s); // �������� ����� ������
	// ��������� ���������� ������, ����������� ��� �������� �������� �������
	if (n % 8 == 0) {
		m = n / 8;
	}
	else {
		m = n / 8 + 1;
	}
	int k = n % 8;
	int i_bv = 0; // ������ ��� �������� �����
	int i_s = 0;  // ������ ��� �������� ������� � ������
	bv = new UC[m](); // �������� ������ ��� ������� ������� ��������
	// ���� ���� �������� ���� � ��������� �����
	if (k) {
		for (int i = 0; i < m - 1; i++) {
			i_s = Input(s, i_bv, i_s, 8); // ��������� ������ ����
			i_bv = i_s; // ��������� ������ �����
		}
		Input(s, i_bv, i_s, k); // ��������� ��������� �������� ����
	}
	else {
		// ���� ��� ����� ������
		for (int i = 0; i < m; i++) {
			Input(s, i_bv, i_s, 8); // ��������� ������ ����
		}
	}
}
// ����������� �����������
boolvector::boolvector(const boolvector& x) {
	n = x.n;
	m = x.m;
	bv = new UC[m]; // �������� ������ ��� ������ �������
	memcpy(bv, x.bv, m); // �������� ������ �� ������� �������
}
// ����������
boolvector::~boolvector() {
	delete[] bv;
}
// ����� ��� ����� �������� ������� �� ������
int boolvector::Input(char* s, int i_bv, int i_s, int k) {
	UC mask = 1;
	mask <<= (k - 1); // ������������� ����� ��� �������� ����
	bv[i_bv] = 0; 
	for (int i = 0; i < k; i++, i_s++, mask >>= 1) {
		if (s[i_s] == '1') {
			bv[i_bv] |= mask; // ������������� ���, ���� ������ '1'
		}
	}
	return i_s + 1; // ���������� ������ ���������� �������
}

// ����� ��� ������ �������� �������
void boolvector::Output(int i_bv, int k) {
	UC mask = 1 << 7;
	mask <<= (k - 1); // ������������� ����� ��� �������� ����
	for (int i = 0; i < k; mask >>= 1, i++) {
		cout << ((bv[i_bv] & mask) ? '1' : '0'); // ������� '1' ��� '0' � ����������� �� ����
	}
}

// ����� ��� ������ ����� �������� �������
void boolvector::Print() {
	int k = n % 8;
	for (int i = 0; i < m; i++) {
		Output(i, (i == m - 1) ? k : 8); // ������� ��������� ���� � ������ �������� �����
	}
	cout << endl; 
}
// ����� ��� ����� �������� ������� � ����������
void boolvector::Scan(int N) {
	char* s = new char[N + 1]; // �������� ������ ��� ������
	cout << "������� ����� ������ ����� " << n << ":";
	cin >> s; 
	boolvector temp(s); // ������� ��������� ����� ������
	*this = temp; // ����������� ��������� ������ ��������
	delete[] s;
}
// ����������� � �������� ������
boolvector::boolvector(int N) {
	n = N;
	m = (n + 7) / 8; // ��������� ���������� ������, �������� �����
	bv = new UC[m](); // �������� ������ � �������������� ������
}


	// ����� ��� �������� ���� � ������� �������
int boolvector::Weight() {
	int w = 0; // ���������� ��� �������� ����
	UC mask = 1; // ����� ��� �������� �����
	for (int i_bv = 0; i_bv < m; i_bv++) { // �������� �� ���� ������
		for (mask = 1; mask; mask <<= 1) {
			if (bv[i_bv] & mask) {
				w++;
			}
		}
	}
	return w;
}

	// ���������� ��������� [] ��� ������� � ����� � ������� �������
UC boolvector::operator[](int i) {
	if (i < 0 || i >= n) {
		throw std::out_of_range("������ ������� �� �������"); // �������� �� ����� �� �������
	}
	return (bv[i / 8] & (1 << (7 - (i % 8)))) ? '1' : '0';
}

// ���������� ��������� & ��� ���������� AND
boolvector boolvector::operator & (boolvector & x) {
	int t; // ����� ��������������� �������
	int min; 
	if (n > x.n) {
		t = x.n; // ���� ������� ������ �������, ����� ����� �������
		min = x.m; 
	}
	else {
		t = n; // ����� ����� ����� �������� �������
		min = m; 
	}
		boolvector temp(t); // ������� ��������� ������
		int i, i_s; 
		temp.m = min; 
		temp.n = t; 

		// ��������� ��������� AND ��� ������� �����
		for (i = m - 1, i_s = x.m - 1; min >= 0; i--, i_s--, min--) {
			temp.bv[min] = bv[i] & x.bv[i_s];
		}
		return temp; 
	}

// ���������� ��������� &= ��� ���������� AND � �������������
boolvector& boolvector::operator &= (boolvector & x) {
	boolvector rez = (*this) & x; // �������� ��������� ��������
	(*this) = rez; // ����������� ��������� �������� �������
	return *this; 
}
// ���������� ��������� << ��� ������ �����
boolvector boolvector::operator << (int k) {
	boolvector temp(*this); // ������� ��������� ������
	temp <<= k; // �������� ��� �����
	return temp; // ���������� ���������
}
// ����� ��� �������� ���� �� ������� K
boolvector& boolvector::inversion(int K) {
	// ��������� ������������ �������
	if ((K < 0) || (K > n - 1)) {
		cout << "������������ ����" << endl;
		return *this; 
	}
		int byteIndex = m - 1 - K / 8;
		int bitIndex = K % 8; 
		bv[byteIndex] ^= (1 << bitIndex); // ����������� ���
		return *this; 
	}
// ���������� ��������� >> ��� ����� �������� �������
istream& operator >> (istream& r, boolvector& x) {
	cout << "������� ����� �������� �������: "; 
	int N; 
	cin >> N; 
	while (getchar() != '\n'); // ������� ����� �����
	x.Scan(N); 
	return r; 
}

// ���������� ��������� = ��� ������������ ������ �������� ������� �������
boolvector& boolvector::operator = (boolvector& x) {
	if (this != &x) { // ��������� �� ����������������
		delete[] bv;
	}
	// ���������, ��������� �� ������� ��������
	if ((x.m == m) && (x.n == n)) {
		for (int i = 0; i < m; i++) {
			bv[i] = x.bv[i]; // �������� �������� �� ������� x
		}
		return *this; // ���������� ������� ������
	}
	cout << "������� ������ �����" << endl; 
}

// ����������� �������� ������� �� ������ � �����
boolvector::boolvector(char* s, int N) {
	n = N; 
	// ��������� ���������� ������, ����������� ��� �������� �������� �������
	if (n % 8 == 0) {
		m = n / 8;
	}
	else {
		m = n / 8 + 1; 
	}

	int k = n % 8; 
	bv = new UC[m * 8]; 
	UC mask = 1; // ����� ��� �������� �����
	int i_s = 0;
	int i_bv = 0;

	// ���� ���� �������� ���� � ��������� �����
	if (k) {
		for (int i = 0; i < m - 1; i++) {
			i_s = Input(s, i_bv, i_s, 8); 
			i_bv = i_s; // ��������� ������ �����
		}
		i_s = Input(s, i_bv, i_s, k); // ��������� ��������� �������� ����
	}
	else {
		// ���� ��� ����� ������
		for (; i_s < m; i_bv++) {
			i_s = Input(s, i_bv, i_s, 8); 
			i_bv = i_s; 
		}
	}
}
// ���������� ��������� == ��� ��������� ���� ������� ��������
bool boolvector::operator ==(boolvector& x) {
	if (n != x.n) return false; // ���������� �����
	for (int i = 0; i < m; i++) {
		if (bv[i] != x.bv[i]) return false; // ���������� �����
	}
	return true; // ������� �����
}

// ���������� ��������� != ��� ��������� ���� ������� �������� �� �����������
bool boolvector::operator !=(boolvector& x) {
	return !(*this == x);
}
// ���������� ��������� < ��� ��������� ���� ������� ��������
bool boolvector::operator <(boolvector& x) {
	if (n != x.n) return n < x.n; // ���������� �����
	for (int i = 0; i < m; i++) {
		if (bv[i] < x.bv[i]) return true;
		if (bv[i] > x.bv[i]) return false;
	}
	return false; // ������� �����
}

// ���������� ��������� > ��� ��������� ���� ������� ��������
bool boolvector::operator >(boolvector& x) {
	return !(*this < x) && (*this != x);
}

// ���������� ��������� | ��� ���������� OR ����� ����� �������� ���������
boolvector boolvector::operator | (boolvector& x) {
	int N = n; 
	int j_rez = m - 1; 
	// ���� ����� ������� ������� ������, ���������� ��� �����
	if (N > x.n) {
		N = x.n;
		j_rez = x.m - 1; 
	}
	boolvector rez(N); // ������� �������������� ������
	int j, j_x; 
	// ��������� ��������� OR ��� ������� �����
	for (j = m - 1, j_x = x.m - 1; j_rez >= 0; j_rez--, j--, j_x--) {
		rez.bv[j_rez] = bv[j] | x.bv[j_x]; 
	}
	return rez; 
}
// ���������� ��������� |= ��� ���������� OR � �������������
boolvector& boolvector::operator |= (boolvector& x) {
	boolvector rez = (*this) | x; // �������� ��������� ��������
	(*this) = rez; // ����������� ��������� �������� �������
	return *this; 
}
// ���������� ��������� ^ ��� ���������� XOR ����� ����� �������� ���������
boolvector boolvector::operator ^ (boolvector& x) {
	int N = n, j_rez = m - 1; // ���������� ����� ��������������� ������� � ������
	// ���� ����� ������� ������� ������, ���������� ��� �����
	if (N > x.n) {
		N = x.n; 
		j_rez = x.m - 1;
	}
	boolvector rez(N); 
	int j, j_x; // ������� ��� ������ ��������
	// ��������� ��������� XOR ��� ������� �����
	for (j = m - 1, j_x = x.m - 1; j_rez >= 0; j_rez--, j--, j_x--) {
		rez.bv[j_rez] = bv[j] ^ x.bv[j_x]; 
	}
	return rez; 
}
// ���������� ��������� ^= ��� ���������� XOR � �������������
boolvector& boolvector::operator ^= (boolvector& x) {
	boolvector rez = (*this) ^ x; 
	(*this) = rez; // ����������� ��������� �������� �������
	return *this; 
}

// ���������� ��������� <<= ��� ������ �����
boolvector& boolvector::operator <<= (int k) {
	boolvector tmp(*this); // ������� ��������� ������
	tmp << k; // �������� ����� �����
	return *this; 
}
// ���������� ��������� >>= ��� ������ ������
boolvector& boolvector::operator >>= (int k) {
	boolvector tmp(*this); // ������� ��������� ������
	tmp >> k; // �������� ����� ������
	return *this;
}
// ���������� ��������� >> ��� ������ ������ � ������������ ������ �������
boolvector boolvector::operator >> (int k) {
	boolvector rez(n); 
	int tmp = k; // ��������� ���������� ��� ������
	// ���� ����� ������ ����� �������
	if (k < n) {
		for (int i = 0; tmp < n; i++, tmp++) {
			if (this->operator[](tmp) == '1') { // ���� ��� ����� 1
				rez.setup1(i); // ������������� 1 � �������������� �������
			}
			else {
				rez.setup0(i); // ������������� 0 � �������������� �������
			}
		}
	}
	return rez; 
}
// ���������� ��������� ~ ��� ���������� ��������� (��������)
boolvector boolvector::operator ~ () {
	boolvector rez(n); // ������� ��������� ������ ��� ��������
	for (int i = 0; i < n; i++) {
		// ����������� ������ ���
		if (this->operator[](i) == '1') {
			rez.setup0(i); // ���� 1, ������������� 0
		}
		else {
			rez.setup1(i); // ���� 0, ������������� 1
		}
	}
	return rez;
}
// ��������� ���� � 1 �� ������� k
boolvector& boolvector::setup1(int k) {
	if (k < 0 || k >= n) {
		throw std::out_of_range("������ ������� �� �������");
	}
	int byteIndex = m - 1 - k / 8; // ������� ������ �����
	int bitIndex = k % 8; // ������� ������ ����
	bv[byteIndex] |= (1 << bitIndex); // ������������� ��� � 1
	return *this; 
}
// ��������� ���� � 0 �� ������� k
boolvector& boolvector::setup0(int k) {
	if (k < 0 || k >= n) {
		throw std::out_of_range("������ ������� �� �������"); // �������� �� ����� �� �������
	}
	int byteIndex = m - 1 - k / 8; // ������� ������ �����
	int bitIndex = k % 8; // ������� ������ ����
	bv[byteIndex] &= ~(1 << bitIndex); // ������������� ��� � 0
	return *this; 
}
// ��������� ���������� ����� � 1, ������� � ������� k
boolvector& boolvector::setup1(int k, int p) {
	boolvector rez(n); // ������� �������������� ������
	for (int i = k; i < k + p; i++) {
		rez.setup1(i); // ������������� 1 �� ������ �������
	}
	return rez; 
}
// ��������� ���������� ����� � 0, ������� � ������� k
boolvector& boolvector::setup0(int k, int p) {
	boolvector rez(n); // ������� �������������� ������
	for (int i = k; i < k + p; i++) {
		rez.setup0(i); // ������������� 0 �� ������ �������
	}
	return rez; 
}
// ���������� ��������� << ��� ������ �������� �������
ostream& operator << (ostream& r, boolvector& x) {
	// �������� �� ������� ����� �������
	for (int is = 0; is < x.m; is++) {
		for (UC mask = 1 << 7; mask; mask >>= 1) { 
			r << ((x.bv[is] & mask) ? '1' : '0'); 
		}
	}
	return r; 
}
// �������� ����� � ��������� �� k �� k + p
boolvector& boolvector::inversion(int k, int p) {
	boolvector rez(n); // ������� �������������� ������
	for (int i = k; i < k + p; i++) {
		rez.inversion(i); // ����������� ������ ��� � ���������
	}
	return rez;
}
