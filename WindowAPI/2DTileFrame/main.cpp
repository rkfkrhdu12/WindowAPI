#include <Windows.h>

#include "GameTimer.h"
#include <d3d9.h>


// ������ ���ν��� �Լ� : ������� ���� ���� �̺�Ʈ�� ó���ϴ� �Լ� (���� ó���Ѵ�)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		MessageBox(0, "Hello World", "Hello", MB_OK);
		return 0;
	case WM_KEYDOWN:
		if (VK_ESCAPE == wParam) 
		{
			DestroyWindow(hWnd); 
		} // ESCŰ �Է½� ������ �ı��䱸
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(
	HINSTANCE hInstance,	// ���� ���� ���α׷��� ���� �ڵ�
	HINSTANCE hPrevInstance,	// �Ⱦ���
	PSTR pCmdLine,	// �����ϴµ� ���̴� ����� �Ǵ� �μ�
	int nCmdShow	// �������α׷� ǥ�� ���. �ּ�ȭ/�ִ�ȭ �ؼ� �����ٰų� �܎�
)
{
	int width = 1024;
	int height = 768;
	bool isWindow = true;

	// ������ ��Ÿ���� ����� ������ ��Ÿ�� ���
	WNDCLASS wc;
	{
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WndProc;	// ������ ���ν��� �Լ� ���
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(0, IDI_APPLICATION);
		wc.hCursor = LoadCursor(0, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName = 0;
		wc.lpszClassName = "2DTileFrameWnd";			// �� ������ ��Ÿ���� �̸�
	}
	if (FALSE == RegisterClass(&wc)) { return 0; }

	// â �ڵ�(���̵�)�� ���� �߱��� ����
	HWND hWnd;
	{
		hWnd = CreateWindow(
			"2DTileFrameWnd",	// ����� ������ ��Ÿ�� �̸�. OS�� ��� �Ǿ�����.
			"2D Tile Frame",
			WS_OVERLAPPEDWINDOW,	// ������ ��Ÿ��
			CW_USEDEFAULT, CW_USEDEFAULT,	// ������ġ :  x, y
			width, height,		// �ػ�. �ʺ�/����
			0,		// �θ� â�� �ڵ�. ��� ����
			0,		// �޴� �ڵ�. ��� ����
			hInstance,	// OS�� ������ ����. OS���� �����츦 ������ �� �ִ�.
			0
		);
	}
	if (NULL == hWnd) { return 0; }

	// hWnd : �ϳ��� �����츦 ����Ű�� �ڵ�(���̵�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���� ���� ���� Ȯ�� 
	if (true == isWindow)
	{
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);
		MoveWindow(hWnd, 0, 0,
			width + (width - clientRect.right),
			height + (height - clientRect.bottom),
			TRUE);
	}

	// DirectX

	// ������  ���� �ϵ���� ���� ������ ���� ���� ��û
	// DirectX ����          dxDevice			���� ��û

	// �׷����� ����ϴ� direct
	LPDIRECT3D9 direct3d;
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (NULL == direct3d) { return 0; }

	//Device�� �����ϱ���
	//Device�� ���� ȭ���� ��� ���������� ����
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp)); // �޸𸮸� ���� 0���� �ʱ�ȭ
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1; // ���� ���� 
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = isWindow;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// Device ���� ��û
	LPDIRECT3DDEVICE9 dxDevice;
	HRESULT hr = direct3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, // GPU�� ����
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, // GPU�� ����
		&d3dpp,
		&dxDevice);
	if (FAILED(hr)) { return 0; }

	// Msg,Window,Game Update

	//// �� �����찡 ������ �ʰ� �����ǵ��� ó��
	//MSG msg;
	//while (-1 != GetMessage(&msg, 0, 0, 0))	// �߻��� �޽����� ������ GetMessage()�� �޼����� ������ ���ι��Ѽ�ȯ
	//{
	//	TranslateMessage(&msg);		// Ű���� ��ȯ ����
	//	DispatchMessage(&msg);	// �޽��� â�� ����� ��û�Ѵ�.
	//}

	float fps = 60.0f;
	float frameInterval = 1.0f / fps;
	float frameTime = 0.0f; 
	float deltaTime;

	GameTimer gameTimer;
	gameTimer.Init();

	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		// �޼����� ������ �޼��� ó�� ������ ���Ӿ�����Ʈ
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) // msg�� �޼����� ������ true ������ false
		{
				TranslateMessage(&msg);		// Ű���� ��ȯ ����
				DispatchMessage(&msg);	// �޽��� â�� ����� ��û�Ѵ�.
		}
		else
		{
			gameTimer.Update();
			deltaTime = gameTimer.GetDelta();

			frameTime = frameTime + deltaTime;

			if (frameInterval <= frameTime)
			{
				frameTime = 0.0f;

				// �� �����Ӹ��� ȭ���� ���� ä���.
				dxDevice->Clear(0, NULL,
					D3DCLEAR_TARGET,
					D3DCOLOR_XRGB(128, 128, 0),
					0.0f, 0);
				// ä�� ���� ����͸� ���� �����ش�.
				dxDevice->Present(NULL, NULL, NULL, NULL);


			}
		}
	}

	return 0;
}