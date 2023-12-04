#include <windows.h>

// 전역 변수
HWND hwnd;
RECT drawnRect = { 0 }; // 초기 사각형 위치
BOOL isMouseLButtonDown = FALSE;
POINT circleCenter = { 0 }; // 원의 중심 좌표

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_LBUTTONDOWN:
    {
        isMouseLButtonDown = TRUE;
        drawnRect.left = LOWORD(lParam);
        drawnRect.top = HIWORD(lParam);
    }
    break;

    case WM_MOUSEMOVE:
    {
        if (isMouseLButtonDown)
        {
            drawnRect.right = LOWORD(lParam);
            drawnRect.bottom = HIWORD(lParam);

            // 화면 갱신 요청
            InvalidateRect(hwnd, NULL, TRUE);
        }
    }
    break;

    case WM_LBUTTONUP:
    {
        isMouseLButtonDown = FALSE;
    }
    break;

    case WM_RBUTTONDOWN:
    {
        POINT mousePos;
        mousePos.x = LOWORD(lParam);
        mousePos.y = HIWORD(lParam);

        // 마우스 좌표가 사각형 내에 있는지 확인
        if (PtInRect(&drawnRect, mousePos))
        {
            // 원의 중심 좌표를 마우스 좌표로 변경
            circleCenter = mousePos;
        }
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // 사각형 그리기
        Rectangle(hdc, drawnRect.left, drawnRect.top, drawnRect.right, drawnRect.bottom);

        // 원 그리기
        Ellipse(hdc, circleCenter.x - 10, circleCenter.y - 10, circleCenter.x + 10, circleCenter.y + 10);

        EndPaint(hwnd, &ps);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc = { 0 };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MyWindowClass";

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
        return 1;
    }

    hwnd = CreateWindowEx(0, L"MyWindowClass", L"Windows API 예제", WS_OVERLAPPEDWINDOW, 100, 100, 400, 400, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
        return 1;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = { 0 };

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
