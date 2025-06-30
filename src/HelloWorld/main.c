#include <windows.h>
#include "header.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow) {
    WNDCLASSEX wcx = {0};
    wcx.cbSize = sizeof(WNDCLASSEX);
    wcx.style = CS_HREDRAW | CS_VREDRAW;
    wcx.lpfnWndProc = WindowProc;
    wcx.hInstance = hInst;
    wcx.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON));
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcx.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wcx.lpszMenuName = MAKEINTRESOURCE(IDM_MENU);
    wcx.lpszClassName = TEXT("MainClass");
    if (RegisterClassEx(&wcx) == 0)
        return 1;

    HWND hWnd = CreateWindowEx(
        0, TEXT("MainClass"), TEXT("Window Application"), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
        NULL, NULL, hInst, 0);

    if (NULL == hWnd)
        return 2;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG Msg = {0};
    while (GetMessage(&Msg, NULL, 0, 0)) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return 0;
}
