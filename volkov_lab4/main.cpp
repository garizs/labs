#include <windows.h>
#include <iostream>

using namespace std;

int length;
HANDLE hSemaphore;

int a;

CRITICAL_SECTION cs;


DWORD WINAPI work(LPVOID pr)
{
	//Сразу входим в критическую секцию, чтобы поток SumElement не начал суммировать раньше времени.
	EnterCriticalSection(&cs);

	//sl для сна
	DWORD sl;
	//ELEM_READY чтобы знать, когда можно потоку main отобразить элемент.
	bool ELEM_READY = false;
	//tmp для перетасовки массива
	float tmp;

	cout << "\nПоток work: введем время для `сна`: "; cin >> sl;
	cout << endl;
	int k = 0;
	for (int i = 0; i < length; i++)
	{
		if (((int*)pr)[i] > a)
		{
			((int*)pr)[k] = ((int*)pr)[i];
			k++;
			ReleaseSemaphore(hSemaphore, 1, NULL);
			Sleep(sl);
		}		
	}

	for (UINT i = k; i < length; i++){
		((int*)pr)[i] = 0;
	}

	//Массив обработан, выходим из критической секции, даем волю SumElement
	LeaveCriticalSection(&cs);

	return 0;
}

//Функция потока SumElement
DWORD WINAPI SumElement(LPVOID pr)
{
	Sleep(500);
	EnterCriticalSection(&cs);

	int sum = 0;

	cout << "\nИтоговый массив: " << endl;
	//Суммируем
	for (int i = 0; i < length; i++){
		sum += ((int*)pr)[i];
		cout << ((int*)pr)[i] << ' ';
	}
 
	cout << "\n\nПоток SumElement: сумма итогового массива: " << sum;
	LeaveCriticalSection(&cs);
	return 0;
}

int main()
{
	cout << "Введем размерность массива: "; cin >> length; cout << endl;
	int* mas = new int[length];
	cout << "Введем элементы массива (целочисленные!)" << endl;
	for (int i = 0; i < length; i++) {
		cin >> mas[i];
	}
	cout << "Размерность: " << length << endl;
	cout << "Массив: " << endl;
	for (int i = 0; i < length; i++){
		cout << mas[i] << " ";
	}
	cout << "\nВведем число для сравнения: " << endl;
	cin >> a;
	HANDLE hThread;
	DWORD IDThread;
	hSemaphore = CreateSemaphore(NULL, 0, 10, NULL); 
	if (hSemaphore == NULL)
		return GetLastError();

	InitializeCriticalSection(&cs);
	HANDLE work_thread = CreateThread(NULL, 0, work, mas, 0, &IDThread);
	if (work_thread == NULL)
		return GetLastError();
	HANDLE sum_thread = CreateThread(NULL, 0, SumElement, mas, 0, &IDThread);
	if (sum_thread == NULL)
		return GetLastError();
	for (int i = 0; i < length; i++) {
		WaitForSingleObject(hSemaphore, INFINITE);
		cout << mas[i] << "\t<-- новый элемент массива" << endl << flush;
	}
	WaitForSingleObject(sum_thread, INFINITE);
	CloseHandle(hSemaphore);
	CloseHandle(work_thread);
	CloseHandle(sum_thread);

	cout << endl << "Готово!";

	return 0;
}
