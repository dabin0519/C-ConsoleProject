#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <io.h>
#include <fcntl.h>
#include <algorithm>
#include <string>
#include <cmath>
#include "console.h";
#include "GameLogic.h"

using namespace std;

#pragma region 광물 

string coreBagName[CoreNum] = { "   석탄   ", "   구리   ", "    철    ", "    금    ", "다이아몬드" };
int coreBag[CoreNum] = { 0 };
int core[CoreNum] = { 2, 4, 5, 10, 25 };
float percent[CoreNum + 1] = { 500, 200, 100, 50, 1, 149}; //마지막은 안나올 확률
int corePrice[CoreNum] = { 20, 70, 100, 200, 1000 }; // 밸런스 어케 하지 훔...
int wallet = 0; // 지갑 
int sWallet[5] = { 0 };
int secPrice = 0; //초당 벌리는 돈
#pragma endregion

int maxPickAxe = 100; // 나중에 곡괭이 업그레이드
int pickAxe = maxPickAxe; //곡괭이 내구도
int brokeCnt = 6; //캐는 횟수
bool isUpgrade[3];

void Menu() {
	SetModeConsole(false);

	system("cls");
	Sleep(100);
	wcout << L"	███╗   ███╗██╗███╗   ██╗███████╗ ██████╗ ██████╗  █████╗ ██████╗ ███████" << endl;
	Sleep(100);
	wcout << L"	████╗ ████║██║████╗  ██║██╔════╝██╔════╝ ██╔══██╗██╔══██╗██╔══██╗██╔════" << endl;
	Sleep(100);
	wcout << L"	██╔████╔██║██║██╔██╗ ██║█████╗  ██║  ███╗██████╔╝███████║██║  ██║█████╗ " << endl;
	Sleep(100);
	wcout << L"	██║╚██╔╝██║██║██║╚██╗██║██╔══╝  ██║   ██║██╔══██╗██╔══██║██║  ██║██╔══╝ " << endl;
	Sleep(100);
	wcout << L"	██║ ╚═╝ ██║██║██║ ╚████║███████╗╚██████╔╝██║  ██║██║  ██║██████╔╝███████" << endl;
	Sleep(100);
	wcout << L"	╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝ ╚══════" << endl;
	Sleep(100);

	SetModeConsole(true);
	
	string cheat = "치트 모드를 킨다고? 혹시 흐으으으접?";

	cout << "치트모드를 키겠습니까? (y/n) : ";
	int inp = _getch();
	cout << endl;
	switch (inp) {
	case 121:
		wallet += 10000;
		for (int i = 0; i < cheat.size(); i++) 
		{
			cout << cheat[i];
			Sleep(100);
		}
		Sleep(1000);
		break;
	case 110:
		cout << "기본 모드로 시작합니다." << endl;
		Sleep(1000);
		break;
	default:
		cout << "잘못된 키를 입력하였습니다. 다시 입력해주세요.";
		Sleep(1000);
		Menu();
		break;
	}
}

void Render()
{
	system("cls");
	
	SetModeConsole(false);

	wcout << L"     ██╗ ██╗███╗   ███╗███████╗███╗   ██╗██╗   ██╗██╗ ██╗  " << endl;
	wcout << L"    ██╔╝██╔╝████╗ ████║██╔════╝████╗  ██║██║   ██║╚██╗╚██╗ " << endl;
	wcout << L"   ██╔╝██╔╝ ██╔████╔██║█████╗  ██╔██╗ ██║██║   ██║ ╚██╗╚██╗" << endl;
	wcout << L"   ╚██╗╚██╗ ██║╚██╔╝██║██╔══╝  ██║╚██╗██║██║   ██║ ██╔╝██╔╝" << endl;
	wcout << L"    ╚██╗╚██╗██║ ╚═╝ ██║███████╗██║ ╚████║╚██████╔╝██╔╝██╔╝ " << endl;
	wcout << L"     ╚═╝ ╚═╝╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝ ╚═╝  " << endl;
	
	Coin();

	SetModeConsole(true);
	cout << endl;
	cout << endl;
	cout << "- 1. 광질 -" << endl << endl;
	cout << "- 2. 상점 -" << endl << endl;
	cout << "- 3. 가방 -" << endl << endl;
	cout << "- 4. 환전 -" << endl << endl;
	cout << "번호를 입력해주세요 : ";
	int inpN;
	cin >> inpN;
	switch (inpN) {
	case 1:
		Mine();
		break;
	case 2:
		Store();
		break;
	case 3:
		Bag();
		break;
	case 4:
		Change();
		break;
	default:
		cout << "잘.못.입.력.했.어.요. 제발 맞는걸 입력해주세요 ^^";
		Sleep(1000);
		Render();
		break;
	}
}

