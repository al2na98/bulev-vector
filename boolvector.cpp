#include "boolvector.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <iostream>
using namespace std;

// Конструктор по умолчанию
boolvector::boolvector() {
	n = 0;
	m = 0;
	bv = nullptr; // Инициализация указателя
}
// // Конструктор из строки
boolvector::boolvector(char* s) {
	n = strlen(s); // Получаем длину строки
	// Вычисляем количество байтов, необходимых для хранения булевого вектора
	if (n % 8 == 0) {
		m = n / 8;
	}
	else {
		m = n / 8 + 1;
	}
	int k = n % 8;
	int i_bv = 0; // Индекс для текущего байта
	int i_s = 0;  // Индекс для текущего символа в строке
	bv = new UC[m](); // Выделяем память для массива булевых значений
	// Если есть значащие биты в последнем байте
	if (k) {
		for (int i = 0; i < m - 1; i++) {
			i_s = Input(s, i_bv, i_s, 8); // Заполняем полный байт
			i_bv = i_s; // Обновляем индекс байта
		}
		Input(s, i_bv, i_s, k); // Заполняем последний неполный байт
	}
	else {
		// Если все байты полные
		for (int i = 0; i < m; i++) {
			Input(s, i_bv, i_s, 8); // Заполняем каждый байт
		}
	}
}
// Конструктор копирования
boolvector::boolvector(const boolvector& x) {
	n = x.n;
	m = x.m;
	bv = new UC[m]; // Выделяем память для нового вектора
	memcpy(bv, x.bv, m); // Копируем данные из другого вектора
}
// Деструктор
boolvector::~boolvector() {
	delete[] bv;
}
// Метод для ввода булевого вектора из строки
int boolvector::Input(char* s, int i_bv, int i_s, int k) {
	UC mask = 1;
	mask <<= (k - 1); // Устанавливаем маску для текущего бита
	bv[i_bv] = 0; 
	for (int i = 0; i < k; i++, i_s++, mask >>= 1) {
		if (s[i_s] == '1') {
			bv[i_bv] |= mask; // Устанавливаем бит, если символ '1'
		}
	}
	return i_s + 1; // Возвращаем индекс следующего символа
}

// Метод для вывода булевого вектора
void boolvector::Output(int i_bv, int k) {
	UC mask = 1 << 7;
	mask <<= (k - 1); // Устанавливаем маску для текущего бита
	for (int i = 0; i < k; mask >>= 1, i++) {
		cout << ((bv[i_bv] & mask) ? '1' : '0'); // Выводим '1' или '0' в зависимости от бита
	}
}

// Метод для печати всего булевого вектора
void boolvector::Print() {
	int k = n % 8;
	for (int i = 0; i < m; i++) {
		Output(i, (i == m - 1) ? k : 8); // Выводим последний байт с учетом значащих битов
	}
	cout << endl; 
}
// Метод для ввода булевого вектора с клавиатуры
void boolvector::Scan(int N) {
	char* s = new char[N + 1]; // Выделяем память для строки
	cout << "Введите булев вектор длины " << n << ":";
	cin >> s; 
	boolvector temp(s); // Создаем временный булев вектор
	*this = temp; // Присваиваем временный вектор текущему
	delete[] s;
}
// Конструктор с заданной длиной
boolvector::boolvector(int N) {
	n = N;
	m = (n + 7) / 8; // Вычисляем количество байтов, округляя вверх
	bv = new UC[m](); // Выделяем память и инициализируем нулями
}


	// Метод для подсчета веса в булевом векторе
int boolvector::Weight() {
	int w = 0; // Переменная для хранения веса
	UC mask = 1; // Маска для проверки битов
	for (int i_bv = 0; i_bv < m; i_bv++) { // Проходим по всем байтам
		for (mask = 1; mask; mask <<= 1) {
			if (bv[i_bv] & mask) {
				w++;
			}
		}
	}
	return w;
}

	// Перегрузка оператора [] для доступа к битам в булевом векторе
UC boolvector::operator[](int i) {
	if (i < 0 || i >= n) {
		throw std::out_of_range("Индекс выходит за пределы"); // Проверка на выход за пределы
	}
	return (bv[i / 8] & (1 << (7 - (i % 8)))) ? '1' : '0';
}

// Перегрузка оператора & для побитового AND
boolvector boolvector::operator & (boolvector & x) {
	int t; // Длина результирующего вектора
	int min; 
	if (n > x.n) {
		t = x.n; // Если текущий вектор длиннее, берем длину второго
		min = x.m; 
	}
	else {
		t = n; // Иначе берем длину текущего вектора
		min = m; 
	}
		boolvector temp(t); // Создаем временный вектор
		int i, i_s; 
		temp.m = min; 
		temp.n = t; 

		// Выполняем побитовое AND для каждого байта
		for (i = m - 1, i_s = x.m - 1; min >= 0; i--, i_s--, min--) {
			temp.bv[min] = bv[i] & x.bv[i_s];
		}
		return temp; 
	}

