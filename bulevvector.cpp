#include "boolvector.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "RUS");
    char c = 111011101110; // Пример булевого вектора в виде символа
    char* s = &c;

    boolvector b1, b2(10), b3(s), b4(s, 10), b5(s, 16), b6 = b5;
    // Вывод начальных состояний векторов
    cout << "Состояние векторов:" << endl;
    b1.Print(); 
    b2.Print(); 
    cout << "111011101110" << endl;
    b3.Print();
    b4.Print();
    b5.Print();
    b6.Print();

    // Вывод веса векторов
    cout << "Вес b2: " << b2.Weight() << endl;
    cout << "Вес b4: " << b4.Weight() << endl; // Подсчет единиц в b4

    // Сравнение векторов
    cout << "Сравнение b2 и b4:" << endl;
    cout << "b2 == b4: " << (b2 == b4) << endl;
    cout << "b2 != b4: " << (b2 != b4) << endl;
    cout << "b2 < b4: " << (b2 < b4) << endl;
    cout << "b2 > b4: " << (b2 > b4) << endl;

    // Инверсия векторов
    boolvector b7 = ~b4;
    cout << "Инверсия b4 (b7): ";
    b7.Print(); // Печать инверсии b4
    b2.setup1(3); // Установка бита в 1 по индексу 3
    cout << "После установки 1 по индексу 3 в b2: ";
    b2.Print();
    b5.setup0(1); // Установка бита в 0 по индексу 1
    cout << "После установки 0 по индексу 1 в b5: ";
    b5.Print();

    return 0;
}
