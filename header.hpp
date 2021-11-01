#include <iostream>
#include <string>
#include <queue>//для очереди - построить дерево хаффмана
#include <unordered_map>//с каждым символов текста ассоциируем код хаффмана
#include <fstream>//для чтения из файла

#include <Windows.h> // Обязательно для SetConsoleCP() и SetConsoleOutputCP()

using namespace std;
// узел дерева
struct Node
{
	char ch;//символ
	int freq;//частота
	Node* left, * right;
};

//сравнение в приоритетеной очереди - самый редкий элт - наивысшей приоритет
struct comp
{
	bool operator()(Node* l, Node* r)
	{
		//элемент с наивысшим приоритетом имеет самую низкую частоту
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
