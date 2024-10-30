#pragma once 
#include <stdio.h> 
#include <stdlib.h> 
#include <conio.h> 
#include <locale.h> 
#include <string.h> 
#include <iostream> 
using namespace std; 
typedef unsigned char UC;

class boolvector
{
    UC* bv; 
    int n; 
    int m; 
public:
    
    // ������������
    boolvector(); // ����������� �� ���������
    boolvector(int N); // ����������� � �������� ������ �������
    boolvector(char* s); // �����������, ���������������� ������ �� ������
    boolvector(char* s, int N); // �����������, ���������������� ������ �� ������ � �������� ������
    boolvector(const boolvector& x);
    ~boolvector(); // ���������� ��� ������������ ��������

    // ������
    int Input(char* s, int i_bv, int i_s, int k); // ����� ��� ����� ������ � ������
    void Output(int i_bv, int k); // ����� ��� ������ ������ �������
    void Print(); // ����� ��� ������ �������
    void Scan(int N); // ����� ��� ������������ ������
    int Weight(); // ����� ��� �������� ���������� ������ � �������
    boolvector& operator = (boolvector& x); // ���������� ��������� ������������
    bool operator == (boolvector& x); // ���������� ��������� ��������� �� ���������
    bool operator != (boolvector& x); // ���������� ��������� ��������� �� �����������
    bool operator < (boolvector& x); // ���������� ��������� ��������� �� ������
    bool operator > (boolvector& x); // ���������� ��������� ��������� �� ������
    UC operator [] (int i); // ���������� ��������� ������� �� �������
    boolvector operator & (boolvector& x); // ���������� ��������� ���������� AND
    boolvector& operator &= (boolvector& x); // ���������� ��������� AND � �������������
    boolvector operator | (boolvector& x); // ���������� ��������� ���������� OR
    boolvector& operator |= (boolvector& x); // ���������� ��������� OR � �������������
    boolvector operator ^ (boolvector& x); // ���������� ��������� ���������� XOR
    boolvector& operator ^= (boolvector& x); // ���������� ��������� XOR � �������������
    boolvector operator << (int k); // ���������� ��������� ������ �����
    boolvector& operator <<= (int k); // ���������� ��������� ������ ����� � �������������
    boolvector operator >> (int k); // ���������� ��������� ������ ������
    boolvector& operator >>= (int k); // ���������� ��������� ������ ������ � �������������
    boolvector operator ~ (); // ���������� ��������� ���������� ��������� (��������)
    boolvector& setup1(int k); // ��������� ���� � 1 �� ������� k
    boolvector& setup0(int k); // ��������� ���� � 0 �� ������� k
    boolvector& setup1(int k, int p); // ��������� ���������� ����� � 1, ������� � ������� k
    boolvector& setup0(int k, int p); // ��������� ���������� ����� � 0, ������� � ������� k
    boolvector& inversion(int k); // �������� ���� �� ������� k
    boolvector& inversion(int k, int p); // �������� ����� � ��������� �� k �� k + p
    friend ostream& operator << (ostream& r, boolvector& x);
    friend istream& operator >> (istream& r, boolvector& x); 
};

