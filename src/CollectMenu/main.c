#include <windows.h>
#include "header.h"

HINSTANCE hInst;

BOOL InitApplication(LPCSTR);

BOOL InitInstance(LPCSTR, int);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    hInst = hInstance;

    const char *lpClassName = TEXT("MainWClass");

    if (!InitApplication(lpClassName))
        return FALSE;

    if (!InitInstance(lpClassName, nShowCmd))
        return FALSE;

    MSG msg;
    BOOL fGotMessage;
    while ((fGotMessage = GetMessage(&msg, (HWND) NULL, 0, 0)) != 0 && fGotMessage != -1) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int) msg.wParam;
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
}

BOOL InitApplication(const char *lpClassName) {
    WNDCLASSEX wcx;
    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_HREDRAW | CS_VREDRAW;
    wcx.lpfnWndProc = WindowProcedure;
    wcx.cbClsExtra = 0;
    wcx.cbWndExtra = 0;
    wcx.hInstance = hInst;
    wcx.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON));
    wcx.hCursor = LoadCursor(hInst, IDC_ARROW);
    wcx.hbrBackground = GetStockObject(WHITE_BRUSH);
    wcx.lpszMenuName = TEXT("MainMenu");
    wcx.lpszClassName = lpClassName;
    wcx.hIconSm = LoadImage(hInst,
                            MAKEINTRESOURCE(IDI_ICON),
                            IMAGE_ICON,
                            GetSystemMetrics(SM_CXSMICON),
                            GetSystemMetrics(SM_CYSMICON),
                            LR_DEFAULTCOLOR);

    return RegisterClassEx(&wcx);
}

BOOL InitInstance(const char *lpClassName, const int nCmdShow) {
    HWND hWnd = CreateWindow(
        lpClassName, TEXT("Window Application"), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        (HWND) NULL, (HMENU) NULL, hInst, (LPVOID) NULL);

    if (!hWnd)
        return FALSE;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}
