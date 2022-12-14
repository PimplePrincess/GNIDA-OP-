#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define FNAME_I "initial.txt\0" // имя исх. файла задано константной строкой
#define FNAME_R "result.txt\0"  // имя рез. файла задано константной строкой

const int LENGTH = 80;       // максимальная длина строки
const char TO_READ[] = "r";  // признак открытия файла на чтение
const char TO_WRITE[] = "w"; // признак открытия файла на запись

void make_file(char*);              // функция, отвечающая за создание файла
int proverka_file(char*, const char*); // функция, проверяющая наличие файла
void obrabotka_file(char*, char*); // функция, отвечающая за обработку содержимого
void out_file(char*);          // функция, отвечающая за вывод содержимого файла на печать
char* add_length(char*);           // функция, которая добавляет длину слова в конец слова

using namespace std;

/* создание файла */
void make_file(char* fname_i) {
	char st[LENGTH]; 
	ofstream out; // поток записи в файл
	char answer; // ответ пользователя для создания нового файла

	/* Окрываем файл в режиме чтения.
	Если файл с таким именем уже есть, то либо пользователь вводит
	новое имя, либо новые записи будут дописаны поверх старых. */
	while (proverka_file(fname_i, TO_READ)) {
		printf("\n Файл с заданным именем уже есть! Зададите новое имя Y/N? ");
		cin >> answer; // ввод ответа 
		if (answer == 'Y' || answer == 'y') {
			printf(" Введите новое имя:\n");
			cin >> fname_i; // ввод нового имени файла
		}
		else {
			cin.get();
			break;
		}
	}

	/* Проверяем возможность открытия файла для записи*/
	if (!proverka_file(fname_i, TO_WRITE)) {
		printf(" Ошибка открытия файла %s на запись.\n", fname_i);
		printf(" Нажмите <Enter>\n");
		cin.get();
		exit(0);
	}

	/* Открываем файл в режиме записи.
	Если файл с таким именем уже есть, то новые данные
	будут дописаны поверх старых. */
	out.open(fname_i);
	printf(" Запись данных в файл.\n");
	printf(" Признак окончания ввода - ввод пустой строки.\n");

	// пока не случится ввод пустой строки
	while (strlen(st)) {
		cout << " Введите строку и нажмите <Enter>\n";
		cout << " -> ";
		cin.getline(st, LENGTH); // читаем строку
		out << st << endl; // добавляем строку в файл
	}

	cout << endl;
	out.close(); // закрываем поток записи out
}

/* Функция проверки существования файла. */
int proverka_file(char* fname, const char* to) {
	if (to == "r") {
		ifstream file(fname); // открытие файла на чтение
		if (!file) return 0; // возврат при ошибке
		return 1; // возврат, если файл открыт
	}
	else if (to == "w") {
		ofstream file(fname); // открытие файла на запись
		if (!file) return 0; // возврат при ошибке
		return 1; // возврат, если файл открыт
	}
}

/* обработка содержимого файла */
void obrabotka_file(char* fname_i, char* fname_r) {
	ifstream in; // исходный файл (поток)
	ofstream out; // результирующий файл (поток)
	char st_in[LENGTH]; // исходная строка
	char st_out[LENGTH]; // результирующая строка
	char* p; // указатель на выделенное слово

	in.open(fname_i); // открываем файл на чтение
	out.open(fname_r); // открываем файл на запись
	in.getline(st_in, LENGTH); // читаем строку из файла in

	while (1) {
		if (in.eof()) break; 

		st_out[0] = '\0'; // очищение строки 
		char* context = NULL; // указатель на местоположение в массиве символов
		p = strtok_s(st_in, " \n", &context); // выделяем первое слово 
		// если очередное слово выделено
		while (p != NULL) {
			// обрабатываем слово
				strcat_s(st_out, p); // добавляем слово
                strcat_s(st_out, add_length(p)); // добавляем длину слова
				strcat_s(st_out, " ");           // добавлям пробел между словами
			
			p = strtok_s(NULL, " ", &context); // выделение последующих слов
		} 

		if (strlen(st_out))
			out << st_out << endl; // записываем строку в новый файл

		in.getline(st_in, LENGTH); // считываем новую строку из файла
	} 

	in.close();  // Закрываем файл in
	out.close(); // Закрываем файл out
}

/* вывод содержимого файла на экран */
void out_file(char* fname) {
	ifstream in_out(fname); // поток на чтение
	char st[LENGTH]; // считанная строка

	// Считывание и отображение строки в цикле
	while (!in_out.eof()) {
		in_out.getline(st, LENGTH);
		cout << st << endl; // выводим очередную строку на экран
	}

	in_out.close(); // Закрываем файл in_out
}

/* возвращение длины слова */
char* add_length(char* word) {
    int dlina = strlen(word); // длина
    char num_char[LENGTH + sizeof(char)];
    sprintf_s(num_char, "%d", dlina);
	return num_char; // возврат длины слова
}

int main() {
	char fname_i[] = FNAME_I; // имя исходного файла
	char fname_r[] = FNAME_R; // имя результирующего файла

	setlocale(LC_ALL, "Russian");

    cout << "Задание: Дан текст, составленный из строк. Под словом текста понимается" <<
        " последовательность цифр. Между соседними словами не менее одного пробела." <<
        " Перед первым и за последним словом каждой строки произвольное число пробелов." << endl;
    cout << "Преобразовать каждую строку, добавив в конец каждого слова символ(символы)," <<
        " соответствующие исходной длине этого слова." << endl << endl;

	printf(" Программа создает файл строк.\n");
	printf(" Затем файл построчно читается, при этом в каждой строке,\n");
	printf(" содержащей слова (слово - последовательность цифр),\n");
	printf(" Создаем исходный файл:\n");

	// создаем исходный файл
	make_file(fname_i);

	// выводим содержимое результата
	if (!proverka_file(fname_i, TO_READ)) {
		printf(" Ошибка открытия файла %s на чтение.\n", fname_i);
		printf(" Нажмите <Enter>\n");
		cin.get();
		return 0; 
	}
	printf(" Содержимое исходного файла:\n");
	out_file(fname_i); // вывод изначального файла

	// обрабатываем файл
	obrabotka_file(fname_i, fname_r);

	// выводим содержимое результата
	if (!proverka_file(fname_r, TO_READ)) {
		printf(" Ошибка открытия файла %s на чтение.\n", fname_r);
		printf(" Нажмите <Enter>\n");
		cin.get();
		return 0; 
	}
	printf(" Результат (в каждой строке в каждом слове с нечетной длиной\n");
	printf(" была произведена замена средней цифры на символ '*'):\n");
	out_file(fname_r); // вывод результирующего файла

	printf("\n Для завершения нажмите <Enter>");

	cin.get();
	return 0;
}
