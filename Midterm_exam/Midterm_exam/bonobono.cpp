#include <windows.h>

bool isPressButton = false;
bool isPressSpace = false;

RECT viewBox = { 0 };
RECT drawBox = { 0 };

void drawbonobono(HWND hWnd, HDC hdc) {
    RECT circle;
    GetClientRect(hWnd, &circle);

    if (isPressButton) {
        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
        HBRUSH face = CreateSolidBrush(RGB(127, 200, 255));
        HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
        HBRUSH mouse = CreateSolidBrush(RGB(255, 150, 255));
        SelectObject(hdc, face);
        Ellipse(hdc, 250, 120, 535, 378);//얼굴
        SelectObject(hdc, mouse);
        Ellipse(hdc, 370, 260, 420, 340);//입

        SelectObject(hdc, white);
        Ellipse(hdc, 340, 255, 395, 300);//코왼쪽
        Ellipse(hdc, 395, 255, 450, 300);//코 오른쪽
        SelectObject(hdc, black);
        Ellipse(hdc, 380, 245, 410, 275);//코
        Ellipse(hdc, 275, 220, 285, 240);//왼쪽눈
        Ellipse(hdc, 500, 220, 510, 240);//오른쪽눈
        SelectObject(hdc, white);
        Ellipse(hdc, 277, 223, 283, 230);//왼쪽눈
        Ellipse(hdc, 502, 223, 508, 230);//오른쪽눈

        MoveToEx(hdc, 320, 255, NULL); // 왼쪽수염1
        LineTo(hdc, 360, 265); // 
        MoveToEx(hdc, 320, 290, NULL); // 왼쪽 수염2
        LineTo(hdc, 360, 280); // 

        MoveToEx(hdc, 430, 265, NULL); // 오른쪽 수염1
        LineTo(hdc, 470, 255); // 
        MoveToEx(hdc, 430, 280, NULL); // 오른쪽 수염2
        LineTo(hdc, 470, 295); // 

        DeleteObject(face);
        DeleteObject(black);
        DeleteObject(white);
        DeleteObject(mouse);
        SelectObject(hdc, hOldPen); // 이전 펜 선택
        DeleteObject(hPen); // 펜 삭제
    }
    if (isPressButton == true && isPressSpace == true) {


        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
        HBRUSH face = CreateSolidBrush(RGB(127, 200, 255));
        HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
        HBRUSH mouse = CreateSolidBrush(RGB(255, 150, 255));
        SelectObject(hdc, face);
        Ellipse(hdc, 250, 120, 535, 378);//얼굴
        SelectObject(hdc, mouse);
        Ellipse(hdc, 370, 260, 420, 340);//입

        SelectObject(hdc, white);
        Ellipse(hdc, 340, 255, 395, 300);//코왼쪽
        Ellipse(hdc, 395, 255, 450, 300);//코 오른쪽
        SelectObject(hdc, black);
        Ellipse(hdc, 380, 245, 410, 275);//코

        MoveToEx(hdc, 280, 200, NULL); // 왼쪽 눈
        LineTo(hdc, 295, 220); // 
        MoveToEx(hdc, 295, 220, NULL); // 왼쪽 눈
        LineTo(hdc, 280, 240); // 

        MoveToEx(hdc, 510, 200, NULL); // 오른쪽 눈
        LineTo(hdc, 495, 220); // 
        MoveToEx(hdc, 495, 220, NULL); // 오른쪽 눈
        LineTo(hdc, 510, 240); // 

        MoveToEx(hdc, 320, 255, NULL); // 왼쪽수염1
        LineTo(hdc, 360, 265); // 
        MoveToEx(hdc, 320, 290, NULL); // 왼쪽 수염2
        LineTo(hdc, 360, 280); // 

        MoveToEx(hdc, 430, 265, NULL); // 오른쪽 수염1
        LineTo(hdc, 470, 255); // 
        MoveToEx(hdc, 430, 280, NULL); // 오른쪽 수염2
        LineTo(hdc, 470, 295); // 

        DeleteObject(face);
        DeleteObject(black);
        DeleteObject(white);
        DeleteObject(mouse);
        SelectObject(hdc, hOldPen); // 이전 펜 선택
        DeleteObject(hPen); // 펜 삭제
    }
    
    
}
void ViewBox(HWND hWnd, HDC hdc) {

    RECT clientRect;
    GetClientRect(hWnd, &clientRect);
    int padding = 8;

    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    HBRUSH background = CreateSolidBrush(RGB(255, 240, 200));

    viewBox = { clientRect.left+padding, clientRect.top+padding, clientRect.right-padding, clientRect.bottom-padding };
    
    SelectObject(hdc, background);
    Rectangle(hdc, viewBox.left, viewBox.top, viewBox.right, viewBox.bottom);

    DeleteObject(background);
    SelectObject(hdc, hOldPen); // 이전 펜 선택
    DeleteObject(hPen); // 펜 삭제
}

void DrawBox(HWND hWnd, HDC hdc) {

    RECT clientRect;
    GetClientRect(hWnd, &clientRect);


    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    HBRUSH background = CreateSolidBrush(RGB(255, 255, 255));

    drawBox = { clientRect.left + 16 , clientRect.top + 104 ,clientRect.right - 16, clientRect.bottom - 16 }; 

    SelectObject(hdc, background);
    Rectangle(hdc, drawBox.left, drawBox.top, drawBox.right, drawBox.bottom);

    DeleteObject(background);
    SelectObject(hdc, hOldPen); // 이전 펜 선택
    DeleteObject(hPen); // 펜 삭제
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    switch (message) {
    case WM_COMMAND:
    {
        //박스 클릭
        if (LOWORD(wParam) == 1) {
            isPressButton = false;
            InvalidateRect(hWnd, NULL, TRUE);

        }
        //원 클릭
        if (LOWORD(wParam) == 2)
        {
            isPressButton = false;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        // 보노보노클릭
        if (LOWORD(wParam) == 3)
        {
            isPressButton = true;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        //라이언클릭
        if (LOWORD(wParam) == 4)
        {
            isPressButton = false;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        //큐브클릭
        if (LOWORD(wParam) == 5)
        {
            isPressButton = false;
            InvalidateRect(hWnd, NULL, TRUE);
        }
    }
    break;

    case WM_SETCURSOR:
    {
        POINT mousePos;
        GetCursorPos(&mousePos);
        ScreenToClient(hWnd, &mousePos);
        
        if (PtInRect(&drawBox, mousePos)) {
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

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        ViewBox(hWnd, hdc);
        DrawBox(hWnd, hdc);
        drawbonobono(hWnd, hdc);
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
        16, 16, 137, 64 + 8 * 2 , hWnd, (HMENU)1, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        137 + 16*2, 16 , 137, 64 + 8 * 2, hWnd, (HMENU)2, hInstance, NULL);

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

