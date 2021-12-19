#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <vector>

using namespace std;

//Структура данная в условии задачи.
struct emp
{
	int num;
	char name[10];
	double grade;
};

//Вход.
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//Объявляем переменные.
	FILE* file; //Пременная для работы с файлом
	LPVOID tmp; //Указатель на пустой объект.
	emp data_struct; //Заводим экземляр emp
	char filename[] = "students.dat"; //Сохраняем название файла.
	CHAR name[] = "child.exe"; //Сохраняем название второго процесса.
	CHAR com_list[100] = { 0 }; //Заводим переменную для передачи команд во вторичный процесс.
	string str; //Создаем строки для последующей записи в них данных одинарной записи.
	string grade; //
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION pi;

	//Открываем файл в бинарном режиме чтения и записи.
	file = fopen(filename, "ab+");
	//Читаем и выводим данные из файла.
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
	cout << "\n\tВведите необходимое количество записей: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		//Делаем запись и сохраняем ее в файл.
		cout << "\n\n\tВведите номер студента: ";
		cin >> data_struct.num;
		cout << "\n\tВведите имя: ";
		cin >> data_struct.name;
		cout << "\n\tВведите оценку: ";
		cin >> data_struct.grade;
		fwrite(&data_struct, sizeof(data_struct), 1, file);
	}
	fclose(file); //Закрываем файл.

	//Вводим данные для передачи в дочерний процесс.
	cout << "\n\n\tПередаем данные в процесс Child";
	cout << "\n\n\tВведите номер: ";
	cin >> data_struct.num; 
	cout << "\n\n\tВведите имя: ";
	cin >> data_struct.name;
	cout << "\n\n\tВведите оценку: ";
	cin >> data_struct.grade;

	//Преобразуем к строке данные сохраненные структуру.
	snprintf(com_list, sizeof com_list, "%s: Номер: %i Имя: %s Оценка: %f", filename, data_struct.num, data_struct.name, data_struct.grade);

	//Запускаем процесс. Передаем необходимые данные в качестве параметров.
	//В случае неудачи выводим сообщение об ошибке и завершаем текущий процесс.
	if (!CreateProcess(name, com_list, NULL, NULL,
		FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		_cputs("\n\n\tThe new process is not created.\n");
		_cputs("\tPress any key to finish.\n");
		return 0;
	}

	//Говорим об успешном запуске процесса и ждем его завершения.
	_cputs("\n\n\tThe new process is created.\n");
	WaitForSingleObject(pi.hProcess, INFINITE);

	//Процесс завершился. Закрываем дискрипторы.
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	//Снова открываем файл, уже в бинарном режиме чтения.
	file = fopen(filename, "rb");
	//Читаем файл и выводим информацию.
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