// Перегрузка оператора &= для побитового AND с присваиванием
boolvector& boolvector::operator &= (boolvector & x) {
	boolvector rez = (*this) & x; // Получаем результат операции
	(*this) = rez; // Присваиваем результат текущему вектору
	return *this; 
}
// Перегрузка оператора << для сдвига влево
boolvector boolvector::operator << (int k) {
	boolvector temp(*this); // Создаем временный вектор
	temp <<= k; // Сдвигаем его влево
	return temp; // Возвращаем результат
}
// Метод для инверсии бита по индексу K
boolvector& boolvector::inversion(int K) {
	// Проверяем корректность индекса
	if ((K < 0) || (K > n - 1)) {
		cout << "Некорректный ввод" << endl;
		return *this; 
	}
		int byteIndex = m - 1 - K / 8;
		int bitIndex = K % 8; 
		bv[byteIndex] ^= (1 << bitIndex); // Инвертируем бит
		return *this; 
	}
// Перегрузка оператора >> для ввода булевого вектора
istream& operator >> (istream& r, boolvector& x) {
	cout << "Введите длину булевого вектора: "; 
	int N; 
	cin >> N; 
	while (getchar() != '\n'); // Очищаем буфер ввода
	x.Scan(N); 
	return r; 
}

// Перегрузка оператора = для присваивания одного булевого вектора другому
boolvector& boolvector::operator = (boolvector& x) {
	if (this != &x) { // Проверяем на самоприсваивание
		delete[] bv;
	}
	// Проверяем, совпадают ли размеры векторов
	if ((x.m == m) && (x.n == n)) {
		for (int i = 0; i < m; i++) {
			bv[i] = x.bv[i]; // Копируем значения из вектора x
		}
		return *this; // Возвращаем текущий вектор
	}
	cout << "Векторы разной длины" << endl; 
}

// Конструктор булевого вектора из строки и длины
boolvector::boolvector(char* s, int N) {
	n = N; 
	// Вычисляем количество байтов, необходимых для хранения булевого вектора
	if (n % 8 == 0) {
		m = n / 8;
	}
	else {
		m = n / 8 + 1; 
	}

	int k = n % 8; 
	bv = new UC[m * 8]; 
	UC mask = 1; // Маска для проверки битов
	int i_s = 0;
	int i_bv = 0;

	// Если есть значащие биты в последнем байте
	if (k) {
		for (int i = 0; i < m - 1; i++) {
			i_s = Input(s, i_bv, i_s, 8); 
			i_bv = i_s; // Обновляем индекс байта
		}
		i_s = Input(s, i_bv, i_s, k); // Заполняем последний неполный байт
	}
	else {
		// Если все байты полные
		for (; i_s < m; i_bv++) {
			i_s = Input(s, i_bv, i_s, 8); 
			i_bv = i_s; 
		}
	}
}
// Перегрузка оператора == для сравнения двух булевых векторов
bool boolvector::operator ==(boolvector& x) {
	if (n != x.n) return false; // Сравниваем длины
	for (int i = 0; i < m; i++) {
		if (bv[i] != x.bv[i]) return false; // Сравниваем байты
	}
	return true; // Векторы равны
}

// Перегрузка оператора != для сравнения двух булевых векторов на неравенство
bool boolvector::operator !=(boolvector& x) {
	return !(*this == x);
}
// Перегрузка оператора < для сравнения двух булевых векторов
bool boolvector::operator <(boolvector& x) {
	if (n != x.n) return n < x.n; // Сравниваем длины
	for (int i = 0; i < m; i++) {
		if (bv[i] < x.bv[i]) return true;
		if (bv[i] > x.bv[i]) return false;
	}
	return false; // Векторы равны
}

// Перегрузка оператора > для сравнения двух булевых векторов
bool boolvector::operator >(boolvector& x) {
	return !(*this < x) && (*this != x);
}

