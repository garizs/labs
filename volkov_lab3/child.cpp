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
	//������� ���������� ������ � �������.
	cout << "\n\t";
	for (int i = 0; i < argc; i++)
	{
		cout << argv[i] << " " << endl;;
	}
	//������� ������, ��� ��� �� �� ����� ������� ����� �������.
	vector<emp> data_struct;
	//������� tmp ��������� ������. ��� ����������� �������� ��������.
	emp struct_temp;
	//��������� � tmp ���������� ������ ��� �� ��������������.
	struct_temp.num = atoi(argv[2]);
	strcpy(struct_temp.name, argv[4]);
	struct_temp.grade = atof(argv[6]);
	//���������� ���������� ������ (tmp) � ������ �������/
	data_struct.push_back(struct_temp);

	//��������� ���� � ������ ��������� ������.
	FILE* file = fopen("student_data.dat", "rb");
	//i ��� ����� �������. ����� ����� ������� ����� ����������.
	//(����� ���� ��������������� �������� �������)
	UINT i = 0;

	//������ ���� � ���������� ������ � ������ �� �����.
	while (!feof(file))
	{
		fread(&struct_temp, sizeof(emp), 1, file);
		data_struct.push_back(struct_temp);
	}
	fclose(file);

	//��������� � ������ ����������.
	file = fopen("student_data.dat", "wb");
	for (UINT j = 1; j < data_struct.size(); j++)
	{
		//j+1, ��� ��� � ������ ����� ���������� ������ �� �������� ��������.
		//���� ������ ������. ������� � �������������� grade.
		if (data_struct[j].num == data_struct[0].num)
		{
			cout << "\n\n\t ������� ������: "; cin >> data_struct[j].grade;
		}
		fwrite(&data_struct[j], sizeof(emp), 1, file);
	}
	fclose(file);
	system("pause");
	return 0;
}