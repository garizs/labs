#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <vector>

using namespace std;

//��������� ������ � ������� ������.
struct emp
{
	int num;
	char name[10];
	double grade;
};

//����.
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//��������� ����������.
	FILE* file; //��������� ��� ������ � ������
	LPVOID tmp; //��������� �� ������ ������.
	emp data_struct; //������� �������� emp
	char filename[] = "students.dat"; //��������� �������� �����.
	CHAR name[] = "child.exe"; //��������� �������� ������� ��������.
	CHAR com_list[100] = { 0 }; //������� ���������� ��� �������� ������ �� ��������� �������.
	string str; //������� ������ ��� ����������� ������ � ��� ������ ��������� ������.
	string grade; //
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION pi;

	//��������� ���� � �������� ������ ������ � ������.
	file = fopen(filename, "ab+");
	//������ � ������� ������ �� �����.
	while (!feof(file))
	{
		if (fread(&data_struct, sizeof(data_struct), 1, file) > 0)
			cout << "\n\t"
			<< data_struct.num
			<< " - "
			<< data_struct.name
			<< " - "
			<< data_struct.grade
			<< endl;
		else
			cout << "\n\t...\n";
	}

	int n;
	cout << "\n\t������� ����������� ���������� �������: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		//������ ������ � ��������� �� � ����.
		cout << "\n\n\t������� ����� ��������: ";
		cin >> data_struct.num;
		cout << "\n\t������� ���: ";
		cin >> data_struct.name;
		cout << "\n\t������� ������: ";
		cin >> data_struct.grade;
		fwrite(&data_struct, sizeof(data_struct), 1, file);
	}
	fclose(file); //��������� ����.

	//������ ������ ��� �������� � �������� �������.
	cout << "\n\n\t�������� ������ � ������� Child";
	cout << "\n\n\t������� �����: ";
	cin >> data_struct.num; 
	cout << "\n\n\t������� ���: ";
	cin >> data_struct.name;
	cout << "\n\n\t������� ������: ";
	cin >> data_struct.grade;

	//����������� � ������ ������ ����������� ���������.
	snprintf(com_list, sizeof com_list, "%s: �����: %i ���: %s ������: %f", filename, data_struct.num, data_struct.name, data_struct.grade);

	//��������� �������. �������� ����������� ������ � �������� ����������.
	//� ������ ������� ������� ��������� �� ������ � ��������� ������� �������.
	if (!CreateProcess(name, com_list, NULL, NULL,
		FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		_cputs("\n\n\tThe new process is not created.\n");
		_cputs("\tPress any key to finish.\n");
		return 0;
	}

	//������� �� �������� ������� �������� � ���� ��� ����������.
	_cputs("\n\n\tThe new process is created.\n");
	WaitForSingleObject(pi.hProcess, INFINITE);

	//������� ����������. ��������� �����������.
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	//����� ��������� ����, ��� � �������� ������ ������.
	file = fopen(filename, "rb");
	//������ ���� � ������� ����������.
	while (!feof(file))
	{
		if (fread(&data_struct, sizeof(data_struct), 1, file) > 0)
			cout << "\n\t"
			<< data_struct.num
			<< " - "
			<< data_struct.name
			<< " - "
			<< data_struct.grade;
		else
			cout << "\n\t";
	}
	fclose(file);

	system("pause");
	return 0;
}