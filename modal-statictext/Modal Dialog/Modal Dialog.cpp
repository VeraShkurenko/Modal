#include <windows.h>
#include <tchar.h>
#include "resource.h"
using namespace std;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	hInst = hInstance;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

TCHAR szStatic[50];
BOOL staticCounter = 0;

BOOL startX, startY;
BOOL endX, endY;

void CreateStatic(HWND& hWnd)
{
	int lowestX = min(startX, endX);
	int highestX = max(startX, endX);
	int lowestY = min(startY, endY);
	int highestY = max(startY, endY);

	if (highestX - lowestX < 10 || highestY - lowestY < 10)
	{
		MessageBox(hWnd, TEXT("Мінімальний розмір елемента - 10x10"), TEXT("Помилка"), MB_OK | MB_ICONERROR);
		return;
	}

	staticCounter++;

	HWND staticText = CreateWindowEx(0, TEXT("STATIC"), 0, WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | WS_EX_CLIENTEDGE,
		lowestX, lowestY, highestX - lowestX, highestY - lowestY, hWnd, 0, hInst, 0);

	wsprintf(szStatic, TEXT("№%d"), staticCounter);
	SetWindowText(staticText, szStatic);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		startX = LOWORD(lParam);
		startY = HIWORD(lParam);
		return TRUE;
	case WM_LBUTTONUP:
		endX = LOWORD(lParam);
		endY = HIWORD(lParam);
		CreateStatic(hWnd);
		return TRUE;
	case WM_SHOWWINDOW:
		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}