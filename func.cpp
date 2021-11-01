#include "header.hpp"

//������� ����� ���� ������
Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

//������ ������ ��������(�������� ������������ �������) � ���������� �����
string Huf_str(string text, priority_queue<Node*, vector<Node*>, comp> *pq)
{
	//���������� ������� ��������� ������� �������(����) � ������ � ���������� �� (��������)
	unordered_map<char, int> freq;// char - ����, int - �������� 
	for (char ch : text)
	{
		freq[ch]++;//��������� ��������
	}

	for (auto elt : freq) //������ �� ����� map
	{
		(*pq).push(getNode(elt.first, elt.second, nullptr, nullptr));//�������� �������� ���� ��� ������� ������� � ������������� �������
	}

	while (((*pq)).size() > 1)//!= 1)
	{
		//������� ��� ���� � ��������� ����������� (����� ������ �������) �� �������
		Node* left = (*pq).top(); //������ ������ �� ��� � ��������� �����������(����� ������)
		(*pq).pop();//������� ��� �� �������
		Node* right = (*pq).top();//��������� � ���� �� ���� ������ � �������(������ �� ��������)
		(*pq).pop();//������� ��� �� �������

		//������� ����� ���������� ���� � ����� ����� ������ ������������
		//�������� ����� ���� � ������������ �������
		int sum = left->freq + right->freq;
		(*pq).push(getNode('\0', sum, left, right));
	}

	Node* root = (*pq).top();

	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);//��������� ���� �������� � huffmanCode

	string str = "";//������ ��������
	for (char ch : text) {
		str += huffmanCode[ch];//���������� ������ �������� ��������������� ��������� ���� �������� ��� ������� �������������� �������
	}

	//cout << str << "\n";

	string str2;//������ �� ������ 8 ��� �� ��� ��������
	string str3 = "";//������ ��������(���� ������� ������������ ����� ������ ��� ��������) �� ����� ������ � ���������������� ����� 

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
			sym = symvol(str2);//����������� � ������ � ����� ��� ����� � str2
			str3 = str3 + sym;
			for (int i = 0; i < 8; i++)//������� ������ 8 �������� �� ��� ��������(�� ������ � str2)
			{
				str.erase(0, 1);
				str_len--;
			}

		}
		else if (str_len > 0)//�������� � ������ �������� ����� 8�� ����
		{
			str2 = str;//0101
			for (int i = 0; i < 8 - str_len; i++)//str2 ����� 0101 0000
				str2 = str2 + "0";

			sym = symvol(str2);
			str3 = str3 + sym;
			str3.insert(0, to_string(8 - str_len));//�������� � ������ ������ ������� ���������� ����� �������� �������� �� 8�� ���
			str_len = -1;
		}
	}
	return str3;

}

//������ �� ������ �������� � ��������� ���� ��������
void encode(Node* root, string str, unordered_map<char, string>& huffmanCode)
{
	if (root == nullptr)
		return;

	// ������ �������� ���� - ��������(��� �����������)
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;//�������� ��� ����� �������
	}

	//�������� ���� �� ������ ���� - ���� ��� �����������
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
	Node* root = (*pq).top();//��������� �� �� ��� � ��������� ����������� � ������������ ������� - ����� ������ ������

	string str = "";//������ ��������
	string rez_str;
	str = to_haf_str(text1_);//������� �� ����� �������� �� ����������������� ����� � ��� ��������
								//������ ������ - ��� ������ ����� <8 -������� ����������� 0 � ����� ���� ������ �������(�� �� ���� �������� � ��� ���)

	//cout << str << "\n";

	int index = -1;

	while (index < (int)str.size() - 2)
	{
		decode(root, &index, str, &rez_str);
	}
	return rez_str;//����������������� �����
}
string to_haf_str(string text1_)//������� �� ����� �������� �� ����������������� ����� � ��� ��������
{							//������ ������ - ��� ������ ����� <8 -������� ����������� 0 � ������ ���� ������ �������(�� �� ���� �������� � ��� ���)
	int dop_nul = text1_[0] - '0';//������� ��� ����� � ����� ���� ���������� �������

	int cod;
	string huf_str;

	int mas[8] = {128, 64, 32, 16, 8, 4, 2, 1};

	for (int i = 1; i < text1_.size(); i++)//�� ������� ����(1�� -������� ��� ����� � ������ ���� ���������� �������)
	{
		cod = (int)text1_[i];//���������� ��� �������

		if (i == text1_.size() - 1)// � ���� ������ ������� ������ ���� � ������
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

//������ �� ������ �������� � ������������� �������������� ������
void decode(Node* root, int* index, string str, string* rez_str)//� string 255 �������� - �� ������ �� ���������� �� �����? ������ �����?���� ����� ����� ��������.
{
	if (root == nullptr)
		return;

	// ����� �������� ���� - ��������(��� �����������)
	if (!root->left && !root->right)
	{
		//cout << root->ch;//�������� ����� ����(������ �� ������������ ������)
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
		if (str[*index] == '0')//� ������ �������� 0 - ���� � ������ �����
			decode(root->left, index, str, rez_str);
		else//� ������ �������� 1 - ���� � ������ ������
			decode(root->right, index, str, rez_str);
	}
}
