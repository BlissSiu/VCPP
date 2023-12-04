#include <windows.h>
#include "yuhanCG.h"
#include "View.h"

int isPressButton = 0;
bool isPressSpace = false;
bool isMouseLbPress = false;
bool isMouseRbPress = false;
bool inMouse = false;
bool isDraw= false;

POINT StartPoint{ 0 }, EndPoint{ 0 };
RECT viewBox = { 0 };
RECT drawView = { 0 };
RECT Box = { 0 };


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    switch (message) {
    case WM_COMMAND:
    {
        //박스 클릭
        if (LOWORD(wParam) == 1)
        {
            isPressButton = 1;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        //원 클릭
        if (LOWORD(wParam) == 2)
        {
            isPressButton = 2;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        // 보노보노클릭
        if (LOWORD(wParam) == 3)
        {
            isPressButton = 3;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        //라이언클릭
        if (LOWORD(wParam) == 4)
        {
            isPressButton = 4;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        //큐브클릭
        if (LOWORD(wParam) == 5)
        {
            isPressButton = 5;
            InvalidateRect(hWnd, NULL, TRUE);
        }
    }
    break;

    case WM_SETCURSOR:
    {
        POINT mousePos;
        GetCursorPos(&mousePos);
        ScreenToClient(hWnd, &mousePos);

        if (PtInRect(&drawView, mousePos)) {
            SetCursor(LoadCursor(NULL, IDC_CROSS)); // 드로잉 영역 내에 있다면 CROSS 커서로 설정
        }
        else {
            SetCursor(LoadCursor(NULL, IDC_ARROW));// 드로잉 영역 밖에 있다면 기본 커서로 설정
        }

        return TRUE;
    }
    break;

    case WM_KEYDOWN:
        if (wParam == VK_SPACE)
        {
            isPressSpace = true;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_KEYUP:
    {
        isPressSpace = false;
        InvalidateRect(hWnd, NULL, TRUE);
    }
    break;
    case WM_LBUTTONDOWN:
    {
        isMouseLbPress = true;

        StartPoint.x = LOWORD(lParam);
        StartPoint.y = HIWORD(lParam);

        InvalidateRect(hWnd, NULL, TRUE);
    }
    break;
    case WM_RBUTTONDOWN:
    {
        isMouseRbPress = true;

        int mouseX = LOWORD(lParam);
        int mouseY = HIWORD(lParam);

        if (mouseX >= Box.left && mouseX <= Box.right &&
            mouseY >= Box.top && mouseY <= Box.bottom) {
            InvalidateRect(hWnd, NULL, TRUE);
            inMouse = true;
        }
        if (isPressButton == 2) {
            if (isDraw) {
                InvalidateRect(hWnd, NULL, TRUE);
                isDraw = false;
            }
        }
    }
         break;
    case WM_LBUTTONUP: 
    {
        HDC hdc = GetDC(hWnd);
        isMouseLbPress = false;
        if (inMouse == false) {
            if (isPressButton == 1) {
                DrawBox(hWnd, hdc, StartPoint.x, StartPoint.y, EndPoint.x, EndPoint.y);
                Box = { StartPoint.x, StartPoint.y, EndPoint.x, EndPoint.y };
            }
            if (isPressButton == 2) {
                DrawCircle(hWnd, hdc, StartPoint.x, StartPoint.y, EndPoint.x, EndPoint.y);
            }
            if (isPressButton == 4) {
                DrawRyan(hWnd, hdc, StartPoint.x, StartPoint.y, EndPoint.x, EndPoint.y);
            }
        }
        ReleaseDC(hWnd, hdc);
    }
      
                     break;
    case WM_RBUTTONUP:
    {
        HDC hdc = GetDC(hWnd);
        isMouseRbPress = false;

        if (inMouse) {
            if (isPressButton == 1) {
                DrawBox(hWnd, hdc, StartPoint.x, StartPoint.y, EndPoint.x, EndPoint.y);
                Box = { StartPoint.x, StartPoint.y, EndPoint.x, EndPoint.y };
            }
        }
        inMouse = false;
        ReleaseDC(hWnd, hdc);
    }
    break;
    case WM_MOUSEMOVE: 
    {
        HDC hdc = GetDC(hWnd);
        if (isMouseLbPress) 
        {
            EndPoint.x = LOWORD(lParam);
            EndPoint.y = HIWORD(lParam);

        }
        if (isMouseRbPress) {
            

            int newX = LOWORD(lParam);
            int newY = HIWORD(lParam);

            // 이동 거리 계산
            int deltaX = newX - StartPoint.x;
            int deltaY = newY - StartPoint.y;

            if (isPressButton == 2) {
                if (deltaX > 0) {
                    DrawCircle(hWnd, hdc, StartPoint.x, StartPoint.y, EndPoint.x+ deltaX, EndPoint.y+ deltaX);
                    isDraw = true;
                }
                else if (deltaX < 0) {
                    DrawCircle(hWnd, hdc, StartPoint.x, StartPoint.y, EndPoint.x - deltaX, EndPoint.y - deltaX);
                    isDraw = true;
                }
            }
            else
            {
                // 사각형의 위치 업데이트
                StartPoint.x += deltaX;
                StartPoint.y += deltaY;
                EndPoint.x += deltaX;
                EndPoint.y += deltaY;


            }

                
            ReleaseDC(hWnd, hdc);
        }
    }
                     break;
    case WM_PAINT: 
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        
        ViewBox(hWnd, hdc, viewBox);
        DrawView(hWnd, hdc, drawView);

        if (isPressButton == 3) {
            DrawBonobono(hWnd, hdc, isPressSpace);
        }

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

    HWND hWnd;
    HWND hButton1, hButton2, hButton3, hButton4, hButton5;

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255, 240, 200));
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"ButtonWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        return 1;
    }

    hWnd = CreateWindow(
        L"ButtonWindowClass", L"Win32 Button Example", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 800, 480, NULL, NULL, hInstance, NULL);


    if (!hWnd) {
        return FALSE;
    }

    hButton1 = CreateWindow(
        L"BUTTON", L"Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        16, 16, 137, 64 + 8 * 2, hWnd, (HMENU)1, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        137 + 16 * 2, 16, 137, 64 + 8 * 2, hWnd, (HMENU)2, hInstance, NULL);

    hButton3 = CreateWindow(
        L"BUTTON", L"BonoBono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        137 * 2 + 16 * 3, 16, 137, 64 + 8 * 2, hWnd, (HMENU)3, hInstance, NULL);

    hButton4 = CreateWindow(
        L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        137 * 3 + 16 * 4, 16, 137, 64 + 8 * 2, hWnd, (HMENU)4, hInstance, NULL);

    hButton5 = CreateWindow(
        L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        137 * 4 + 16 * 5, 16, 137, 64 + 8 * 2, hWnd, (HMENU)5, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}