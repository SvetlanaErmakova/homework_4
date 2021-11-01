#include "header.hpp"
#include "Autotest.hpp"
int main()
{
    //русификация ввода,вывода консоли
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);//!!!сохранить файл в кодировке ansi а не utf-8

    if (Autotest() != 1)
    {
        cout << "Error! Tests not passed!\n";
        return 0;
    }

    priority_queue<Node*, vector<Node*>, comp> pq;//приоритетная очередь для хранения активных узлов дерева Хаффмана

    //процесс архивации

    FILE* stream;
    ifstream file("C:\\Users\\nices\\source\\repos\\sem3\\homework_4\\my_file.txt", ios::binary | ios::ate);
    long size = file.tellg();//размер файла
    file.close();


    char* list = new char[size];
    int numread;
    string text1;//текст из файла

    if (fopen_s(&stream, "C:\\Users\\nices\\source\\repos\\sem3\\homework_4\\my_file.txt", "r+b") == 0)
    {
        numread = fread(list, sizeof(char), size, stream);//вернет сколько считалось
        for (int y = 0; y < size; y++)
        {
            text1 = text1 + list[y];
        }
        fclose(stream);
    }
    delete[] list;

    string archive = Huf_str(text1, &pq);//архив: символы, двоичные коды которых - строка хаффмана(коды хаффмана в порядке символов в тексте)


    char* list1 = new char[archive.size()];
    for (int i = 0; i < archive.size(); i++)//превращаем archive в массив char
    {
        list1[i] = archive[i];
    }
    FILE* file1;
    if (fopen_s(&file1, "C:\\Users\\nices\\source\\repos\\sem3\\homework_4\\archive.txt", "wb") == 0)
    {
        numread = fwrite(list1, sizeof(char), archive.size(), file1);
        fclose(file1);
    }
    delete[] list1;

    cout << "\nthe file is zipped!\n";

    //так добавит лишние переводы строк
    //out.open("C:\\Users\\nices\\source\\repos\\sem3\\homework_4_2\\archive.txt"); // окрываем файл для записи
    //if (out.is_open())
    //{
    //    out << archive << std::endl; //заархивированный файл
    //}
    //out.close();

    //процесс разархивации
    string text2 = unarchive(archive, &pq);//изначальный текст

    char* list2 = new char[text2.size()];
    for (int i = 0; i < text2.size(); i++)//превратить text2 в массив чаров
    {
        list2[i] = text2[i];
    }
    FILE* file2;
    if (fopen_s(&file2, "C:\\Users\\nices\\source\\repos\\sem3\\homework_4\\file_after.txt", "wb") == 0)
    {
        numread = fwrite(list2, sizeof(char), text2.size(), file2);
        fclose(file2);
    }
    delete[] list2;

    cout << "\nthe file is unzipped!\n";
	return 0;
}
