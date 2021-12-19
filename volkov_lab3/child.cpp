#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct emp
{
	int num;
	char name[10];
	double grade;
};

int main(int argc, char** argv)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//Выводим полученные данные в консоли.
	cout << "\n\t";
	for (int i = 0; i < argc; i++)
	{
		cout << argv[i] << " ";
	}
	emp tmp, input;

	input.num = atoi(argv[2]);
	strcpy(input.name, argv[4]);
	input.grade = atof(argv[6]);
	FILE* f_iter = fopen("C:\\Users\\garizs\\source\\repos\\labs\\volkov_lab3\\students.dat", "r+b");
	long pos;
	while (!feof(f_iter))
	{
		fread(&tmp, sizeof(emp), 1, f_iter);
		if (tmp.num == input.num) {
			pos = ftell(f_iter) - sizeof(emp);
			fclose(f_iter);
			f_iter = fopen("C:\\Users\\garizs\\source\\repos\\labs\\volkov_lab3\\students.dat", "r+b");
			fseek(f_iter, pos, SEEK_SET);
			fwrite(&input, sizeof(emp), 1, f_iter);
			break;
		}
	}
	fclose(f_iter);

	system("pause");
	return 0;
}
