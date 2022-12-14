#pragma once
/* Заголовочный файл ModSp1.h
* Содержит определения новых типов и объявления 
функций для работы со списком */
// Определение типов
typedef int telem; // определение типа информационного поля
struct list {	   // определение типа элемента списка
	telem data;	   // информационное поле
	list* link;	   // поле адреса
};
// Объявления (прототипы) функций
void init_spis(list**, list**);
void add_spis(telem, list**, list**);
void obrabotka(list*);
void view_spis(list*);
void udal_spis(list**, list**);
