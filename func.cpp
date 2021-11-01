#include "header.hpp"

//создать новый узел дерева
Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

//строит дерево хаффмана(изменяет приоритетную очередь) и возвращает архив
string Huf_str(string text, priority_queue<Node*, vector<Node*>, comp> *pq)
{
	//подсчитать частоту появления каждого символа(ключ) в тексте и сохраняить ее (значение)
	unordered_map<char, int> freq;// char - ключ, int - значение 
	for (char ch : text)
	{
		freq[ch]++;//увеличить значение
	}

	for (auto elt : freq) //пройти по всему map
	{
		(*pq).push(getNode(elt.first, elt.second, nullptr, nullptr));//добавить листовой узел для каждого символа в приоритетеную очередь
	}

	while (((*pq)).size() > 1)//!= 1)
	{
		//Удалить два узла с наивысшим приоритетом (самая низкая частота) из очереди
		Node* left = (*pq).top(); //вернет сслыку на элт с наивысшим приоритетом(самый редкий)
		(*pq).pop();//удаляем его из очереди
		Node* right = (*pq).top();//обращение к элту кт стал первым в очереди(второй по редкости)
		(*pq).pop();//удаляем его из очереди

		//Создать новый внутренний узел с этими двумя узлами наследниками
		//Добавить новый узел в приоритетную очередь
		int sum = left->freq + right->freq;
		(*pq).push(getNode('\0', sum, left, right));
	}

	Node* root = (*pq).top();

	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);//сохранить коды хаффмана в huffmanCode

	string str = "";//строка хаффмана
	for (char ch : text) {
		str += huffmanCode[ch];//составляем строку хаффмана последовательно записывая коды хаффмана для каждого встречающегося символа
	}

	//cout << str << "\n";

	string str2;//строка из первых 8 бит из стр хаффмана
	string str3 = "";//строка символов(коды которых представляют собой данную стр хаффмана) кт будет лежать в заархивированном файле 

	char sym;
	int str_len = str.length();
	while (str_len >= 0)
	{
		if (str_len == 0)
		{
			str_len--;
			str3.insert(0, to_string(0));
		}
		if (str_len >= 8)
		{
			str2 = str.substr(0, 8);
			sym = symvol(str2);//преобразуем в символ с кодом как цифры в str2
			str3 = str3 + sym;
			for (int i = 0; i < 8; i++)//удалить первые 8 символов из стр хаффмана(кт сейчас в str2)
			{
				str.erase(0, 1);
				str_len--;
			}

		}
		else if (str_len > 0)//осталось в строке хаффмана менее 8ми цифр
		{
			str2 = str;//0101
			for (int i = 0; i < 8 - str_len; i++)//str2 стала 0101 0000
				str2 = str2 + "0";

			sym = symvol(str2);
			str3 = str3 + sym;
			str3.insert(0, to_string(8 - str_len));//добавить в начало архива сколько незначимых нулей пришлось добавить до 8ми бит
			str_len = -1;
		}
	}
	return str3;

}

//пройти по дереву хаффмана и сохранить коды хаффмана
void encode(Node* root, string str, unordered_map<char, string>& huffmanCode)
{
	if (root == nullptr)
		return;

	// найден листовой узел - конечный(нет наследников)
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;//записать код этого символа
	}

	//рекурсия пока не найдем лист - узел без наследников
	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}
char symvol(string str2)
{
	int mas[8] = { 128, 64, 32, 16, 8, 4, 2, 1 };
	int sum = 0;
	int str_len = str2.length();

	for (int i = 0; i < str_len; i++)
	{
		sum = sum + (((str2[i] - '0') << (str_len - i - 1)) & mas[i]);
	}
	return (char)sum;
}

string unarchive(string text1_, priority_queue<Node*, vector<Node*>, comp>* pq)
{
	Node* root = (*pq).top();//указатель на на элт с наивысшим приоритетом в приоритетной очереди - самый редкий символ

	string str = "";//строка хаффмана
	string rez_str;
	str = to_haf_str(text1_);//переход от кодов символов из заархивированного файла к стр хаффмана
								//первый символ - это всегда цифра <8 -сколько добавленных 0 в конце кода послед символа(их не надо помещать в стр хаф)

	//cout << str << "\n";

	int index = -1;

	while (index < (int)str.size() - 2)
	{
		decode(root, &index, str, &rez_str);
	}
	return rez_str;//разархивированный текст
}
string to_haf_str(string text1_)//переход от кодов символов из заархивированного файла к стр хаффмана
{							//первый символ - это всегда цифра <8 -сколько добавленных 0 в начале кода послед символа(их не надо помещать в стр хаф)
	int dop_nul = text1_[0] - '0';//сколько доп нулей в конце кода последнего символа

	int cod;
	string huf_str;

	int mas[8] = {128, 64, 32, 16, 8, 4, 2, 1};

	for (int i = 1; i < text1_.size(); i++)//от второго элта(1ый -сколько доп нулей в начале кода последнего символа)
	{
		cod = (int)text1_[i];//десятичный код символа

		if (i == text1_.size() - 1)// в коде послед символа лишние нули в начале
		{
			for (int j = 0; j < 8- dop_nul; j++)
			{
				if ((cod & mas[j]) != 0)
					huf_str = huf_str + "1";
				else
					huf_str = huf_str + "0";
			}
		}
		else
		{
			for (int j = 0; j < 8; j++)
			{
				if ((cod & mas[j]) != 0)
					huf_str = huf_str + "1";
				else
					huf_str = huf_str + "0";
			}
		}
	}
	return huf_str;
}

//пройти по дереву хаффмана и раскодировать закодированную строку
void decode(Node* root, int* index, string str, string* rez_str)//в string 255 символов - мб потому не помещается до конца? массив строк?хотя изнач текст помещает.
{
	if (root == nullptr)
		return;

	// нашел листовой узел - конечный(нет наследников)
	if (!root->left && !root->right)
	{
		//cout << root->ch;//значение этого узла(символ из изначального текста)
		*rez_str = *rez_str + root->ch;
		return;
	}

	(*index)++;

	if (*index == (int)str.length())
	{
		return;
	}
	else
	{
		if (str[*index] == '0')//в строке хаффмана 0 - идем в дереве влево
			decode(root->left, index, str, rez_str);
		else//в строке хаффмана 1 - идем в дереве вправо
			decode(root->right, index, str, rez_str);
	}
}
