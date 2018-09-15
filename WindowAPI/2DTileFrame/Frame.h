#pragma once
#include <d3dx9.h>

class Frame
{
private:
	ID3DXSprite * _spriteDX;
	IDirect3DTexture9* _textureDX;

	RECT _textureRect;
	D3DCOLOR _textureColor;
	float _scale;

	float _frameInterval;
	float _width;
	float _height;
public:
	Frame();
	~Frame();

	void Init(ID3DXSprite* spriteDX, IDirect3DTexture9* textureDX,
		int left, int top, int width, int height,
		float frameInterval,D3DCOLOR textureColor, float scale);
	void Reset();

	void Render();

	float GetInterval() { return _frameInterval; }
};