void Coin() {
	int x = 65;
	int y = 1;
	Gotoxy(x, y);
	wcout << L"▄▀▀▀▀▀▄" << endl;
	Gotoxy(x, y + 1);
	wcout << L"█ █▀▀ █" << endl;
	Gotoxy(x, y + 2);
	wcout << L"█ ▀▀▀ █" << endl;
	Gotoxy(x, y + 3);;
	wcout << L" ▀▀▀▀▀ " << endl;

	CalcNum();

	x += 4; //  x 현재 위치에서 위에코인 텍스트 길이가 7이므로 4를 더해주고 for문 안에서 4씩 더해줘서 겹치지 않도록 4라는 보정치를 선으로 더해줌
	for (int i = 0; i < 5; i++) //아무리 봐도 5자리 이상 안나올것 같기 때문에
	{
		x += 4; // 텍스트 가로 크기가 3이므로 1칸씩 뛰어서 보이도록 4를 더해줌
		switch (sWallet[i]) //calcNum에서 sWallet이 채워졌으므로 각각 가져와서 그 sWallet[i] 에 들어간 값을 switch로 돌려 숫자 출력
		{
		case 1:
			SetModeConsole(false);
			Gotoxy(x, y);
			wcout << L"▄▄ " << endl;
			Gotoxy(x, y + 1);
			wcout << L" █ " << endl;
			Gotoxy(x, y + 2);
			wcout << L"▄█▄" << endl;
			break;
		case 2:
			SetModeConsole(false);
			Gotoxy(x, y);
			wcout << L"▄▄▄" << endl;
			Gotoxy(x, y + 1);
			wcout << L"▄▄█" << endl;
			Gotoxy(x, y + 2);
			wcout << L"█▄▄" << endl;
			break;
		case 3:
			SetModeConsole(false);
			Gotoxy(x, y);
			wcout << L"▄▄▄" << endl;
			Gotoxy(x, y + 1);
			wcout << L"▄▄█" << endl;
			Gotoxy(x, y + 2);
			wcout << L"▄▄█" << endl;
			break;
		case 4:
			SetModeConsole(false);
			Gotoxy(x, y);
			wcout << L"▄ ▄" << endl;
			Gotoxy(x, y + 1);
			wcout << L"█▄█" << endl;
			Gotoxy(x, y + 2);
			wcout << L"  █" << endl;
			break;
		case 5:
			SetModeConsole(false);
			Gotoxy(x, y);
			wcout << L"▄▄▄" << endl;
			Gotoxy(x, y + 1);
			wcout << L"█▄▄" << endl;
			Gotoxy(x, y + 2);
			wcout << L"▄▄█" << endl;
			break;
		case 6:
			SetModeConsole(false);
			Gotoxy(x, y);
			wcout << L"▄▄▄" << endl;
			Gotoxy(x, y + 1);
			wcout << L"█▄▄" << endl;
			Gotoxy(x, y + 2);
			wcout << L"█▄█" << endl;
			break;
		case 7:
			SetModeConsole(false);
			Gotoxy(x, y);
			wcout << L"▄▄▄" << endl;
			Gotoxy(x, y + 1);
			wcout << L"▀ █" << endl;
			Gotoxy(x, y + 2);
			wcout << L"  █" << endl;
			break;
		case 8:
			SetModeConsole(false);
			Gotoxy(x, y);
			wcout << L"▄▄▄" << endl;
			Gotoxy(x, y + 1);
			wcout << L"█▄█" << endl;
			Gotoxy(x, y + 2);
			wcout << L"█▄█" << endl;
			break;
		case 9:
			SetModeConsole(false);
			Gotoxy(x, y);
			wcout << L"▄▄▄" << endl;
			Gotoxy(x, y + 1);
			wcout << L"█▄█" << endl;
			Gotoxy(x, y + 2);
			wcout << L"▄▄█" << endl;
			break;
		case 0:
			SetModeConsole(false);
			Gotoxy(x, y);
			wcout << L"▄▄▄" << endl;
			Gotoxy(x, y + 1);
			wcout << L"█ █" << endl;
			Gotoxy(x, y + 2);
			wcout << L"█▄█" << endl;
			break;
		}
	}
}

void CalcNum() {
	SetModeConsole(true);
	sWallet[0] = wallet / 10000; // 12345 / 10000
	sWallet[1] = wallet % 10000 / 1000; // 0 ~ 9999 / 1000 => 0 ~ 9 (int이므로 알아서 버려지니께)
	sWallet[2] = wallet % 1000 / 100;
	sWallet[3] = wallet % 100 / 10;
	sWallet[4] = wallet % 10; //0~9
}