// Перегрузка оператора | для побитового OR между двумя булевыми векторами
boolvector boolvector::operator | (boolvector& x) {
	int N = n; 
	int j_rez = m - 1; 
	// Если длина второго вектора меньше, используем его длину
	if (N > x.n) {
		N = x.n;
		j_rez = x.m - 1; 
	}
	boolvector rez(N); // Создаем результирующий вектор
	int j, j_x; 
	// Выполняем побитовое OR для каждого байта
	for (j = m - 1, j_x = x.m - 1; j_rez >= 0; j_rez--, j--, j_x--) {
		rez.bv[j_rez] = bv[j] | x.bv[j_x]; 
	}
	return rez; 
}
// Перегрузка оператора |= для побитового OR с присваиванием
boolvector& boolvector::operator |= (boolvector& x) {
	boolvector rez = (*this) | x; // Получаем результат операции
	(*this) = rez; // Присваиваем результат текущему вектору
	return *this; 
}
// Перегрузка оператора ^ для побитового XOR между двумя булевыми векторами
boolvector boolvector::operator ^ (boolvector& x) {
	int N = n, j_rez = m - 1; // Определяем длину результирующего вектора и индекс
	// Если длина второго вектора меньше, используем его длину
	if (N > x.n) {
		N = x.n; 
		j_rez = x.m - 1;
	}
	boolvector rez(N); 
	int j, j_x; // Индексы для обхода векторов
	// Выполняем побитовое XOR для каждого байта
	for (j = m - 1, j_x = x.m - 1; j_rez >= 0; j_rez--, j--, j_x--) {
		rez.bv[j_rez] = bv[j] ^ x.bv[j_x]; 
	}
	return rez; 
}
// Перегрузка оператора ^= для побитового XOR с присваиванием
boolvector& boolvector::operator ^= (boolvector& x) {
	boolvector rez = (*this) ^ x; 
	(*this) = rez; // Присваиваем результат текущему вектору
	return *this; 
}

// Перегрузка оператора <<= для сдвига влево
boolvector& boolvector::operator <<= (int k) {
	boolvector tmp(*this); // Создаем временный объект
	tmp << k; // Вызываем сдвиг влево
	return *this; 
}
// Перегрузка оператора >>= для сдвига вправо
boolvector& boolvector::operator >>= (int k) {
	boolvector tmp(*this); // Создаем временный объект
	tmp >> k; // Вызываем сдвиг вправо
	return *this;
}
// Перегрузка оператора >> для сдвига вправо с возвращением нового вектора
boolvector boolvector::operator >> (int k) {
	boolvector rez(n); 
	int tmp = k; // Временная переменная для сдвига
	// Если сдвиг меньше длины вектора
	if (k < n) {
		for (int i = 0; tmp < n; i++, tmp++) {
			if (this->operator[](tmp) == '1') { // Если бит равен 1
				rez.setup1(i); // Устанавливаем 1 в результирующем векторе
			}
			else {
				rez.setup0(i); // Устанавливаем 0 в результирующем векторе
			}
		}
	}
	return rez; 
}
// Перегрузка оператора ~ для побитового отрицания (инверсии)
boolvector boolvector::operator ~ () {
	boolvector rez(n); // Создаем временный массив для инверсии
	for (int i = 0; i < n; i++) {
		// Инвертируем каждый бит
		if (this->operator[](i) == '1') {
			rez.setup0(i); // Если 1, устанавливаем 0
		}
		else {
			rez.setup1(i); // Если 0, устанавливаем 1
		}
	}
	return rez;
}
// Установка бита в 1 по индексу k
boolvector& boolvector::setup1(int k) {
	if (k < 0 || k >= n) {
		throw std::out_of_range("Индекс выходит за пределы");
	}
	int byteIndex = m - 1 - k / 8; // Находим индекс байта
	int bitIndex = k % 8; // Находим индекс бита
	bv[byteIndex] |= (1 << bitIndex); // Устанавливаем бит в 1
	return *this; 
}
// Установка бита в 0 по индексу k
boolvector& boolvector::setup0(int k) {
	if (k < 0 || k >= n) {
		throw std::out_of_range("Индекс выходит за пределы"); // Проверка на выход за пределы
	}
	int byteIndex = m - 1 - k / 8; // Находим индекс байта
	int bitIndex = k % 8; // Находим индекс бита
	bv[byteIndex] &= ~(1 << bitIndex); // Устанавливаем бит в 0
	return *this; 
}
// Установка нескольких битов в 1, начиная с индекса k
boolvector& boolvector::setup1(int k, int p) {
	boolvector rez(n); // Создаем результирующий вектор
	for (int i = k; i < k + p; i++) {
		rez.setup1(i); // Устанавливаем 1 на каждом индексе
	}
	return rez; 
}
// Установка нескольких битов в 0, начиная с индекса k
boolvector& boolvector::setup0(int k, int p) {
	boolvector rez(n); // Создаем результирующий вектор
	for (int i = k; i < k + p; i++) {
		rez.setup0(i); // Устанавливаем 0 на каждом индексе
	}
	return rez; 
}
// Перегрузка оператора << для вывода булевого вектора
ostream& operator << (ostream& r, boolvector& x) {
	// Проходим по каждому байту вектора
	for (int is = 0; is < x.m; is++) {
		for (UC mask = 1 << 7; mask; mask >>= 1) { 
			r << ((x.bv[is] & mask) ? '1' : '0'); 
		}
	}
	return r; 
}
// Инверсия битов в диапазоне от k до k + p
boolvector& boolvector::inversion(int k, int p) {
	boolvector rez(n); // Создаем результирующий вектор
	for (int i = k; i < k + p; i++) {
		rez.inversion(i); // Инвертируем каждый бит в диапазоне
	}
	return rez;
}
