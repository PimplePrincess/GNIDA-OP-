/* �������� ���� ModSp1.cpp
���������� ������ ������� ��� ������ �� �������*/
#include <iostream>
#include "ModSp1.h"
using namespace std;

// �������, ���������� �� ���������� ������ �������� � ����� ������
void add_spis(int ch, list** beg, list** end) {
	list* nov = new list; // �������� ������ ��� ������� ������
	nov->data = ch; // ��������� �������������� �����
	nov->link = 0; // � ��������� - NULL
	if (*beg) // ���� ������ �� ����, 
		(*end)->link = nov; // ��������� � ����� ������
	else *beg = nov; // ���� ������ ��� ����
	*end = nov; // ����� ������� - ���������
	return;
}

/* ���������� ������������ ����� �������� ���� ����� ��������� ������ */
void obrabotka(list* beg) {
	list* cur = beg; // ������ ������
	list* m1 = new list; // ������������ �������
	telem max = beg->data; // �������� ������������� ��������

	// ���� �������� � �������
	while (cur) {
		if (cur->data > max) {
			m1 = cur; // ������������ �������
			max = cur->data; // �������� ������������� ��������
		}
		cur = cur->link; // ����. �������
	}

	cur = beg; // ������ ������

	// ���� ������ ��������
	// �.�. ������������ �������� ����� ���������
	// � ���������� ����� ������� � ������� ���������
	// � ���. ���� ��������� �������� ������
	while (cur) {
		// ���� ������� �� ����� �������������,
		// �� ����� �������� ������ ��� ������ �������������
		if (cur != m1 && cur->data <= max)
			beg->data = cur->data + max; // ���������� � ����������
		cur = cur->link; // ����. �������
	}
}

// �������, ���������� �� �������� ������
void view_spis(list* beg) {
	while (beg) {
		cout << beg->data << ' ';
		beg = beg->link;
	}
	cout << endl;
	return;
}

// �������, ���������� �� ������������� ������
void init_spis(list** beg, list** end) {
	*beg = *end = 0;
	return;
}

// �������, ���������� �� �������� ������
void udal_spis(list** beg, list** end) {
	list* tec;
	while (*beg) {
		tec = *beg;
		*beg = (*beg)->link;
		delete tec;
	}
	*end = 0;
	// ������ ����
	return;
}