void Mine()
{
	int _core = 0;
	while (true)
	{
		system("cls");
		SetModeConsole(true);
		cout << "<아무키 입력시 돌을 캡니다. (종료 esc)>" << endl << endl;
		cout << "곡괭이 내구도 : " << pickAxe << " / " << maxPickAxe << endl;
		int inpKey = _getch();
		_core = Rand();
		if (inpKey == 27) //종료 조건 처리
			break;
		pickAxe--;
		int x = 0, y = 0;
		SetModeConsole(false);
		for (int r = 0; r < _core * brokeCnt; r++) { // 숫자는 광석에 따라 캐지는 횟수
			system("cls");
			//player
			if (r % 2 == 1) {
				wcout << L"        ▄▄▄▄▄▄▄▄" << endl;
				wcout << L"       █▀ ▄  ▄ ▀█" << endl;
				wcout << L"       █  █▀▀█  █" << endl;
				wcout << L"  ▄▄▄  █▀▀▀▀▀▀▀▀█" << endl;
				wcout << L" ▀ █ ▀ █ ▀ ▄▄ ▀ █" << endl;
				wcout << L"   █▀▄ ▀▄▄▄▄▄▄▄▄▀" << endl;
				wcout << L"   █  ▀▀█      █▀▄" << endl;
				wcout << L"        █▄▄▄▄▄▄█  ▀" << endl;
				wcout << L"         █ █ █ █" << endl;
				wcout << L"         ▀▀▀ ▀▀▀" << endl;
			}
			else
			{
				wcout << L"        ▄▄▄▄▄▄▄▄	" << endl;
				wcout << L"       █▀ ▄  ▄ ▀█  " << endl;
				wcout << L"       █  █▀▀█  █  " << endl;
				wcout << L"  ▄▄   █▀▀▀▀▀▀▀▀█  " << endl;
				wcout << L"▄█     █ ▀ ▄▄ ▀ █  " << endl;
				wcout << L"█ ▀█▀▄ ▀▄▄▄▄▄▄▄▄▀  " << endl;
				wcout << L"   ▀█ ▀▀█      █▀▄ " << endl;
				wcout << L"     ▀  █▄▄▄▄▄▄█  ▀" << endl;
				wcout << L"         █ █ █ █   " << endl;
				wcout << L"         ▀▀▀ ▀▀▀   " << endl;
			}

			x = 50;
			y = 0;
			//dril
			if (isUpgrade[0]) 
			{
				if (r % 3 == 0)
			{
				Gotoxy(x, y);
				wcout << L"          ▄▄ ▄█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█ " << endl;
				Gotoxy(x, y + 1);
				wcout << L"      ▄▄█▀██▀▀                █ " << endl;
				Gotoxy(x, y + 2);
				wcout << L"  ▄▄█▀█ ▀▄ █                  █ " << endl;
				Gotoxy(x, y + 3);
				wcout << L" ██ ▀▄ █ █ █                  █ " << endl;
				Gotoxy(x, y + 4);
				wcout << L"   ▀▀█▄█ █ █▀▀▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█ " << endl;
				Gotoxy(x, y + 5);
				wcout << L"        ▀▀██ █ ▄▀▄ ▄▀▄ ▄▀▄ ▄▀▄ █" << endl;
				Gotoxy(x, y + 6);
				wcout << L"             ▀▄▄█▄▄▄█▄▄▄█▄▄▄█▄▄█" << endl;
			}
				else if (r % 3 == 1)
			{
				Gotoxy(x, y);
				wcout << L"          ▄▄ ▄█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█ " << endl;
				Gotoxy(x, y + 1);
				wcout << L"      ▄▄█▀██▀▀                █ " << endl;
				Gotoxy(x, y + 2);
				wcout << L"  ▄▄█▀█ █ ██                  █ " << endl;
				Gotoxy(x, y + 3);
				wcout << L" ██ █ █ ▀▄ █                  █ " << endl;
				Gotoxy(x, y + 4);
				wcout << L"   ▀▀█▄█ █ █▀▀▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█ " << endl;
				Gotoxy(x, y + 5);
				wcout << L"        ▀▀██ █ ▄▀▄ ▄▀▄ ▄▀▄ ▄▀▄ █" << endl;
				Gotoxy(x, y + 6);
				wcout << L"             ▀▄▄█▄▄▄█▄▄▄█▄▄▄█▄▄█" << endl;
			}
				else if (r % 3 == 2) {
				Gotoxy(x, y);
				wcout << L"          ▄▄ ▄█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█ " << endl;
				Gotoxy(x, y + 1);
				wcout << L"      ▄▄█▀██▀▀                █ " << endl;
				Gotoxy(x, y + 2);
				wcout << L"  ▄▄█▀█ █ ██                  █ " << endl;
				Gotoxy(x, y + 3);
				wcout << L" ██ █ █ █ ██                  █ " << endl;
				Gotoxy(x, y + 4);
				wcout << L"   ▀▀██▄▀▄ █▀▀▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█ " << endl;
				Gotoxy(x, y + 5);
				wcout << L"        ▀▀██ █ ▄▀▄ ▄▀▄ ▄▀▄ ▄▀▄ █" << endl;
				Gotoxy(x, y + 6);
				wcout << L"             ▀▄▄█▄▄▄█▄▄▄█▄▄▄█▄▄█" << endl;
			}
			}

			y = 11;
			//porkcrane
			if (isUpgrade[1]) 
			{
				if (r % 2 == 0)
			{
				Gotoxy(50, y);
				wcout << L"  ▄▄▄▄▄                " << endl;
				Gotoxy(50, y + 1);
				wcout << L" █▀   ▀█▄              " << endl;
				Gotoxy(50, y + 2);
				wcout << L" █      ▀█▄            " << endl;
				Gotoxy(50, y + 3);
				wcout << L"▄█        ▀█▄▄▄▄▄▄▄    " << endl;
				Gotoxy(50, y + 4);
				wcout << L"█          █      █    " << endl;
				Gotoxy(50, y + 5);
				wcout << L"█          █      ▀▀▀▀█" << endl;
				Gotoxy(50, y + 6);
				wcout << L"█▄▄▄▄▄     █          █" << endl;
				Gotoxy(50, y + 7);
				wcout << L"█▄   █     █▄▄▄▄▄▄▄▄▄▄▀" << endl;
				Gotoxy(50, y + 8);
				wcout << L" ▀▀▀▀▀     ▄▀        ▀▄" << endl;
				Gotoxy(50, y + 9);
				wcout << L"           ▀█▄▄▄▄▄▄▄▄▄█" << endl;
			}
				else if (r % 2 == 1)
			{
				Gotoxy(50, y);
				wcout << L"  ▄▄▄▄▄                " << endl;
				Gotoxy(50, y + 1);
				wcout << L" █▀   ▀█▄              " << endl;
				Gotoxy(50, y + 2);
				wcout << L" █      ▀█▄            " << endl;
				Gotoxy(50, y + 3);
				wcout << L" █        ▀█▄▄▄▄▄▄▄    " << endl;
				Gotoxy(50, y + 4);
				wcout << L" █▄        █      █    " << endl;
				Gotoxy(50, y + 5);
				wcout << L"  █   ▄▄▄  █      ▀▀▀▀█" << endl;
				Gotoxy(50, y + 6);
				wcout << L"  ▀█▄█▀ █  █          █" << endl;
				Gotoxy(50, y + 7);
				wcout << L"   ▀█  ▄█  █▄▄▄▄▄▄▄▄▄▄▀" << endl;
				Gotoxy(50, y + 8);
				wcout << L"    ▀▀▀▀   ▄▀        ▀▄" << endl;
				Gotoxy(50, y + 9);
				wcout << L"           ▀█▄▄▄▄▄▄▄▄▄█" << endl;
			}
			}

			//detector
			y = 11;
			x = 0;
			if (isUpgrade[2])
			{
				if (r % 4 == 3) {
				Gotoxy(x, y);
				wcout << L"                 ▀▀▀▄▄▄▄▄▄      " << endl;
				Gotoxy(x, y + 1);
				wcout << L"                         ▀█▄    " << endl;
				Gotoxy(x, y + 2);
				wcout << L"                ▀▀▀▀▀▄▄▄   ▀█   " << endl;
				Gotoxy(x, y + 3);
				wcout << L"                       ▀█    █  " << endl;
				Gotoxy(x, y + 4);
				wcout << L"                ▀▀█▄▄   ▀█   █  " << endl;
				Gotoxy(x, y + 5);
				wcout << L"                    ▀█▄  █▄   █ " << endl;
				Gotoxy(x, y + 6);
				wcout << L"         ▄█▀▀▀█   ▄█  █   ▀     " << endl;
				Gotoxy(x, y + 7);
				wcout << L"        █▀     ▀▄█▀             " << endl;
				Gotoxy(x, y + 8);
				wcout << L"        █▄    ▄█▀█▄             " << endl;
				Gotoxy(x, y + 9);
				wcout << L"        ██   ▀▀   ▀█            " << endl;
				Gotoxy(x, y + 10);
				wcout << L"      ▄▀▀▀█▄       █            " << endl;
				Gotoxy(x, y + 11);
				wcout << L"    ▄▀     ▀▀█▄▄▄▄█▀            " << endl;
				Gotoxy(x, y + 12);
				wcout << L"    █▀▀▀▀▀▀▀█▄                  " << endl;
				Gotoxy(x, y + 13);
				wcout << L"    █        ▀██▀▀▀▀█           " << endl;
				Gotoxy(x, y + 14);
				wcout << L"    █          ▀█▄  █           " << endl;
				Gotoxy(x, y + 15);
				wcout << L"    █▄▄▄▄▄▄▄▄▄▄▄▄█▄▄█           " << endl;
			}
				else if (r % 4 == 2)
			{
				Gotoxy(x, y);
				wcout << L"                                " << endl;
				Gotoxy(x, y + 1);
				wcout << L"                                " << endl;
				Gotoxy(x, y + 2);
				wcout << L"                ▀▀▀▀▀▄▄▄        " << endl;
				Gotoxy(x, y + 3);
				wcout << L"                       ▀█       " << endl;
				Gotoxy(x, y + 4);
				wcout << L"                ▀▀█▄▄   ▀█      " << endl;
				Gotoxy(x, y + 5);
				wcout << L"                    ▀█▄  █▄     " << endl;
				Gotoxy(x, y + 6);
				wcout << L"         ▄█▀▀▀█   ▄█  █   ▀     " << endl;
				Gotoxy(x, y + 7);
				wcout << L"        █▀     ▀▄█▀             " << endl;
				Gotoxy(x, y + 8);
				wcout << L"        █▄    ▄█▀█▄             " << endl;
				Gotoxy(x, y + 9);
				wcout << L"        ██   ▀▀   ▀█            " << endl;
				Gotoxy(x, y + 10);
				wcout << L"      ▄▀▀▀█▄       █            " << endl;
				Gotoxy(x, y + 11);
				wcout << L"    ▄▀     ▀▀█▄▄▄▄█▀            " << endl;
				Gotoxy(x, y + 12);
				wcout << L"    █▀▀▀▀▀▀▀█▄                  " << endl;
				Gotoxy(x, y + 13);
				wcout << L"    █        ▀██▀▀▀▀█           " << endl;
				Gotoxy(x, y + 14);
				wcout << L"    █          ▀█▄  █           " << endl;
				Gotoxy(x, y + 15);
				wcout << L"    █▄▄▄▄▄▄▄▄▄▄▄▄█▄▄█           " << endl;
			}
				else if (r % 4 == 1)
			{
				Gotoxy(x, y);
				wcout << L"                                " << endl;
				Gotoxy(x, y + 1);
				wcout << L"                                " << endl;
				Gotoxy(x, y + 2);
				wcout << L"                                " << endl;
				Gotoxy(x, y + 3);
				wcout << L"                                " << endl;
				Gotoxy(x, y + 4);
				wcout << L"                ▀▀█▄▄           " << endl;
				Gotoxy(x, y + 5);
				wcout << L"                    ▀█▄         " << endl;
				Gotoxy(x, y + 6);
				wcout << L"         ▄█▀▀▀█   ▄█  █         " << endl;
				Gotoxy(x, y + 7);
				wcout << L"        █▀     ▀▄█▀             " << endl;
				Gotoxy(x, y + 8);
				wcout << L"        █▄    ▄█▀█▄             " << endl;
				Gotoxy(x, y + 9);
				wcout << L"        ██   ▀▀   ▀█            " << endl;
				Gotoxy(x, y + 10);
				wcout << L"      ▄▀▀▀█▄       █            " << endl;
				Gotoxy(x, y + 11);
				wcout << L"    ▄▀     ▀▀█▄▄▄▄█▀            " << endl;
				Gotoxy(x, y + 12);
				wcout << L"    █▀▀▀▀▀▀▀█▄                  " << endl;
				Gotoxy(x, y + 13);
				wcout << L"    █        ▀██▀▀▀▀█           " << endl;
				Gotoxy(x, y + 14);
				wcout << L"    █          ▀█▄  █           " << endl;
				Gotoxy(x, y + 15);
				wcout << L"    █▄▄▄▄▄▄▄▄▄▄▄▄█▄▄█           " << endl;
			}
				else if (r % 4 == 0)
			{
				Gotoxy(x, y);
				wcout << L"                                " << endl;
				Gotoxy(x, y + 1);
				wcout << L"                                " << endl;
				Gotoxy(x, y + 2);
				wcout << L"                                " << endl;
				Gotoxy(x, y + 3);
				wcout << L"                                " << endl;
				Gotoxy(x, y + 4);
				wcout << L"                                " << endl;
				Gotoxy(x, y + 5);
				wcout << L"                                " << endl;
				Gotoxy(x, y + 6);
				wcout << L"         ▄█▀▀▀█   ▄█            " << endl;
				Gotoxy(x, y + 7);
				wcout << L"        █▀     ▀▄█▀             " << endl;
				Gotoxy(x, y + 8);
				wcout << L"        █▄    ▄█▀█▄             " << endl;
				Gotoxy(x, y + 9);
				wcout << L"        ██   ▀▀   ▀█            " << endl;
				Gotoxy(x, y + 10);
				wcout << L"      ▄▀▀▀█▄       █            " << endl;
				Gotoxy(x, y + 11);
				wcout << L"    ▄▀     ▀▀█▄▄▄▄█▀            " << endl;
				Gotoxy(x, y + 12);
				wcout << L"    █▀▀▀▀▀▀▀█▄                  " << endl;
				Gotoxy(x, y + 13);
				wcout << L"    █        ▀██▀▀▀▀█           " << endl;
				Gotoxy(x, y + 14);
				wcout << L"    █          ▀█▄  █           " << endl;
				Gotoxy(x, y + 15);
				wcout << L"    █▄▄▄▄▄▄▄▄▄▄▄▄█▄▄█           " << endl;
			}
			}

			Sleep(100);
		}

		SetModeConsole(true);
		if (_core == core[4]) 
		{
			cout << "★★★★★축하합니다!! 다이아몬드를 캤어요★★★★★" << endl;
			++coreBag[4];
		}
		else if (_core == core[3])
		{
			cout << "축하합니다!! 금을 캤어요" << endl;
			++coreBag[3];
		}
		else if (_core == core[2]) 
		{
			cout << "철을 캤어요" << endl;
			++coreBag[2];
		}
		else if (_core == core[1])
		{
			cout << "구리를 캤다." << endl;
			++coreBag[1];
		}
		else if (_core == core[0]) {
			cout << "석탄을 캤다." << endl;
			++coreBag[0];
		}
		else{
			cout << "아무것도 안나왔다." << endl;
		}
		Sleep(1000);
	}
}

