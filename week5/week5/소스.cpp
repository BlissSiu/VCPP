#include <windows.h>

// ���� ����
HWND hwnd;
RECT drawnRect = { 0 }; // �ʱ� �簢�� ��ġ
BOOL isMouseLButtonDown = FALSE;
POINT circleCenter = { 0 }; // ���� �߽� ��ǥ

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

            // ȭ�� ���� ��û
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

        // ���콺 ��ǥ�� �簢�� ���� �ִ��� Ȯ��
        if (PtInRect(&drawnRect, mousePos))
        {
            // ���� �߽� ��ǥ�� ���콺 ��ǥ�� ����
            circleCenter = mousePos;
        }
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // �簢�� �׸���
        Rectangle(hdc, drawnRect.left, drawnRect.top, drawnRect.right, drawnRect.bottom);

        // �� �׸���
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

    hwnd = CreateWindowEx(0, L"MyWindowClass", L"Windows API ����", WS_OVERLAPPEDWINDOW, 100, 100, 400, 400, NULL, NULL, hInstance, NULL);

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
