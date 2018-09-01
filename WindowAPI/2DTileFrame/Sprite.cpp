#include "Sprite.h"



Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}

void Sprite::Init(IDirect3DDevice9* dxDevice, std::wstring fileName, ID3DXSprite* spriteDX)
{
	_fileName = fileName;
	_dxDevice = dxDevice;
	_spriteDX = spriteDX;

	HRESULT hr = D3DXGetImageInfoFromFile(_fileName.c_str(), &_texInfo);
	if (FAILED(hr)) { return; }

	int walkAni			 = 1;	// left idle right
	int dirAni			 = 0;	// bottom left right top
	int texWidthBlock	 = _texInfo.Width / (3 * 4);
	int texHeightBlock	 = _texInfo.Height / (4 * 2);
	_textureRect.left	 = texWidthBlock * walkAni;
	_textureRect.top	 = texHeightBlock * dirAni;
	_textureRect.right	 = _textureRect.left + texWidthBlock;
	_textureRect.bottom	 = _textureRect.top + texHeightBlock;

	//  이미지 데이터 로드
	hr = D3DXCreateTextureFromFileEx(
		_dxDevice, _fileName.c_str(),
		_texInfo.Width, _texInfo.Height,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT, D3DX_DEFAULT,
		D3DCOLOR_ARGB(255, 255, 255, 255),
		&_texInfo,
		NULL,
		&_textureDX);
	if (FAILED(hr)) { return; }

	_textureColor = D3DCOLOR_ARGB(255, 255, 255, 255);
}

void Sprite::Release()
{
	if (_textureDX)
	{
		_textureDX->Release();
		_textureDX = 0;
	}
}

void Sprite::Reset()
{
	HRESULT hr = D3DXCreateTextureFromFileEx(
		_dxDevice, _fileName.c_str(),
		_texInfo.Width, _texInfo.Height,
		1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_DEFAULT,
		D3DX_DEFAULT, D3DX_DEFAULT,
		D3DCOLOR_ARGB(255, 255, 255, 255),
		&_texInfo, 0, &_textureDX);
}

void Sprite::Render()
{
	// 2D이미지(Texture) 출력 공간 
	_spriteDX->Draw(
		_textureDX,			// 그릴 텍스쳐 정보가 담긴 인터페이스
		&_textureRect,		//  원본 이미지에서 그릴 프레임
		NULL, NULL,
		_textureColor);		// 스프라이트의 색상과 알파채널(투명값)
}