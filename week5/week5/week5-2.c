#include <windows.h>

POINT startPoint = { 0 };
POINT endPoint = { 0 };
int isMouseLButtonPressed = 0;
int isMouseRButtonPressed = 0;
int isRectDrawn = 0;

RECT drawnRect = { 0 };
RECT prevRect = { 0 };

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_LBUTTONDOWN:
    {
        startPoint.x = LOWORD(lParam);
        startPoint.y = HIWORD(lParam);
        isMouseLButtonPressed = 1;
        isRectDrawn = 0;
    }
    break;

    case WM_MOUSEMOVE:
    {
        if (isMouseLButtonPressed)
        {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            InvalidateRect(hwnd, NULL, TRUE);
        }
    }
    break;

    case WM_LBUTTONUP:
    {
        endPoint.x = LOWORD(lParam);
        endPoint.y = HIWORD(lParam);
        isMouseLButtonPressed = 0;
        isRectDrawn = 1;
        drawnRect.left = min(startPoint.x, endPoint.x);
        drawnRect.top = min(startPoint.y, endPoint.y);
        drawnRect.right = max(startPoint.x, endPoint.x);
        drawnRect.bottom = max(startPoint.y, endPoint.y);
        InvalidateRect(hwnd, NULL, TRUE);
    }
    break;

    case WM_RBUTTONDOWN:
        if (isRectDrawn)
        {
            POINT mousePos;
            mousePos.x = LOWORD(lParam);
            mousePos.y = HIWORD(lParam);

            // 현재 마우스 위치가 그려진 사각형 안에 있는지 확인
            if (PtInRect(&drawnRect, mousePos))
            {
                isMouseRButtonPressed = 1;
                prevRect = drawnRect; // 드래그 이전의 사각형 좌표 저장
            }
        }
        break;

    case WM_RBUTTONUP:
        if (isMouseRButtonPressed)
        {
            POINT mousePos;
            mousePos.x = LOWORD(lParam);
            mousePos.y = HIWORD(lParam);

            // 드래그한 거리 계산
            int deltaX = mousePos.x - startPoint.x;
            int deltaY = mousePos.y - startPoint.y;

            // 드래그한 거리만큼 사각형 좌표 업데이트
            drawnRect.left = prevRect.left + deltaX;
            drawnRect.top = prevRect.top + deltaY;
            drawnRect.right = prevRect.right + deltaX;
            drawnRect.bottom = prevRect.bottom + deltaY;

            // 사각형 그리기 활성화 및 화면 다시 그리기
            isRectDrawn = 1;
            InvalidateRect(hwnd, NULL, TRUE);
        }
        isMouseRButtonPressed = 0;
        break;



    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        RECT clientRect;
        GetClientRect(hwnd, &clientRect);
        FillRect(hdc, &clientRect, (HBRUSH)(COLOR_WINDOW + 1));

        if (isRectDrawn)
        {
            HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
            FillRect(hdc, &drawnRect, hBrush);
            DeleteObject(hBrush);
        }

        EndPaint(hwnd, &ps);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return S_OK;
}

#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
#endif
{
    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(wc));

    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("DrawingApp");
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_CROSS);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;

    if (RegisterClass(&wc) == 0)
    {
        MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
        exit(-1);
    }

    RECT rect = { 150, 100, 800, 600 };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    HWND hwnd = CreateWindow(
        wc.lpszClassName,
        TEXT("202007007 박상원"),
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        0, 0,
        width, height,
        NULL, NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL)
    {
        MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
        exit(-1);
    }

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (msg.message != WM_QUIT)
    {
        if (GetMessage(&msg, hwnd, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}
