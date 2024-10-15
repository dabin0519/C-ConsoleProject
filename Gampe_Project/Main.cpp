#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <io.h>
#include <fcntl.h>
#include "GameLogic.h";
#include "console.h";
#include "Event.h";

using namespace std;

int main()
{
	srand((unsigned int)time(NULL));
	Menu();

	while (true) {
		Render();
		Event();
	}
}