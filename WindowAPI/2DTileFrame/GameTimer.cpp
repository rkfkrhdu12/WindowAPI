#include "GameTimer.h"

#include <Windows.h>
GameTimer::GameTimer()
{
	__int64 countsPerSec;
	// cpu 초당 진동수
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	
	_secondsPerCount = 1.0f / (double)countsPerSec;
}

GameTimer::~GameTimer()
{

}

void GameTimer::Init()
{
	__int64 curTime;
	// 현재까지의 cpu 진동수 ?
	QueryPerformanceCounter((LARGE_INTEGER*)&curTime);

	_deltaTime = 0.0f;
	_prevTime = curTime;
}

void GameTimer::Update()
{
	__int64 curTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&curTime);

	_deltaTime = (curTime - _prevTime)* _secondsPerCount;
	_prevTime = curTime;
}

float GameTimer::GetDelta()
{

	return _deltaTime;
}