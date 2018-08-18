#include "GameTimer.h"

#include <Windows.h>
GameTimer::GameTimer()
{
	__int64 countsPerSec;
	// cpu �ʴ� ������
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	
	_secondsPerCount = 1.0f / (double)countsPerSec;
}

GameTimer::~GameTimer()
{

}

void GameTimer::Init()
{
	__int64 curTime;
	// ��������� cpu ������ ?
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