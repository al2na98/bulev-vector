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
    
    // Конструкторы
    boolvector(); // Конструктор по умолчанию
    boolvector(int N); // Конструктор с заданной длиной вектора
    boolvector(char* s); // Конструктор, инициализирующий вектор из строки
    boolvector(char* s, int N); // Конструктор, инициализирующий вектор из строки с заданной длиной
    boolvector(const boolvector& x);
    ~boolvector(); // Деструктор для освобождения ресурсов

    // Методы
    int Input(char* s, int i_bv, int i_s, int k); // Метод для ввода данных в вектор
    void Output(int i_bv, int k); // Метод для вывода данных вектора
    void Print(); // Метод для печати вектора
    void Scan(int N); // Метод для сканирования данных
    int Weight(); // Метод для подсчета количества единиц в векторе
    boolvector& operator = (boolvector& x); // Перегрузка оператора присваивания
    bool operator == (boolvector& x); // Перегрузка оператора сравнения на равенство
    bool operator != (boolvector& x); // Перегрузка оператора сравнения на неравенство
    bool operator < (boolvector& x); // Перегрузка оператора сравнения на меньше
    bool operator > (boolvector& x); // Перегрузка оператора сравнения на больше
    UC operator [] (int i); // Перегрузка оператора доступа по индексу
    boolvector operator & (boolvector& x); // Перегрузка оператора побитового AND
    boolvector& operator &= (boolvector& x); // Перегрузка оператора AND с присваиванием
    boolvector operator | (boolvector& x); // Перегрузка оператора побитового OR
    boolvector& operator |= (boolvector& x); // Перегрузка оператора OR с присваиванием
    boolvector operator ^ (boolvector& x); // Перегрузка оператора побитового XOR
    boolvector& operator ^= (boolvector& x); // Перегрузка оператора XOR с присваиванием
    boolvector operator << (int k); // Перегрузка оператора сдвига влево
    boolvector& operator <<= (int k); // Перегрузка оператора сдвига влево с присваиванием
    boolvector operator >> (int k); // Перегрузка оператора сдвига вправо
    boolvector& operator >>= (int k); // Перегрузка оператора сдвига вправо с присваиванием
    boolvector operator ~ (); // Перегрузка оператора побитового отрицания (инверсии)
    boolvector& setup1(int k); // Установка бита в 1 по индексу k
    boolvector& setup0(int k); // Установка бита в 0 по индексу k
    boolvector& setup1(int k, int p); // Установка нескольких битов в 1, начиная с индекса k
    boolvector& setup0(int k, int p); // Установка нескольких битов в 0, начиная с индекса k
    boolvector& inversion(int k); // Инверсия бита по индексу k
    boolvector& inversion(int k, int p); // Инверсия битов в диапазоне от k до k + p
    friend ostream& operator << (ostream& r, boolvector& x);
    friend istream& operator >> (istream& r, boolvector& x); 
};

