#include <windows.h>

// ���������� �������
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM RegMyWindowClass(HINSTANCE, LPCTSTR);

////////////////////////////////////////////////////////////////////////// 
// ������� ��������� ��������� WinMain
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE         hPrevInstance,
	LPSTR             lpCmdLine,
	int               nCmdShow)
{

	// ��� �������� ������
	LPCTSTR lpzClass = TEXT("My Window Class!");

	// ����������� ������
	if (!RegMyWindowClass(hInstance, lpzClass))
		return 1;

	// ���������� ��������� ������ ������
	RECT screen_rect;
	GetWindowRect(GetDesktopWindow(), &screen_rect); // ���������� ������
	//int x = screen_rect./ 2 - 150;
	//int y = screen_rect.bottom / 2 - 75;
	int x = screen_rect.left + 150;
	int y = screen_rect.top + 50;

	// �������� ����������� ����
	HWND hWnd = CreateWindow(lpzClass, TEXT("Dialog Window"),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, x, y, 1000, 600, NULL, HWND hWnd1,
		hInstance, NULL);
	HWND hWnd1 = CreateWindow(lpzClass, TEXT("˳��"),
		/*WS_OVERLAPPEDWINDOW | */WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, x, y, 200, 50, HWND hWnd, NULL,
		hInstance, NULL);

	// ���� ���� �� �������, ��������� ����� ����� 0
	if (!hWnd) return 2;

	// ���� ��������� ����������
	MSG msg = { 0 };    // ��������� ���������
	int iGetOk = 0;   // ���������� ���������
	while ((iGetOk = GetMessage(&msg, NULL, 0, 0)) != 0) // ���� ���������
	{
		if (iGetOk == -1) return 3;  // ���� GetMessage ������ ������ - �����
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;  // ���������� ��� ���������� ���������
}

////////////////////////////////////////////////////////////////////////// 
// ������� ����������� ������ ����
ATOM RegMyWindowClass(HINSTANCE hInst, LPCTSTR lpzClassName)
{
	WNDCLASS wcWindowClass = { 0 };
	// ����� �-��� ��������� ���������
	wcWindowClass.lpfnWndProc = (WNDPROC)WndProc;
	// ����� ����
	wcWindowClass.style = CS_HREDRAW | CS_VREDRAW;
	// ���������� ���������� ����������
	wcWindowClass.hInstance = hInst;
	// �������� ������
	wcWindowClass.lpszClassName = lpzClassName;
	// �������� �������
	wcWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	// �������� ����� ����
	wcWindowClass.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
	return RegisterClass(&wcWindowClass); // ����������� ������
}

////////////////////////////////////////////////////////////////////////// 
// ������� ��������� ���������
LRESULT CALLBACK WndProc(
	HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// ������� � ��������� ���������
	switch (message)
	{
	case WM_LBUTTONUP:
		// ������� �� ���������
		MessageBox(hWnd, TEXT("�� ��������!"), TEXT("�������"), 0);
		break;
	case WM_COMMAND:
		if (lparam == (LPARAM)hWnd1)
	case WM_DESTROY:
		PostQuitMessage(0);  // ������� �� ���������
		break;
	default:
		// ��� ��������� �� ������������ ���� ���������� ���� Windows
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}