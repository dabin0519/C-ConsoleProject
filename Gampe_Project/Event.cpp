#include <iostream>
#include <time.h>;
#include <Windows.h>
#include "Event.h"
#include "GameLogic.h"

using namespace std;

float _coolTime = 5; 
float _time = 0;
float _currentTime = 0;

void Event()
{
	_time = clock();

	if (_time - _currentTime > _coolTime * 1000)
	{
		_currentTime = clock();
	}
}
