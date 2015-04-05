#include<Windows.h>
#include<tchar.h>

static TCHAR WindowsClass[] = L"win32app";
static TCHAR Title[] = L"MyApp";
HINSTANCE hinst;
bool flag = true;

#define ID_BUTTON1 1001
#define ID_BUTTON2 1002
#define ID_EDIT1 1004

HWND button1, button2, edit1;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hinstance;
	wcex.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	/*wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);*/
	wcex.hbrBackground = CreateSolidBrush(RGB(150, 70, 150));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WindowsClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, L"Call faild!", L"MyApp", NULL);
		return 1;
	}

	hinst = hinstance;

	HWND hWnd = CreateWindow(
		WindowsClass,
		Title,
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		800,
		500,
		NULL,
		NULL,
		hinst,
		NULL);

	if (!hWnd)
	{
		MessageBox(NULL, L"Create window faild!", L"MyApp", NULL);
		return 1;
	}
	SetTimer(hWnd, 1, 100, NULL);
	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return(int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;
	
	TCHAR text1[] = L"Какой нибудь, неважно какой длинный текст";
	TCHAR text2[] = L"Какой нибудь, ДРУГОЙ текст";
	TCHAR text3[] = L"Далее";
	TCHAR text4[] = L"Выход";
	TCHAR text5[] = L"Назад";

	switch (message)
	{
	
	case WM_COMMAND:

	case BN_CLICKED:

		if (LOWORD(wParam) == ID_BUTTON1)
		{
			
			if (flag)

			{
				flag = false;
				SendMessage(button1, WM_SETTEXT, sizeof(text5), (LPARAM)text5);
				SendMessage(edit1, WM_SETTEXT, (WPARAM)0, (LPARAM)text2);
			}
			else
			{
				flag = true;
				SendMessage(button1, WM_SETTEXT, sizeof(text3), (LPARAM)text3);
				SendMessage(edit1, WM_SETTEXT, (WPARAM)0, (LPARAM)text1);
			}
		}
		
		if (LOWORD(wParam) == ID_BUTTON2)
			PostQuitMessage(NULL);
		
		break;

	case WM_CREATE:

		GetClientRect(hWnd, &rect);
				
		edit1 = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"edit",
			text1,
			WS_CHILD | WS_VISIBLE,
			rect.right / 2 - ARRAYSIZE(text1) * 4.5,		/*координаты по X*/
			(rect.bottom / 3),								/*координаты по Y*/
			sizeof(text1)* sizeof(TCHAR) * 2,				/*Ширина окошка*/
			20,
			hWnd,
			(HMENU)ID_EDIT1,
			hinst,
			NULL);

		
		button1 = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"button",
			text3,
			WS_CHILD | WS_VISIBLE,
			rect.right / 3 - ARRAYSIZE(text3) * 4,		/*координаты по X*/
			(rect.bottom / 1.66),						/*координаты по Y*/
			ARRAYSIZE(text3) * 10,						/*Ширина окошка*/
			25,
			hWnd,
			(HMENU)ID_BUTTON1,
			hinst,
			NULL);

		button2 = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"button",
			text4,
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			rect.right / 1.66 - ARRAYSIZE(text4) * 4,		/*координаты по X*/
			(rect.bottom / 1.66),						/*координаты по Y*/
			ARRAYSIZE(text4) * 10,						/*Ширина окошка*/
			25,
			hWnd,
			(HMENU)ID_BUTTON2,
			hinst,
			NULL);
		
		break;
	
	case WM_PAINT:
		
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}