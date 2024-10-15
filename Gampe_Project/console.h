#pragma once
#include <Windows.h>
enum class COLOR {
	BLACK, VLUE, GREEN, SKYBLUE, RED, VIOLET, YELLOW, 
	LIGHT_GRAY, GRAY, LIGHT_BLUE, LIGHT_GREEN, MINT,
	LIGHT_RED, LIGHT_VIOLET, LIGHT_YELLOW, WHITE

};

void FullScreen();
void Gotoxy(int, int);
BOOL Gotoxytest(int, int);
void CursorSet(bool, DWORD);
void SetColor(int color, int bgColor);
int GetColor();
int GetbgColor();
void GotoxyPlayer(int, int);
void fontsize(UINT _weight, UINT _sizex, UINT _sizey);