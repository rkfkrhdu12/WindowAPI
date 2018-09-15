#include "Frame.h"



Frame::Frame()
{
	_frameInterval = 0;
	_width = 0;
	_height = 0;
}


Frame::~Frame()
{
}

void Frame::Init(
	ID3DXSprite* spriteDX, IDirect3DTexture9* textureDX,
	int left, int top, int width, int height,
	float frameInterval, D3DCOLOR textureColor, float scale)
{	
	_spriteDX				= spriteDX;
	_textureDX				= textureDX;
	_frameInterval			= frameInterval;
	_scale					= scale;
	_width					= width * _scale;
	_height					= height * _scale;

	_textureRect.left		= left * width;
	_textureRect.top		= top * height;
	_textureRect.right		= _textureRect.left + width;
	_textureRect.bottom		= _textureRect.top + height;

	_textureColor			= textureColor;
}

void Frame::Reset()
{

}

void Frame::Render()
{
	
	D3DXVECTOR2 scale		= D3DXVECTOR2(_scale, _scale);				// 확대/축소 값
	D3DXVECTOR2 rotCenter	= D3DXVECTOR2((_width / 2), (_height / 2)); // 회전중심
	float rot = 0;			//회전
	D3DXVECTOR2 translate	= D3DXVECTOR2(100.0f - _width / 2, 200.0f - _height); // 이동

	D3DXMATRIX matrix; // 크기,회전,회전중심,회전각도,이동
	D3DXMatrixTransformation2D(
		&matrix,		// 연산결과 저장공간
		0,				// scale의 중심점
		0.0f,			// 확대 크기 시킬때 x y 의 비율이 다를경우 조정하는 값
		&scale,			// 확대 축소값
		&rotCenter,		// 회전 중심
		rot,			// 회전 각도
		&translate);	// 이동

	_spriteDX->SetTransform(&matrix);
	// 2D이미지(Texture) 출력 공간 
	_spriteDX->Draw(
		_textureDX,			// 그릴 텍스쳐 정보가 담긴 인터페이스
		&_textureRect,		//  원본 이미지에서 그릴 프레임
		NULL, NULL,
		_textureColor);		// 스프라이트의 색상과 알파채널(투명값)

}