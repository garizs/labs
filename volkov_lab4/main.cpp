#include <windows.h>
#include <iostream>

using namespace std;

int length;
HANDLE hSemaphore;

CRITICAL_SECTION cs;
DWORD WINAPI work(a)
{
	int j = 0;
	cin >> time;
	for (int i = 0; i < length; i++) {
		if (a > mas[i]){
			int buf = mas[i];
			mas[i] = 0;
			mas[j] = buf;
			j++;
			ReleaseSemaphore(hSemaphore, 1, NULL);
			Sleep(time);
		}

	}
	int i, j;
	for (j = 0; j < 10; j++)
	{
		// входим в критическую секцию
		EnterCriticalSection(&cs);
		for (i = 0; i < 10; i++)
		{
			cout << j << ' '; 
			cout.flush();
		}
		cout << endl;
		// выходим из критической секции
		LeaveCriticalSection(&cs);
	}
	return 0;
}

DWORD WINAPI SumElement(LPVOID)
{
	WaitForSingleObject(work, INFINITE);

	return 0;
}

int main()
{
	cin >> length;
	int* mas = new int[length];
	for (int i = 0; i < length; i++) {
		cin >> mas[i];
	}
	int k, a;
	cin >> k;
	cin >> a;
	HANDLE hThread;
	DWORD IDThread;
	hSemaphore = CreateSemaphore(NULL, 0, 10, NULL); 
	if (hSemaphore == NULL)
		return GetLastError();

	// инициализируем критическую секцию
	//InitializeCriticalSection(&cs);
	work_thread = CreateThread(NULL, 0, work, a, 0, &IDThread);
	sum_thread = CreateThread(NULL, 0, SumElement, NULL, 0, &IDThread);

	if (work_thread == NULL)
		return GetLastError();

	for (int i = 0; i < length; i++) {
		WaitForSingleObject(hSemaphore, INFINITE);
		cout << mas[i] << ' ' << flush;
	}
	//for (j = 10; j < 20; j++)
	//{
	//	// входим в критическую секцию
	//	EnterCriticalSection(&cs);
	//	for (i = 0; i < 10; i++)
	//	{
	//		cout << j << ' '; 
	//		cout.flush();
	//	}
	//	cout << endl;
	//	
	//	LeaveCriticalSection(&cs);
	//}
	//
	//DeleteCriticalSection(&cs);
	//
	//WaitForSingleObject(hThread, INFINITE);
	return 0;
}