#include <windows.h>

POINT startPoint = { 0 }; //마우스 클릭 시작 좌표
POINT endPoint = { 0 }; // 마우스 클릭 끝나는 좌표
POINT mousePos = { 0 }; //이동시킬때 필요한 좌표
bool isMouseLButtonPressed = false;
int changeMode = 0;
bool isdraw = false;
int move = 0;

RECT rect = { 0 }; //사각형
RECT circle = { 0 }; //원


// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    const wchar_t* text = L"선";

    switch (message) {
    case WM_COMMAND:
  
        if (LOWORD(wParam) == 1) {
            changeMode++;
            if (changeMode > 2) {
                changeMode = 0;
            }
            InvalidateRect(hWnd, NULL, TRUE);
            isdraw = false;
        }
        else if (LOWORD(wParam) == 2) {
            // 두 번째 버튼 클릭
            InvalidateRect(hWnd, NULL, TRUE);
            isdraw = false;
        }
        break;

    case WM_LBUTTONDOWN:
        isMouseLButtonPressed = true;
        isdraw = false;
        startPoint.x = LOWORD(lParam);
        startPoint.y = HIWORD(lParam);
        break;

    case WM_LBUTTONUP: {
        HDC hdc = GetDC(hWnd);
        isMouseLButtonPressed = false;
        isdraw = true;
        //사각형 그리기 
        if (changeMode == 1) {
            HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            rect = { startPoint.x, startPoint.y, endPoint.x, endPoint.y };
            SelectObject(hdc, hBrush);
            Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
            DeleteObject(hBrush);

        }
        //원그리기
        if (changeMode == 2) {
            HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);

            circle = { startPoint.x, startPoint.y, endPoint.x, endPoint.y };
            SelectObject(hdc, hBrush);
            Ellipse(hdc, circle.left, circle.top, circle.right, circle.bottom);
            DeleteObject(hBrush);
        }
        ReleaseDC(hWnd, hdc);
    }
        break;

   // case WM_RBUTTONDOWN:
        //mousePos.x = LOWORD(lParam);
        //mousePos.y = HIWORD(lParam);

        //if (PtInRect(&rect, mousePos))
        
    //case WM_RBUTTONUP:
   // {
   //     move = false;
   // }
   // break;

        
    case WM_MOUSEMOVE:
    {
        HDC hdc = GetDC(hWnd);
        if (isMouseLButtonPressed) {
            //선그리기 
            if (changeMode == 0) {
                MoveToEx(hdc, startPoint.x, startPoint.y, NULL);
                startPoint.x = LOWORD(lParam);
                startPoint.y = HIWORD(lParam);
                LineTo(hdc, startPoint.x, startPoint.y);
            }
        }


        ReleaseDC(hWnd, hdc);
    }
        break;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        if (changeMode == 0) {
            text = L"선";
        }
        else if (changeMode == 1) {
            text = L"사각형";
        }
        else if (changeMode == 2) {
            text = L"원";
        }
        TextOut(hdc, 10, 10, text, lstrlen(text));
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
    HWND hButton1, hButton2;

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"ButtonWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        return 1;
    }

    hWnd = CreateWindow(
        L"ButtonWindowClass", L"Win32 Button Example", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        return FALSE;
    }

    hButton1 = CreateWindow(
        L"BUTTON", L"Add Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 100, 200, 60, hWnd, (HMENU)1, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"Remove Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 200, 200, 60, hWnd, (HMENU)2, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}