#pragma once
#include <d3dx9.h>
#include <iostream>

class Sprite
{
private:

	std::wstring _fileName;

	D3DXIMAGE_INFO _texInfo;
	RECT _textureRect;
	D3DCOLOR _textureColor;

	ID3DXSprite* _spriteDX;
	IDirect3DTexture9* _textureDX;
	IDirect3DDevice9* _dxDevice;
public:
	Sprite();
	~Sprite();

	void Init(IDirect3DDevice9* dxDevice,std::wstring fileName, ID3DXSprite* spriteDX);
	void Release();
	void Reset();

	void Render();
};

