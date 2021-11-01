#include <iostream>
#include <string>
#include <queue>//��� ������� - ��������� ������ ��������
#include <unordered_map>//� ������ �������� ������ ����������� ��� ��������
#include <fstream>//��� ������ �� �����

#include <Windows.h> // ����������� ��� SetConsoleCP() � SetConsoleOutputCP()

using namespace std;
// ���� ������
struct Node
{
	char ch;//������
	int freq;//�������
	Node* left, * right;
};

//��������� � ������������� ������� - ����� ������ ��� - ��������� ���������
struct comp
{
	bool operator()(Node* l, Node* r)
	{
		//������� � ��������� ����������� ����� ����� ������ �������
		return l->freq > r->freq;
	}
};

string Huf_str(string text, priority_queue<Node*, vector<Node*>, comp>* pq);
void encode(Node* root, string str, unordered_map<char, string>& huffmanCode);
char symvol(string str2);


string unarchive(string text1_, priority_queue<Node*, vector<Node*>, comp> *pq);
void decode(Node* root, int* index, string str, string* rez_str);
string to_haf_str(string text1_);

#pragma once