int Rand() {
	float corePercent = rand() % 10001 / 10.f;
	if (corePercent <= percent[4]) {
		return core[4];
	}
	else if (corePercent <= percent[3]) {
		return core[3];
	}
	else if (corePercent <= percent[2]) {
		return core[2];
	}
	else if (corePercent <= percent[1]) {
		return core[1];
	}
	else if (corePercent <= percent[0]) {
		return core[0];
	}
	else if (corePercent <= percent[5]) {
		return 1;
	}
	else
		return -1;
}

void Bag()
{
	system("cls");
	SetModeConsole(true);
	cout << "         ___" << endl;
	cout << "        |   |" << endl;
	cout << "+ㅡㅡㅡㅡㅡㅡㅡㅡㅡ+" << endl;
	cout << "|                  |" << endl;
	cout << "|                  |" << endl;
	for (int i = 0; i < 5; i++) {
		cout << "|  " << coreBagName[i] << " : " << coreBag[i] << "  |" << endl;
	}
	cout << "|                  |" << endl;
	cout << "|                  |" << endl;
	cout << "+ㅡㅡㅡㅡㅡㅡㅡㅡㅡ+" << endl;
	cout << "아무키 입력시 나가집니다.";
	
	SetModeConsole(false);
	_getch();
}

void Store()
{
	system("cls");
	SetModeConsole(false);


	wcout << L"  ██╗ ██╗███████╗████████╗ ██████╗ ██████╗ ███████╗██╗ ██╗	   " << endl;
	wcout << L" ██╔╝██╔╝██╔════╝╚══██╔══╝██╔═══██╗██╔══██╗██╔════╝╚██╗╚██╗  " << endl;
	wcout << L"██╔╝██╔╝ ███████╗   ██║   ██║   ██║██████╔╝█████╗   ╚██╗╚██╗" << endl;
	wcout << L"╚██╗╚██╗ ╚════██║   ██║   ██║   ██║██╔══██╗██╔══╝   ██╔╝██╔╝" << endl;
	wcout << L" ╚██╗╚██╗███████║   ██║   ╚██████╔╝██║  ██║███████╗██╔╝██╔╝  " << endl;
	wcout << L"  ╚═╝ ╚═╝╚══════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝ ╚═╝	   " << endl;
	Coin();

	wcout << endl << endl << endl;
	wcout << L"█▀▀▀▀▀▀▀▀▀▀▀▀▀▀█               █▀▀▀▀▀▀▀▀▀▀▀▀▀▀█               █▀▀▀▀▀▀▀▀▀▀▀▀▀▀█" << endl;
	wcout << L"█    곡괭이    █               █    내구도    █               █  업그레이드  █"  << endl;
	wcout << L"█▄▄▄▄▄▄▄▄▄▄▄▄▄▄█               █▄▄▄▄▄▄▄▄▄▄▄▄▄▄█               █▄▄▄▄▄▄▄▄▄▄▄▄▄▄█" << endl; 

	SetModeConsole(true);
	cout << endl << endl << "업그레이드 할 항목을 고르세요 (1 ~ 3 / 종료는 esc) : ";
	int inp = _getch();
	int price = 0;

	switch (inp) {
	case 49: //1이 눌렸을 때
		if (maxPickAxe < 300)
		{
			int upgradePrice = 700 - (300 - maxPickAxe);
			cout << endl;
			cout << "현재 최대 내구도 : " << maxPickAxe << endl;
			cout << "강화에 드는 비용 : " << upgradePrice << endl;
			float f = (300 - maxPickAxe) * 0.4; // (최대 내구도 - 현재 최대 내구도) * 0.4 => 300 - 100 = 200 * 0.4 = 80
			cout << "강화 확률 : " << f << endl;
			float r = rand() % 10001 / 100.f;
			cout << "강화를 하시겠습니까? (y/n) : ";
			inp = _getch();
			switch (inp) 
			{
			case 121:
				if (wallet >= upgradePrice) 
				{
					if (r <= f) 
					{
						cout << "<< " << f << " >>에 확률을 뚫고 강화에 성공했다!!!" << endl;
						maxPickAxe += 50;
					}
					else
					{
						cout << "강화 실패...!! 정말 아쉽네요.." << endl;
					}
				}
				else {
					cout << "강화를 하기 위해서는 " << upgradePrice - wallet << "원이 부족합니다." << endl;
					Sleep(2000);
				}
				break;
			case 110:
				cout << endl << "그래 강화가 리스크가 크긴해. 너같은 허접이 넘볼수도 없지. ㅋ*ㅋ";
				break;
			default:
				cout << "잘'못된' 키를 입력하였습니다. 넌 '못된'아이구나";
				Sleep(1000);
				Store();
				break;
			}
			Sleep(1000);
		}
		else
		{
			cout << endl << "최대 강화입니다. 더 강화를 원한다면 다빈이를 갈구세요" << endl;
			Sleep(1000);
		}
		break;
	case 50: //2가 눌렸을 때
		#pragma region 내구도
		price = (maxPickAxe - pickAxe) * 10;
		cout << endl << "현재 내구도 : " << pickAxe << endl;
		cout << "내구도 회복에 필요한 돈 : " << price << endl;
		cout << "내구도를 회복하시겠습니까? (y / n) : ";
		inp = _getch();
		switch (inp) {
		case 121:
			if (wallet >= price)
			{
				wallet -= price;
				pickAxe = maxPickAxe;
				cout << "<< " << price << " >> 원을 소비하여 내구도를 회복하였습니다." << endl;
			}
			else
			{
				cout << price << "원도 없는 아이구나? 더 벌어와 ^^" << endl;
			}
			Sleep(1000);

			break;
		case 110:
			cout << "다른것도 구경해봐~~" << endl;
			Sleep(1000);
			break;
		default:
			cout << "잘'못된' 키를 입력하였습니다. 넌 '못된'아이구나";
			Sleep(1000);
			Store();
			break;
		}
		break;
#pragma endregion
	case 51: //3이 눌렸을 때
		Upgrade();
		break;
	case 27: //esc가 눌렸을 때
		return;
		break;
	default: //잘못 입력
		cout << "<<잘못된 수를 입력하셨습니다. 1~3까지 또는 esc키만 입력해주세요>>";
		Sleep(1000);
		Store();
		break;
	}
}

