#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

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
		cout << argv[i] << " " << endl;;
	}
	//Заводим вектор, так как мы не знаем сколько будет записей.
	vector<emp> data_struct;
	//Заводим tmp экземпляр класса. Это значительно упростит операции.
	emp struct_temp;
	//Сохраняем в tmp полученные данные для их структуризации.
	struct_temp.num = atoi(argv[2]);
	strcpy(struct_temp.name, argv[4]);
	struct_temp.grade = atof(argv[6]);
	//Запихиваем полученные данные (tmp) в начало вектора/
	data_struct.push_back(struct_temp);

	//Открываем файл в режиме бинарного чтения.
	FILE* file = fopen("student_data.dat", "rb");
	//i для счета записей. Чтобы знать сколько потом записывать.
	//(Можно было воспользоваться размеров вектора)
	UINT i = 0;

	//Читаем файл и записываем данные в вектор до упора.
	while (!feof(file))
	{
		fread(&struct_temp, sizeof(emp), 1, file);
		data_struct.push_back(struct_temp);
	}
	fclose(file);

	//Открываем в режиме перезаписи.
	file = fopen("student_data.dat", "wb");
	for (UINT j = 1; j < data_struct.size(); j++)
	{
		//j+1, так как в начале лежат полученные данные от процесса родителя.
		//Ищем нужную запись. Находим и перезаписываем grade.
		if (data_struct[j].num == data_struct[0].num)
		{
			cout << "\n\n\t Введите оценку: "; cin >> data_struct[j].grade;
		}
		fwrite(&data_struct[j], sizeof(emp), 1, file);
	}
	fclose(file);
	system("pause");
	return 0;
}