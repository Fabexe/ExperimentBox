// main.c
// Simple Win32 program that shows a white window

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
        switch (msg) {
        case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
        default:
                return DefWindowProc(hwnd, msg, wParam, lParam);
        }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
        const char CLASS_NAME[] = "WhiteWindowClass";

        WNDCLASS wc = {0};
        wc.lpfnWndProc = WndProc;
        wc.hInstance = hInstance;
        wc.lpszClassName = CLASS_NAME;
        wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

        if (!RegisterClass(&wc)) {
                return 0;
        }

        HWND hwnd = CreateWindowEx(
                0,
                CLASS_NAME,
                "White Screen",
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
                NULL,
                NULL,
                hInstance,
                NULL
        );

        if (!hwnd) return 0;

        ShowWindow(hwnd, nShowCmd);
        UpdateWindow(hwnd);

        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
        }

        return (int)msg.wParam;
}