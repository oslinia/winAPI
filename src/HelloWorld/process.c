#include <sec_api/stdio_s.h>
#include <windows.h>
#include "header.h"

RECT rc = {0};

VOID ShowAboutDialog(HWND hWnd) {
    LPCSTR lpText = TEXT("A windowed application with a frame counter, menu, and message box.");

    MessageBox(hWnd, lpText, TEXT("   About"), MB_OK);
}

VOID PaintFrameCount(HDC hDc) {
    static int nFrame = 0;
    TCHAR szFrame[64] = {0};
    int nFrameLen = sprintf_s(szFrame, 64,TEXT("%i"), nFrame);
    nFrame++;
    TextOut(hDc, 5, 5, szFrame, nFrameLen);
}

VOID PaintWindowText(HDC hDc) {
    LPCSTR lpWindowText = TEXT("Hello World!");

    DrawText(hDc, lpWindowText, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
    switch (Msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps = {0};
            HDC hDc = BeginPaint(hWnd, &ps);

            PaintFrameCount(hDc);
            PaintWindowText(hDc);

            EndPaint(hWnd, &ps);
        }
            return 0;
        case WM_SIZE:
            rc.right = LOWORD(lParam);
            rc.bottom = HIWORD(lParam);
            return 0;
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case IDM_ABOUT:
                    ShowAboutDialog(hWnd);
                    return 0;
                case IDM_EXIT:
                    DestroyWindow(hWnd);
                    return 0;
                default: break;
            }
            break;
        case WM_KEYDOWN:
            if (wParam == VK_ESCAPE) {
                DestroyWindow(hWnd);
                return 0;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default: break;
    }
    return DefWindowProc(hWnd, Msg, wParam, lParam);
}
