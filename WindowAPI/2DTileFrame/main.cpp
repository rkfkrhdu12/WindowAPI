#include <Windows.h>

#include "GameTimer.h"
//#include ""
// 윈도우 프로시저 함수 : 윈도우로 부터 받은 이벤트를 처리하는 함수 (내가 처리한다)
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
		} // ESC키 입력시 윈도우 파괴요구
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(
	HINSTANCE hInstance,	// 현재 응용 프로그램의 메인 핸들
	HINSTANCE hPrevInstance,	// 안쓰임
	PSTR pCmdLine,	// 실행하는데 쓰이는 명령줄 또는 인수
	int nCmdShow	// 응용프로그램 표시 방식. 최소화/최대화 해서 보여줄거냐 겨렂
)
{
	// 윈도우 스타일을 만들고 윈도우 스타일 등록
	WNDCLASS wc;
	{
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WndProc;	// 윈도우 프로시저 함수 등록
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(0, IDI_APPLICATION);
		wc.hCursor = LoadCursor(0, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wc.lpszMenuName = 0;
		wc.lpszClassName = "2DTileFrameWnd";			// 이 윈도우 스타일의 이름
	}
	if (FALSE == RegisterClass(&wc)) { return 0; }

	// 창 핸들(아이디)를 먼저 발급을 받자
	HWND hWnd;
	{
		hWnd = CreateWindow(
			"2DTileFrameWnd",	// 사용할 윈도우 스타일 이름. OS에 등록 되어있음.
			"2D Tile Frmae",
			WS_OVERLAPPEDWINDOW,	// 윈도우 스타일
			CW_USEDEFAULT, CW_USEDEFAULT,	// 시작위치 :  x, y
			1024, 768,		// 해상도. 너비/높이
			0,		// 부모 창의 핸들. 사용 안함
			0,		// 메뉴 핸들. 사용 안함
			hInstance,	// OS와 윈도우 연결. OS에서 윈도우를 관리할 수 있다.
			0
		);
	}
	if (NULL == hWnd) { return 0; }

	// hWnd : 하나의 윈도우를 가리키는 핸들(아이디)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//// 이 윈도우가 꺼지지 않고 유지되도록 처리
	//MSG msg;
	//while (-1 != GetMessage(&msg, 0, 0, 0))	// 발생된 메시지가 있으면 GetMessage()는 메세지가 없으면 내부무한순환
	//{
	//	TranslateMessage(&msg);		// 키보드 변환 수행
	//	DispatchMessage(&msg);	// 메시지 창에 배분을 요청한다.
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
		// 메세지가 있으면 메세지 처리 없으면 게임업데이트
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) // msg에 메세지가 있으면 true 없으면 false
		{
				TranslateMessage(&msg);		// 키보드 변환 수행
				DispatchMessage(&msg);	// 메시지 창에 배분을 요청한다.
		}
		else
		{
			gameTimer.Update();
			deltaTime = gameTimer.GetDelta();

			frameTime += deltaTime;
			// todo : gameUpdate
			if (frameInterval <= frameTime)
			{
				// 60fps
				frameTime = 0.0f;

				OutputDebugString("Update\n");
			}
		}
	}

	return 0;
}