#include <sec_api/stdio_s.h>
#include <windows.h>
#include "header.h"

RECT rc = {0};

VOID MainMenu(HWND hWnd) {
    HMENU hMenuOptions = CreatePopupMenu();

    AppendMenu(hMenuOptions,MF_STRING, IDM_FILE_ITEM, "Item");

    HMENU hMenuFile = CreatePopupMenu();

    AppendMenu(hMenuFile,MF_CHECKED | MF_STRING, IDM_FILE_CHECK, "Checked");
    AppendMenu(hMenuFile,MF_POPUP, (UINT_PTR) hMenuOptions, "Options");
    AppendMenu(hMenuFile,MF_SEPARATOR, 0, 0);
    AppendMenu(hMenuFile,MF_STRING, IDM_FILE_EXIT, "Exit");

    HMENU hMainMenu = CreateMenu();

    AppendMenu(hMainMenu,MF_POPUP, (UINT_PTR) hMenuFile, "File");
    AppendMenu(hMainMenu,MF_STRING, IDM_ABOUT, "About");

    SetMenu(hWnd, hMainMenu);
}

VOID ShowAboutDialog(HWND hWnd) {
    const char *lpText = TEXT(
        "Windowed application with frame counter,"
        " menu built on functions,"
        " modal message window.");

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

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
    switch (Msg) {
        case WM_CREATE:
            MainMenu(hWnd);
            break;
        case WM_SIZE:
            rc.right = LOWORD(lParam);
            rc.bottom = HIWORD(lParam);
            return 0;
        case WM_PAINT: {
            PAINTSTRUCT ps = {0};
            HDC hDc = BeginPaint(hWnd, &ps);

            PaintFrameCount(hDc);
            PaintWindowText(hDc);

            EndPaint(hWnd, &ps);
        }
            return 0;
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case IDM_FILE_CHECK:
                case IDM_FILE_ITEM:
                    MessageBeep(MB_ICONWARNING);
                    return 0;
                case IDM_FILE_EXIT:
                    DestroyWindow(hWnd);
                    return 0;
                case IDM_ABOUT:
                    ShowAboutDialog(hWnd);
                    break;
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
