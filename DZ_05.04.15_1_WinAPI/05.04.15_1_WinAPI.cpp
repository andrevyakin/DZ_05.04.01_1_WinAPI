#include <windows.h> // ������������ ����, ���������� WINAPI
#include <conio.h>

// �������� ������� ��������� ��������� � ���������������� ���������:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR mainMessage1[] = L"�����-�� �����!"; // ������ � ����������
TCHAR mainMessage2[] = L"�����-�� ������ �����!"; // ������ � ����������

// ����������� �������:
int WINAPI WinMain(HINSTANCE hInst, // ���������� ���������� ����������
	HINSTANCE hPrevInst, // �� ����������
	LPSTR lpCmdLine, // �� ����������
	int nCmdShow) // ����� ����������� ������
{
	TCHAR szClassName[] = L"��� �����"; // ������ � ������ ������
	HWND hMainWnd; // ������ ���������� �������� ������
	MSG msg; // ����� ��������� ��������� MSG ��� ��������� ���������
	WNDCLASSEX wc; // ������ ���������, ��� ��������� � ������ ������ WNDCLASSEX
	wc.cbSize = sizeof(wc); // ������ ��������� (� ������)
	wc.style = CS_HREDRAW | CS_VREDRAW; // ����� ������ ������
	wc.lpfnWndProc = WndProc; // ��������� �� ���������������� �������
	wc.lpszMenuName = NULL; // ��������� �� ��� ���� (� ��� ��� ���)
	wc.lpszClassName = szClassName; // ��������� �� ��� ������
	wc.cbWndExtra = NULL; // ����� ������������� ������ � ����� ���������
	wc.cbClsExtra = NULL; // ����� ������������� ������ ��� �������� ���������� ����������
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO); // ��������� �����������
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO); // ���������� ��������� ����������� (� ����)
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // ���������� �������
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // ���������� ����� ��� �������� ���� ����
	wc.hInstance = hInst; // ��������� �� ������, ���������� ��� ����, ������������ ��� ������
	if (!RegisterClassEx(&wc)){
		// � ������ ���������� ����������� ������:
		MessageBox(NULL, L"�� ���������� ���������������� �����!", L"������", MB_OK);
		return NULL; // ����������, �������������, ������� �� WinMain
	}
	// �������, ��������� ������:
	hMainWnd = CreateWindow(
		szClassName, // ��� ������
		L"�� ������ ������", // ��� ������ (�� ��� ������)
		WS_OVERLAPPEDWINDOW | WS_VSCROLL, // ������ ����������� ������
		CW_USEDEFAULT, // ������� ������ �� ��� �
		NULL, // ������� ������ �� ��� � (��� ������ � �, �� ������ �� �����)
		CW_USEDEFAULT, // ������ ������
		NULL, // ������ ������ (��� ������ � ������, �� ������ �� �����)
		(HWND)NULL, // ���������� ������������� ����
		NULL, // ���������� ����
		HINSTANCE(hInst), // ���������� ���������� ����������
		NULL); // ������ �� ������� �� WndProc
	if (!hMainWnd){
		// � ������ ������������� �������� ������ (�������� ��������� � ��):
		MessageBox(NULL, L"�� ���������� ������� ����!", L"������", MB_OK);
		return NULL;
	}

	
		HWND button1 = CreateWindow(
			L"BUTTON", // ������ ������ //
			L"�����", // ��� ����� ������ ������ //
			WS_VISIBLE | WS_CHILD,
			550, /* ��������� � ������� ������*/
			60,
			105,
			20,
			hMainWnd, /* ������������ ����*/
			(HMENU)100, /* ��������� ������� */
			(HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
			NULL);
		

	HWND button3 = CreateWindow(
		L"BUTTON", // ������ ������ //
		L"�����", // ��� ����� ������ ������ //
		WS_VISIBLE | WS_CHILD,
		750, /* ��������� � ������� ������*/
		60,
		105,
		20,
		hMainWnd, /* ������������ ����*/
		(HMENU)300, /* ��������� ������� */
		(HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
		NULL);



	ShowWindow(hMainWnd, nCmdShow); // ���������� ������
	UpdateWindow(hMainWnd); // ��������� ������
	while (GetMessage(&msg, NULL, NULL, NULL)){ // ��������� ��������� �� �������, ���������� ��-�����, ��
		TranslateMessage(&msg); // �������������� ���������
		DispatchMessage(&msg); // ������� ��������� ������� ��
	}
	return msg.wParam; // ���������� ��� ������ �� ����������
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC; // ������ ���������� ���������� ������ �� ������
	PAINTSTRUCT ps; // ���������, ���-��� ���������� � ���������� ������� (�������, ���� � ��)
	RECT rect; // ���-��, ������������ ������ ���������� �������
	COLORREF colorText = RGB(255, 0, 0); // ����� ���� ������
	static bool flag1 = true, flag2 = true;
	switch (uMsg)
	{
	case WM_PAINT: // ���� ����� ����������, ��:
		hDC = BeginPaint(hWnd, &ps); // �������������� �������� ����������
		GetClientRect(hWnd, &rect); // �������� ������ � ������ ������� ��� ���������
		SetTextColor(hDC, colorText); // ������������� ���� ������������ ����������
		if (flag1)
		{
			flag1 = false;
			InvalidateRect(hWnd, &rect,0);
		
			DrawText(hDC, mainMessage1, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER); // ������ �����
			
		}
		else
		{
			flag1 = true;
			InvalidateRect(hWnd, &rect, 0);
			
			DrawText(hDC, mainMessage2, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER); // ������ ������ �����
			
		}
		EndPaint(hWnd, &ps); // ����������� ��������
		_kbhit();
		break;
	case WM_COMMAND:
	{
					   
					   switch (wParam)
					   {

					   case 100: // ������ ������
						   if (flag2)
						   {
							   flag2 = false;
							   SetWindowText((HWND)lParam, L"�����");
						   }
						   else
						   {
							   flag2 = true;
							   SetWindowText((HWND)lParam, L"�����");
						   }
								   break;
					 

					   case 300 :

						   PostQuitMessage(NULL); // ���������� WinMain() ��������� WM_QUIT
						   break;

					   }
					   break;
	}

	case WM_DESTROY: // ���� ������ ���������, ��:
		PostQuitMessage(NULL); // ���������� WinMain() ��������� WM_QUIT
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return NULL; // ���������� ��������
}