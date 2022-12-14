/* Исходный файл ModSp1.cpp
Реализация набора функций для работы со списком*/
#include <iostream>
#include "ModSp1.h"
using namespace std;

// Функция, отвечающая за добавление нового элемента в конец списка
void add_spis(int ch, list** beg, list** end) {
	list* nov = new list; // выделяем память под элемент списка
	nov->data = ch; // заполняем информационную часть
	nov->link = 0; // в ссылочную - NULL
	if (*beg) // если список не пуст, 
		(*end)->link = nov; // добавляем в конец списка
	else *beg = nov; // если список был пуст
	*end = nov; // новый элемент - последний
	return;
}

/* нахождение максимальной суммы значений двух любых элементов списка */
void obrabotka(list* beg) {
	list* cur = beg; // начало списка
	list* m1 = new list; // максимальный элемент
	telem max = beg->data; // значение максимального элемента

	// ищем максимум и минимум
	while (cur) {
		if (cur->data > max) {
			m1 = cur; // максимальный элемент
			max = cur->data; // значение максимального элемента
		}
		cur = cur->link; // след. элемент
	}

	cur = beg; // начало списка

	// ищем второй максимум
	// т.е. максимальное значение перед масимумом
	// и записываем сумму второго и первого максимума
	// в инф. поле головного элемента списка
	while (cur) {
		// если элемент не равен максимальному,
		// но имеет значение равное или меньше максимального
		if (cur != m1 && cur->data <= max)
			beg->data = cur->data + max; // складываем и записываем
		cur = cur->link; // след. элемент
	}
}

// Функция, отвечающая за просмотр списка
void view_spis(list* beg) {
	while (beg) {
		cout << beg->data << ' ';
		beg = beg->link;
	}
	cout << endl;
	return;
}

// Функция, отвечающая за инициализацию списка
void init_spis(list** beg, list** end) {
	*beg = *end = 0;
	return;
}

// Функция, отвечающая за удаление списка
void udal_spis(list** beg, list** end) {
	list* tec;
	while (*beg) {
		tec = *beg;
		*beg = (*beg)->link;
		delete tec;
	}
	*end = 0;
	// список пуст
	return;
}