int iDril = 0;
int iPork = 0;
int iDetect = 0;

void Upgrade()
{
	system("cls");
	//드릴 (캐는 속도 업그레이드)
	#pragma region 보기_싫어서_묶을거임
	SetModeConsole(false);
	int y = 0;
	wcout << L"          ▄▄ ▄█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█ " << endl;
	wcout << L"      ▄▄█▀██▀▀                █ " << endl;
	wcout << L"  ▄▄█▀█ █ ██                  █ " << endl;
	wcout << L" ██ █ █ ▀▄ █                  █ " << endl;
	wcout << L"   ▀▀█▄█ █ █▀▀▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█ " << endl;
	wcout << L"        ▀▀██ █ ▄▀▄ ▄▀▄ ▄▀▄ ▄▀▄ █" << endl;
	wcout << L"             ▀▄▄█▄▄▄█▄▄▄█▄▄▄█▄▄█" << endl;
	#pragma endregion 
	SetModeConsole(true);
	if (iDril < 5) 
	{
		cout << "현재 드릴 레벨 : " << iDril << endl;
		cout << "업그레이드시 캐는 속도가 증가한다!!" << endl;
	}
	else
	{
		cout << "현재 드릴 레벨 : MAX_LEVEL" << endl;
	}

	//포크레인(자동 사냥)
	#pragma region 보기_싫어서_묶을거임2
	SetModeConsole(false);
	Gotoxy(50, y);
	wcout << L"  ▄▄▄▄▄                " << endl;
	Gotoxy(50, y + 1);
	wcout << L" █▀   ▀█▄              " << endl;
	Gotoxy(50, y + 2);
	wcout << L" █      ▀█▄            " << endl;
	Gotoxy(50, y + 3);
	wcout << L"▄█        ▀█▄▄▄▄▄▄▄    " << endl;
	Gotoxy(50, y + 4);
	wcout << L"█          █      █    " << endl;
	Gotoxy(50, y + 5);
	wcout << L"█          █      ▀▀▀▀█" << endl;
	Gotoxy(50, y + 6);
	wcout << L"█▄▄▄▄▄     █          █" << endl;
	Gotoxy(50, y + 7);
	wcout << L"█▄   █     █▄▄▄▄▄▄▄▄▄▄▀" << endl;
	Gotoxy(50, y + 8);
	wcout << L" ▀▀▀▀▀     ▄▀        ▀▄" << endl;
	Gotoxy(50, y + 9);
	wcout << L"           ▀█▄▄▄▄▄▄▄▄▄█" << endl;
#pragma endregion 
	SetModeConsole(true);
	if (iPork < 5)
	{
		Gotoxy(50, y + 10);
		cout << "현재 포크레인 레벨 : " << iPork << endl;
		Gotoxy(50, y + 11);
		cout << "업그레이드시 광질을 하지 않아도 돈이 증가한다!!" << endl;
	}
	else
	{
		Gotoxy(50, y + 10);
		cout << "현재 포크레인 레벨 : MAX_LEVEL" << endl;
	}
	
	//탐지기 (확률 업그레이드)
	Gotoxy(0, y + 9);
	#pragma region 보기_싫어서_묶을거임3
	SetModeConsole(false);
	wcout << L"                 ▀▀▀▄▄▄▄▄▄      " << endl;
	wcout << L"                         ▀█▄    " << endl;
	wcout << L"                ▀▀▀▀▀▄▄▄   ▀█   " << endl;
	wcout << L"                       ▀█    █  " << endl;
	wcout << L"                ▀▀█▄▄   ▀█   █  " << endl;
	wcout << L"                    ▀█▄  █▄   █ " << endl;
	wcout << L"         ▄█▀▀▀█   ▄█  █   ▀     " << endl;
	wcout << L"        █▀     ▀▄█▀             " << endl;
	wcout << L"        █▄    ▄█▀█▄             " << endl;
	wcout << L"        ██   ▀▀   ▀█            " << endl;
	wcout << L"      ▄▀▀▀█▄       █            " << endl;
	wcout << L"    ▄▀     ▀▀█▄▄▄▄█▀            " << endl;
	wcout << L"    █▀▀▀▀▀▀▀█▄                  " << endl;
	wcout << L"    █        ▀██▀▀▀▀█           " << endl;
	wcout << L"    █          ▀█▄  █           " << endl;
	wcout << L"    █▄▄▄▄▄▄▄▄▄▄▄▄█▄▄█           " << endl;
	#pragma endregion
	SetModeConsole(true);
	if (iDetect < 5)
	{
		cout << "현재 탐지기 레벨 : " << iDetect << endl;
		cout << "업그레이드시 광물을 캘 때 더 높은 자원이 나온다!!" << endl;
	}
	else
	{
		cout << "현재 탐지기 레벨 : MAX_LEVEL" << endl;
	}

	cout << "업그레이드할 항목에 번호를 입력해주세요. (1. 드릴 2. 포크레인 3. 탐지기)";
	int inpNum = 0, maxPrice = 1000;
	cin >> inpNum;

	system("cls");
	SetModeConsole(false);
	switch (inpNum)
	{
	case 1:
		wcout << L"          ▄▄ ▄█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█ " << endl;
		wcout << L"      ▄▄█▀██▀▀                █ " << endl;
		wcout << L"  ▄▄█▀█ ▀▄ █                  █ " << endl;
		wcout << L" ██ ▀▄ █ █ █                  █ " << endl;
		wcout << L"   ▀▀█▄█ █ █▀▀▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█ " << endl;
		wcout << L"        ▀▀██ █ ▄▀▄ ▄▀▄ ▄▀▄ ▄▀▄ █" << endl;
		wcout << L"             ▀▄▄█▄▄▄█▄▄▄█▄▄▄█▄▄█" << endl;
		if (iDril != 5)
		{
			int price = maxPrice - (5 - iDril) * 100;
			SetModeConsole(true);
			cout << "드릴 업그레이드 : " << price << "원";
			cout << "업그레이드를 하시겠습니까 (y/n) : ";
			int inp = _getch();

			switch (inp)
			{
			case 121:
				isUpgrade[0] = true;
				if (wallet >= price)
				{
					iDril++;
					brokeCnt--;
					cout << "<< " << price << "원을 사용하여 강화하였습니다. >>" << endl;
				}
				else 
				{
					cout << price - wallet << "원이 부족합니다.";;
				}
				break;
			case 110:
				cout << "강화를 취소하였습니다.";
				Sleep(1000);
				break;
			default:
				cout << "잘못 입력하셨습니다.";
				Sleep(1000);
				break;
			}

		}
		else
		{
			cout << "이미 최대레벨 입니다.";
		}
		Sleep(2000);
		break;
	case 2:
		wcout << L"  ▄▄▄▄▄                " << endl;
		wcout << L" █▀   ▀█▄              " << endl;
		wcout << L" █      ▀█▄            " << endl;
		wcout << L"▄█        ▀█▄▄▄▄▄▄▄    " << endl;
		wcout << L"█          █      █    " << endl;
		wcout << L"█          █      ▀▀▀▀█" << endl;
		wcout << L"█▄▄▄▄▄     █          █" << endl;
		wcout << L"█▄   █     █▄▄▄▄▄▄▄▄▄▄▀" << endl;
		wcout << L" ▀▀▀▀▀     ▄▀        ▀▄" << endl;
		wcout << L"           ▀█▄▄▄▄▄▄▄▄▄█" << endl;

		if (iPork != 5)
		{
			int price = maxPrice - (5 - iPork) * 100;
			SetModeConsole(true);
			cout << "포크레인 업그레이드 : " << price << "원";
			cout << "업그레이드를 하시겠습니까 (y/n) : ";
			int inp = _getch();

			switch (inp)
			{
			case 121:
				isUpgrade[1] = true;
				if (wallet >= price)
				{
					iPork++;
					//시간당 버는 돈 증가
					secPrice += 10;
					cout << "<< " << price << "원을 사용하여 강화하였습니다. >>" << endl;
				}
				else
				{
					cout << price - wallet << "원이 부족합니다.";;
				}
				break;
			case 110:
				cout << "강화를 취소하였습니다.";
				Sleep(1000);
				break;
			default:
				cout << "잘못 입력하셨습니다.";
				Sleep(1000);
				break;
			}

		}
		else
		{
			cout << "이미 최대레벨 입니다.";
		}
		Sleep(2000);
		break;
	case 3:
		wcout << L"         ▄█▀▀▀█   ▄█            " << endl;
		wcout << L"        █▀     ▀▄█▀             " << endl;
		wcout << L"        █▄    ▄█▀█▄             " << endl;
		wcout << L"        ██   ▀▀   ▀█            " << endl;
		wcout << L"      ▄▀▀▀█▄       █            " << endl;
		wcout << L"    ▄▀     ▀▀█▄▄▄▄█▀            " << endl;
		wcout << L"    █▀▀▀▀▀▀▀█▄                  " << endl;
		wcout << L"    █        ▀██▀▀▀▀█           " << endl;
		wcout << L"    █          ▀█▄  █           " << endl;
		wcout << L"    █▄▄▄▄▄▄▄▄▄▄▄▄█▄▄█           " << endl;
		if (iDetect != 5)
		{
			int price = maxPrice - (5 - iDetect) * 100;
			SetModeConsole(true);
			cout << "탐지기 업그레이드 : " << price << "원";
			cout << "업그레이드를 하시겠습니까 (y/n) : ";
			int inp = _getch();

			switch (inp)
			{
			case 121:
				isUpgrade[2] = true;
				if (wallet >= price)
				{
					iDetect++;
					//float percent[CoreNum] = { 500, 200, 100, 50, 1 , 149}; 15% 50% 20% 10% 5% 0.1% => 10% 10% 20% 30% 20% 10% 
					//확률 업그레이드 훔.. 낮은건 감소 큰건 증가? 아니면 큰것만 증가? 뭐하지 훔.. 
					//일단은 만렙시 다이아확률 10(1%)을 하고 싶은데
					//그리고 만렙시 안나오는 확률을 10%를 하고 싶다.. 훔..
					percent[5] -= 10;
					percent[0] -= 80;
					percent[2] += 4;
					percent[3] += 3;
					percent[4] += 2;
					cout << "<< " << price << "원을 사용하여 강화하였습니다. >>" << endl;
				}
				else
				{
					cout << price - wallet << "원이 부족합니다.";;
				}
				break;
			case 110:
				cout << "강화를 취소하였습니다.";
				Sleep(1000);
				break;
			default:
				cout << "잘못 입력하셨습니다.";
				Sleep(1000);
				break;
			}
		}
		else
		{
			cout << "이미 최대레벨 입니다.";
		}
		Sleep(2000);
		break;
	default:
		SetModeConsole(true);
		string error = "에러 에러 에러 에러 삐용 삐용 삐용 삐용 !!!!!!!!!";
		for (int i = 0; i < error.size(); i++)
		{
			if (i % 3 == 2)
			{
				Sleep(200);
			}
			cout << error[i];
		}
		cout << "\n 다시 입력해주세요." << endl;
		Sleep(1000);
		Upgrade();
		break;
	}
}

