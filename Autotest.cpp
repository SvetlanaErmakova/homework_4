#include <iostream>
#include "header.hpp"
#include "Autotest.hpp"

using namespace std;

int Autotest1()
{
    int f = 0;

    priority_queue<Node*, vector<Node*>, comp> pq;//приоритетная очередь для хранения активных узлов дерева Хаффмана

    FILE* stream;
    ifstream file("C:\\Users\\nices\\source\\repos\\sem3\\homework_4\\Autotest1.txt", ios::binary | ios::ate);
    long size = file.tellg();
    file.close();


    char* list = new char[size];
    int  numread;
    string text1;

    if (fopen_s(&stream, "C:\\Users\\nices\\source\\repos\\sem3\\homework_4\\Autotest1.txt", "r+b") == 0)
    {
        numread = fread(list, sizeof(char), size, stream);
        for (int y = 0; y < size; y++)
        {
            text1 = text1 + list[y];
        }
        fclose(stream);
    }
    delete[] list;

    string archive = Huf_str(text1, &pq);//архив: символы двоичные коды которых - строка хаффмана
    string text2 = unarchive(archive, &pq);
    if(text2.length()== text1.length()&& text2[0]== text1[0])
    {
        f = 1;
        cout << "Test 1 passed...\n";
    }
    else
    {
        cout << "Test 1 failed!\n";
        f = 0;
    }
    return f;

}

int Autotest2()
{
    int f = 0;

    priority_queue<Node*, vector<Node*>, comp> pq;//приоритетная очередь для хранения активных узлов дерева Хаффмана

    FILE* stream;
    ifstream file("C:\\Users\\nices\\source\\repos\\sem3\\homework_4\\Autotest2.txt", ios::binary | ios::ate);
    long size = file.tellg();
    file.close();


    char* list = new char[size];
    int numread;
    string text1;

    if (fopen_s(&stream, "C:\\Users\\nices\\source\\repos\\sem3\\homework_4\\Autotest2.txt", "r+b") == 0)
    {
        numread = fread(list, sizeof(char), size, stream);
        for (int y = 0; y < size; y++)
        {
            text1 = text1 + list[y];
        }
        fclose(stream);
    }
    delete[] list;

    string archive = Huf_str(text1, &pq);//архив: символы двоичные коды которых - строка хаффмана
    string text2 = unarchive(archive, &pq);
    if (text2.length() == text1.length() && text2[0] == text1[0])
    {
        f = 1;
        cout << "Test 2 passed...\n";
    }
    else
    {
        cout << "Test 2 failed!\n";
        f = 0;
    }
    return f;
}

int Autotest3()
{
    int f = 0;

    priority_queue<Node*, vector<Node*>, comp> pq;//приоритетная очередь для хранения активных узлов дерева Хаффмана

    FILE* stream;
    ifstream file("C:\\Users\\nices\\source\\repos\\sem3\\homework_4\\Autotest3.txt", ios::binary | ios::ate);
    long size = file.tellg();
    file.close();


    char* list = new char[size];
    int numread;
    string text1;

    if (fopen_s(&stream, "C:\\Users\\nices\\source\\repos\\sem3\\homework_4\\Autotest3.txt", "r+b") == 0)
    {
        numread = fread(list, sizeof(char), size, stream);
        for (int y = 0; y < size; y++)
        {
            text1 = text1 + list[y];
        }
        fclose(stream);
    }
    delete[] list;

    string archive = Huf_str(text1, &pq);//архив: символы двоичные коды которых - строка хаффмана
    string text2 = unarchive(archive, &pq);
    if (text2.length() == text1.length() && text2[0] == text1[0])
    {
        f = 1;
        cout << "Test 3 passed...\n";
    }
    else
    {
        cout << "Test 3 failed!\n";
        f = 0;
    }
    return f;
}


int Autotest()
{
    if (Autotest1() * Autotest2() * Autotest3() == 1)
        return 1;
    else
        return 0;
}

