#pragma once
class GameTimer
{
private:
	float _secondsPerCount;

	float _prevTime;
	float _deltaTime;

public:
	GameTimer();
	~GameTimer();

	void Init();
	void Update();

	float GetDelta();

};