void Change() {
	system("cls");
	SetModeConsole(false);

	for (int i = 0; i < CoreNum; i++)
	{
		corePrice[i] = corePrice[i] + rand() % 21 - 10; //현재 가격에서 +- 10원 사이로 환률이 변동
		if(i != 0)
			corePrice[i] = clamp(corePrice[i], corePrice[i - 1], 9999); // 전 가격보다 밑으로 가지는 않게
		else
			corePrice[i] = clamp(corePrice[i], 1, 9999); // 운이 안좋게 1원 밑으로 떨어지지 않도록 한다.
	}

	wcout << L"█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█" << endl;
	wcout << L"█         <<현재 시세>>         █" << endl;
	wcout << L"█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█" << endl;
	wcout << L"█   █   █   █   █   █   █   █   █" << endl;
	wcout << L"█   █   █   █   █   █   █   █   █" << endl;
	wcout << L"█▀▄▀ ▀▄▀ ▀▄▀ ▀▄▀ ▀▄▀ ▀▄▀ ▀▄▀ ▀▄▀█" << endl;
	wcout << L"█ █                           █ █" << endl;
	for (int i = 0; i < CoreNum; i++)
	{
		wcout << L"█ █ ";
		SetModeConsole(true);
		cout << "<< " << i + 1 << "." << coreBagName[i] << " : ";
		cout.width(4); 
		cout.fill('0'); //00XX이런식으로 출력 하도록
		cout << corePrice[i];
		SetModeConsole(false);
		wcout << L" >> █ █" << endl;
	}
	wcout << L"█ █                           █ █" << endl;
	wcout << L"█ █▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█ █" << endl;
	wcout << L"█ █                           █ █" << endl;
	wcout << L"█ ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀ █" << endl;
	wcout << L"█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█" << endl;

	int x = 50;
	int y = 5;

	Gotoxy(x - 12, y);
	wcout << L"▄▀▀▀▀▀▀▀▀▀▄" << endl;
	Gotoxy(x - 12, y + 1);
	int r = rand() % 3;
	switch (r) {
	case 0:
		wcout << L"█  안녕?! █" << endl;
		break;
	case 1:
		wcout << L"█ 싸다~!! █" << endl;
		break;
	case 2:
		wcout << L"█  사줘!! █" << endl;
		break;
	}
	Gotoxy(x - 12, y + 2);
	wcout << L"█         █" << endl;
	Gotoxy(x - 12, y + 3);
	wcout << L" ▀▀▀▀▀▀▀█ █" << endl;
	Gotoxy(x - 12, y + 4);
	wcout << L"         ▀ " << endl;

	Gotoxy(x, y);
	wcout << L"    ▄▀▀▀▀▀▀▀▀▀▄  " << endl;
	Gotoxy(x, y + 1);
	wcout << L"    █ █▀▄ ▄▀█ █  " << endl;
	Gotoxy(x, y + 2);
	wcout << L"    █ ▀  ▀  ▀ █  " << endl;
	Gotoxy(x, y + 3);
	wcout << L" ▀▀▀█▀▀▀▀▀▀▀▀▀█  " << endl;
	Gotoxy(x, y + 4);
	wcout << L"    █ █     █ █  " << endl;
	Gotoxy(x, y + 5);
	wcout << L"▄▄  █▄  ▀▀▀  ▄█  " << endl;
	Gotoxy(x, y + 6);
	wcout << L"  ▀▄▄█▀▀▀▀▀▀▀█▄  " << endl;
	Gotoxy(x, y + 7);
	wcout << L"     █       █ ▀▄" << endl;
	Gotoxy(x, y + 8);
	wcout << L"     █▀▀▀▀▀▀▀█  ▀" << endl;
	Gotoxy(x, y + 9);
	wcout << L"     ▀▄▄▄▄▄▄▄▀   " << endl;
	Gotoxy(x, y + 10);
	wcout << L"      █ █ █ █    " << endl;
	Gotoxy(x, y + 11);
	wcout << L"      ▀▀▀ ▀▀▀    " << endl;

	SetModeConsole(true);
	cout << endl << "환전 하고 싶은 항목에 번호를 고르시오 (가방을 볼려면 0 / 나가려면 9) : ";
	int inp = _getch();
	switch (inp) {
	case 48:
		Bag();
		break;
	case 49:
		ChangeLogic(0);
		break;
	case 50:
		ChangeLogic(1);
		break;
	case 51:
		ChangeLogic(2);
		break;
	case 52:
		ChangeLogic(3);
		break;
	case 53:
		ChangeLogic(4);
		break;
	case 57:
		return;
		break;
	default:
		cout << "잘못 입력했어ㅠ.ㅠ";
		Sleep(1000);
		Change();
		break;
	}
	Sleep(1000);
	Change();
}

void ChangeLogic(int i)
{
	if (coreBag[i] > 0)
	{
		coreBag[i]--;
		wallet += corePrice[i];
		cout << "<<" << coreBagName[i] << ">> 를(을) 팔아 " << corePrice[i] << "원 만큼 벌었다.";
		Sleep(1000);
	}
	else
	{
		int r = rand() % 3;
		switch (r) {
		case 0:
			cout << "환전 해줄 수 없어." << endl;
			break;
		case 1:
			cout << "바꿔 주고싶어도 광물이 없는데?" << endl;
			break;
		case 2:
			cout << "광물을 가져와야 바꿔줄거야 ㅡㅡ;;" << endl;
			break;
		}
	}
}

void SetModeConsole(bool value) //value가 true : 기본 출력 false : 유니코드
{
	if(value)
		_setmode(_fileno(stdout), _O_TEXT);
	else
		_setmode(_fileno(stdout), _O_U16TEXT);
}

void SetWallet() 
{
	wallet += secPrice;
}
