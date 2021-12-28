#include <iostream>
#include <windows.h>

#pragma comment(lib, "winmm.lib")

using namespace std;

UINT TM1, TM2, TM3;
int C2;
DWORD time_var3;

void main_menu();
void var_1();
void var_2();
void var_3();
void err();

DWORD p1();
DWORD p2();
DWORD p3();
DWORD p4();
DWORD p5();

void CALLBACK time_proc1(HWND hwnd, UINT message, UINT idTimer, DWORD dwTimer);
void CALLBACK time_proc2(HWND hwnd, UINT message, UINT idTimer, DWORD dwTimer);
void CALLBACK time_proc3(UINT uTimerID, UINT uMessage, DWORD dwUser, DWORD dw1, DWORD dw2);

int main()
{
	main_menu();
}

void main_menu()
{
	while (true)
	{
		int item = 0;
		cout
			<< " Enter the variant number: \n"
			<< " 1. First variant I\n"
			<< " 2. Second variant\n"
			<< " 3. Third variant\n"
			<< " 0. Exit\n";

		//-----------CIN-PART------------//
		cout << "\n -> "; cin >> item;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			err();
			continue;
		}
		//-----------CIN-PART------------//

		switch (item)
		{
		case 1: var_1(); break;
		case 2: var_2(); break;
		case 3: var_3();  break;
		case 0: return;
		default: err(); break;
		}
	}
}

void err()
{
	system("cls");
	cout << " Error: Something wrong. Try again.\n\n";
}

void var_1()
{
	system("cls");
	MSG msg = {};
	C2 = 3;
	TM1 = SetTimer(NULL, NULL, 8400, (TIMERPROC)time_proc1);
	TM2 = SetTimer(NULL, NULL, 8700, (TIMERPROC)time_proc1);
	TM3 = SetTimer(NULL, NULL, 4500, (TIMERPROC)time_proc1);

	while (GetMessage(&msg, 0, 0, 0))
	{
		DispatchMessage(&msg);
		if (C2 == 0)
			break;
	}
	Sleep(300);
	cout << endl;
}

void var_2()
{
	system("cls");
	C2 = 4;
	MSG msg = {};

	TM2 = SetTimer(NULL, NULL, 1400, (TIMERPROC)time_proc2);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		DispatchMessage(&msg);
		if (C2 == 0)
			break;
	}

	Sleep(1000);
	cout << endl;
}

void var_3()
{
	system("cls");
	C2 = 0;
	int check = 3;
	MSG msg = {};
	time_var3 = GetTickCount64();
	TM1 = timeSetEvent(7500, 0, time_proc3, GetTickCount64(), TIME_PERIODIC);
	if (TM1 == 0)
		err();
	while (true) {
		if ((C2 == -1) || (C2 == check)) {
			timeKillEvent(TM1);
			break;
		}
	}
	Sleep(1000);
	cout << endl;
}

void CALLBACK time_proc1(HWND hwnd, UINT message, UINT idTimer, DWORD dwTimer)
{
	if (idTimer == TM1)
	{
		cout << " p1 - " << GetTickCount64() - dwTimer << " - ";
		p2();
		cout << GetTickCount64() - dwTimer << endl;
		timeKillEvent(TM1);
		C2--;
	}

	if (idTimer == TM2)
	{
		cout << " p2 - " << GetTickCount64() - dwTimer << " - ";
		p3();
		cout << GetTickCount64() - dwTimer << endl;
		timeKillEvent(TM2);
		C2--;
	}

	if (idTimer == TM3)
	{
		cout << " p3 - " << GetTickCount64() - dwTimer << " - ";
		p4();
		cout << GetTickCount64() - dwTimer << endl;
		timeKillEvent(TM3);
		C2--;
	}
}

void CALLBACK time_proc2(HWND hwnd, UINT message, UINT idTimer, DWORD dwTimer)
{

	if (idTimer == TM2)
	{
		cout << " p1 - " << GetTickCount64() - dwTimer << " - ";
		p2();
		cout << GetTickCount64() - dwTimer << endl;
		C2--;

		TM3 = SetTimer(NULL, NULL, 700, (TIMERPROC)time_proc2);

		if (C2 == 0)
			timeKillEvent(TM2);
	}

	if (idTimer == TM3)
	{
		cout << " p2 - " << GetTickCount64() - dwTimer << " - ";
		p3();
		cout << GetTickCount64() - dwTimer << endl;
		timeKillEvent(TM3);
	}
}

void CALLBACK time_proc3(UINT uTimerID, UINT uMessage, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	if (TM1 == uTimerID)
	{
		DWORD p_result = p1(); C2++;
		cout << " p1 = " << p_result << " -> " << GetTickCount64() - time_var3 << endl;
		switch (p_result)
		{
		case 0:
			cout << " z1\n";
			TM2 = timeSetEvent(6300, 35, time_proc3, GetTickCount64(), TIME_ONESHOT);
			break;
		case 2:
			cout << " z2\n";
			TM3 = timeSetEvent(4500, 45, time_proc3, GetTickCount64(), TIME_ONESHOT);
			break;
		case 3:
			cout << " z3 and kill\n\n";
			C2 = -1;
			KillTimer(NULL, TM1);
			break;
		default:
			break;
		}
		time_var3 = GetTickCount64();
	}

	if (TM2 == uTimerID)
	{
		cout << " p2 " << endl;
		p2();
		KillTimer(NULL, TM2);
	}

	if (TM3 == uTimerID)
	{
		cout << " p3" << endl;
		p3();
		KillTimer(NULL, TM3);
	}


}

DWORD p1() {
	srand(time(NULL));
	DWORD i, j, result = 0;
	i = 1 + rand() % 30;
	j = GetTickCount64();
	while ((GetTickCount64() - j) < i)
		result = rand() % 5;

	return result;
}

DWORD p2() {
	srand(time(NULL));
	DWORD i, j, result = 0;
	i = 1 + rand() % 40;
	j = GetTickCount64();
	while ((GetTickCount64() - j) < i)
		result = rand() % 5;

	return result;
}

DWORD p3() {
	srand(time(NULL));
	DWORD i, j, result = 0;
	i = 1 + rand() % 50;
	j = GetTickCount64();
	while ((GetTickCount64() - j) < i)
		result = rand() % 5;

	return result;
}

DWORD p4() {
	srand(time(NULL));
	DWORD i, j, result = 0;
	i = 1 + rand() % 60;
	j = GetTickCount64();
	while ((GetTickCount64() - j) < i)
		result = rand() % 5;

	return result;
}
DWORD p5() {
	srand(time(NULL));
	DWORD i, j, result = 0;
	i = 1 + rand() % 70;
	j = GetTickCount64();
	while ((GetTickCount64() - j) < i)
		result = rand() % 5;
	return result;
}