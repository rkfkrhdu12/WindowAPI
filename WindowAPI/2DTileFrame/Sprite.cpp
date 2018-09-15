#include "Sprite.h"

#include "Frame.h"

#define WALK1 0
#define IDLE 1
#define WALK2 2

#define Character0 0
#define Character1 3
#define Character2 6
#define Character3 9

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
	

	_frameIdx = 0;
	_frameTime = 0;


	int width = _texInfo.Width / (3 * 4);
	int height = _texInfo.Height / (4 * 2);

	{
		Frame* frame = new Frame();
		frame->Init(_spriteDX, _textureDX,
			Character0+ WALK1, 0, width, height,
			.3f, D3DCOLOR_ARGB(255, 255, 255, 255),1.0f);
		_frameList.push_back(frame);
	}
	{
		Frame* frame = new Frame();
		frame->Init(_spriteDX, _textureDX,
			Character0+ WALK2, 0, width, height,
			.3f, D3DCOLOR_ARGB(255, 255, 255, 255),1.0f);
		_frameList.push_back(frame);
	}
	{
		Frame* frame = new Frame();
		frame->Init(_spriteDX, _textureDX,
			Character1 + WALK1, 0, width, height,
			.5f, D3DCOLOR_ARGB(255, 255, 0, 0), 2.0f);
		_frameList.push_back(frame);
	}
	{
		Frame* frame = new Frame();
		frame->Init(_spriteDX, _textureDX,
			Character1 + WALK2, 0, width, height,
			.5f, D3DCOLOR_ARGB(255, 255, 0, 0), 2.0f);
		_frameList.push_back(frame);
	}
}
void Sprite::Update(float deltaTime)
{
	_frameTime += deltaTime;
	if (_frameList[_frameIdx]->GetInterval() < _frameTime)
	{
		_frameTime = 0;
		_frameIdx++;
		if (_frameList.size() <= _frameIdx)
		{
			_frameIdx = 0;
		}
	}
}

void Sprite::Release()
{
	for (int i = 0; i < _frameList.size(); i++)
	{
		delete _frameList[i];
	}
	_frameList.clear();


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
	if (_frameIdx < _frameList.size())
	{
		_frameList[_frameIdx]->Render();
	}
}