#pragma once
/* ������������ ���� ModSp1.h
* �������� ����������� ����� ����� � ���������� 
������� ��� ������ �� ������� */
// ����������� �����
typedef int telem; // ����������� ���� ��������������� ����
struct list {	   // ����������� ���� �������� ������
	telem data;	   // �������������� ����
	list* link;	   // ���� ������
};
// ���������� (���������) �������
void init_spis(list**, list**);
void add_spis(telem, list**, list**);
void obrabotka(list*);
void view_spis(list*);
void udal_spis(list**, list**);
