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

void Frame::Init(ID3DXSprite* spriteDX, IDirect3DTexture9* textureDX, int left, int top, int width, int height, float frameInterval, D3DCOLOR textureColor)
{	
	_spriteDX				= spriteDX;
	_textureDX				= textureDX;
	_frameInterval			= frameInterval;
	_width					= width;
	_height					= height;

	_textureRect.left		= left;
	_textureRect.top		= top;
	_textureRect.right		= _textureRect.left + width;
	_textureRect.bottom		= _textureRect.top + height;

	_textureColor			= textureColor;
}

void Frame::Reset()
{

}

void Frame::Render()
{
	D3DXVECTOR2 scale		= D3DXVECTOR2(3.0f,3.0f);				// Ȯ��/��� ��
	D3DXVECTOR2 rotCenter	= D3DXVECTOR2(_width / 2, _height / 2); // ȸ���߽�
	float rot = 0;			//ȸ��
	D3DXVECTOR2 translate	= D3DXVECTOR2(-_width/2,-_height/2); // �̵�

	D3DXMATRIX matrix; // ũ��,ȸ��,ȸ���߽�,ȸ������,�̵�
	D3DXMatrixTransformation2D(
		&matrix,		// ������ �������
		0,				// scale�� �߽���
		0.0f,			// Ȯ�� ũ�� ��ų�� x y �� ������ �ٸ���� �����ϴ� ��
		&scale,			// Ȯ�� ��Ұ�
		&rotCenter,		// ȸ�� �߽�
		rot,			// ȸ�� ����
		&translate);	// �̵�

	_spriteDX->SetTransform(&matrix);
	// 2D�̹���(Texture) ��� ���� 
	_spriteDX->Draw(
		_textureDX,			// �׸� �ؽ��� ������ ��� �������̽�
		&_textureRect,		//  ���� �̹������� �׸� ������
		NULL, NULL,
		_textureColor);		// ��������Ʈ�� ����� ����ä��(����)

}