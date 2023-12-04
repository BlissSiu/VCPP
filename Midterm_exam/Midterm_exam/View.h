#pragma once

void ViewBox(HWND hWnd, HDC hdc, RECT viewBox) {

    RECT clientRect;
    GetClientRect(hWnd, &clientRect);
    int padding = 8;

    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    HBRUSH background = CreateSolidBrush(RGB(255, 240, 200));

    viewBox = { clientRect.left + padding, clientRect.top + padding, clientRect.right - padding, clientRect.bottom - padding };

    SelectObject(hdc, background);
    Rectangle(hdc, viewBox.left, viewBox.top, viewBox.right, viewBox.bottom);

    DeleteObject(background);
    SelectObject(hdc, hOldPen); // ¿Ã¿¸ ∆Ê º±≈√
    DeleteObject(hPen); // ∆Ê ªË¡¶
}

void DrawView(HWND hWnd, HDC hdc, RECT drawView) {

    RECT clientRect;
    GetClientRect(hWnd, &clientRect);


    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    HBRUSH background = CreateSolidBrush(RGB(255, 255, 255));

    drawView = { clientRect.left + 16 , clientRect.top + 104 ,clientRect.right - 16, clientRect.bottom - 16 };

    SelectObject(hdc, background);
    Rectangle(hdc, drawView.left, drawView.top, drawView.right, drawView.bottom);

    DeleteObject(background);
    SelectObject(hdc, hOldPen); // ¿Ã¿¸ ∆Ê º±≈√
    DeleteObject(hPen); // ∆Ê ªË¡¶
}