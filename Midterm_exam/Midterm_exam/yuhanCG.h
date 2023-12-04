#pragma once

void DrawBox(HWND hWnd, HDC hdc, int left, int top, int right, int bottom) {

    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    RECT Box = { left, top, right, bottom };

    Rectangle(hdc, Box.left, Box.top, Box.right, Box.bottom);

    MoveToEx(hdc, Box.left, Box.top, NULL);
    LineTo(hdc, Box.left + 30, Box.top - 30);

    MoveToEx(hdc, Box.left + 30, Box.top - 30, NULL);
    LineTo(hdc, Box.right + 30, Box.top - 30);

    MoveToEx(hdc, Box.right, Box.top, NULL);
    LineTo(hdc, Box.right + 30, Box.top - 30);

    MoveToEx(hdc, Box.right + 30, Box.top - 30, NULL);
    LineTo(hdc, Box.right + 30, Box.bottom - 30);

    MoveToEx(hdc, Box.right, Box.bottom, NULL);
    LineTo(hdc, Box.right + 30, Box.bottom - 30);

    SelectObject(hdc, hOldPen); // ���� �� ����
    DeleteObject(hPen); // �� ����

}

void DrawCircle(HWND hWnd, HDC hdc, int left, int top, int right, int bottom)
{
        Ellipse(hdc, left, top, right, bottom);
}

void DrawBonobono(HWND hWnd, HDC hdc, int blink)
{
RECT circle;
GetClientRect(hWnd, &circle);

    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    HBRUSH face = CreateSolidBrush(RGB(127, 200, 255));
    HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
    HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
    HBRUSH mouse = CreateSolidBrush(RGB(255, 150, 255));
    SelectObject(hdc, face);
    Ellipse(hdc, 250, 120, 535, 378);//��
    SelectObject(hdc, mouse);
    Ellipse(hdc, 370, 260, 420, 340);//��

    SelectObject(hdc, white);
    Ellipse(hdc, 340, 255, 395, 300);//�ڿ���
    Ellipse(hdc, 395, 255, 450, 300);//�� ������
    SelectObject(hdc, black);
    Ellipse(hdc, 380, 245, 410, 275);//��
    Ellipse(hdc, 275, 220, 285, 240);//���ʴ�
    Ellipse(hdc, 500, 220, 510, 240);//�����ʴ�
    SelectObject(hdc, white);
    Ellipse(hdc, 277, 223, 283, 230);//���ʴ�
    Ellipse(hdc, 502, 223, 508, 230);//�����ʴ�

    MoveToEx(hdc, 320, 255, NULL); // ���ʼ���1
    LineTo(hdc, 360, 265); // 
    MoveToEx(hdc, 320, 290, NULL); // ���� ����2
    LineTo(hdc, 360, 280); // 

    MoveToEx(hdc, 430, 265, NULL); // ������ ����1
    LineTo(hdc, 470, 255); // 
    MoveToEx(hdc, 430, 280, NULL); // ������ ����2
    LineTo(hdc, 470, 295); // 

    DeleteObject(face);
    DeleteObject(black);
    DeleteObject(white);
    DeleteObject(mouse);
    SelectObject(hdc, hOldPen); // ���� �� ����
    DeleteObject(hPen); // �� ����

if (blink == 1) {


    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    HBRUSH face = CreateSolidBrush(RGB(127, 200, 255));
    HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
    HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
    HBRUSH mouse = CreateSolidBrush(RGB(255, 150, 255));
    SelectObject(hdc, face);
    Ellipse(hdc, 250, 120, 535, 378);//��
    SelectObject(hdc, mouse);
    Ellipse(hdc, 370, 260, 420, 340);//��

    SelectObject(hdc, white);
    Ellipse(hdc, 340, 255, 395, 300);//�ڿ���
    Ellipse(hdc, 395, 255, 450, 300);//�� ������
    SelectObject(hdc, black);
    Ellipse(hdc, 380, 245, 410, 275);//��

    MoveToEx(hdc, 280, 200, NULL); // ���� ��
    LineTo(hdc, 295, 220); // 
    MoveToEx(hdc, 295, 220, NULL); // ���� ��
    LineTo(hdc, 280, 240); // 

    MoveToEx(hdc, 510, 200, NULL); // ������ ��
    LineTo(hdc, 495, 220); // 
    MoveToEx(hdc, 495, 220, NULL); // ������ ��
    LineTo(hdc, 510, 240); // 

    MoveToEx(hdc, 320, 255, NULL); // ���ʼ���1
    LineTo(hdc, 360, 265); // 
    MoveToEx(hdc, 320, 290, NULL); // ���� ����2
    LineTo(hdc, 360, 280); // 

    MoveToEx(hdc, 430, 265, NULL); // ������ ����1
    LineTo(hdc, 470, 255); // 
    MoveToEx(hdc, 430, 280, NULL); // ������ ����2
    LineTo(hdc, 470, 295); // 

    DeleteObject(face);
    DeleteObject(black);
    DeleteObject(white);
    DeleteObject(mouse);
    SelectObject(hdc, hOldPen); // ���� �� ����
    DeleteObject(hPen); // �� ����
}


}


void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom) {

    int faceWidth = right - left;
    int faceHeight = bottom - top;

    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    HBRUSH face = CreateSolidBrush(RGB(255, 200, 15));
    HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
    HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, face);
    //�� �׸���
    int earRadius = faceWidth / 4;  // ���� ������ ����

    // ���� ��
    Ellipse(hdc, left - (earRadius / 2), top - (earRadius / 2), left + (earRadius * 1.5), top + (earRadius * 1.5));

    // ������ �� �׸��� (��Ī)
    Ellipse(hdc, right - (earRadius * 1.5), top - (earRadius / 2), right + (earRadius / 2), top + (earRadius * 1.5));

 


    Ellipse(hdc, left, top, right, bottom);

    SelectObject(hdc, white);
    //���� ��

    int leftNoseLeft = left + (faceWidth / 2) - (faceWidth / 7);
    int leftNoseTop = top + (faceHeight / 2) - (faceHeight / 20);
    int leftNoseRight = left + (faceWidth / 2) + (faceWidth / 150);
    int leftNoseBottom = top + (faceHeight / 2) + (faceHeight / 9);
    Ellipse(hdc, leftNoseLeft, leftNoseTop, leftNoseRight, leftNoseBottom);

    // ������ �� �׸��� (��Ī)
    
    int rightNoseLeft = right - (leftNoseRight - left);
    int rightNoseTop = leftNoseTop;
    int rightNoseRight = right - (leftNoseLeft - left);
    int rightNoseBottom = leftNoseBottom;
    Ellipse(hdc, rightNoseLeft, rightNoseTop, rightNoseRight, rightNoseBottom);
    

    SelectObject(hdc, black);
    // ���� ��
    int leftEyeLeft = left + (faceWidth / 4) + (faceWidth / 20);
    int leftEyeTop = top + (faceHeight / 4) + (faceHeight / 10);
    int leftEyeRight = left + (faceWidth / 5) + (faceWidth / 20);
    int leftEyeBottom = top + (faceHeight / 5) + (faceHeight / 10);
    Ellipse(hdc, leftEyeLeft, leftEyeTop, leftEyeRight, leftEyeBottom);

// ������ �� �׸��� (��Ī)
    int rightEyeLeft = right - ((faceWidth / 4) + (faceWidth / 20));
    int rightEyeTop = leftEyeTop;
    int rightEyeRight = right - ((faceWidth / 5) + (faceWidth / 20));
    int rightEyeBottom = leftEyeBottom;
    Ellipse(hdc, rightEyeLeft, rightEyeTop, rightEyeRight, rightEyeBottom);


    //���� ����
    MoveToEx(hdc, leftEyeLeft - (faceWidth / 6), leftEyeTop - (faceHeight / 13), NULL);
    LineTo(hdc, leftEyeRight + (faceWidth / 10), leftEyeTop - (faceHeight / 13));

    MoveToEx(hdc, leftEyeLeft - (faceWidth / 6), leftEyeTop - (faceHeight / 11), NULL);
    LineTo(hdc, leftEyeRight + (faceWidth / 10), leftEyeTop - (faceHeight / 11));

    MoveToEx(hdc, leftEyeLeft - (faceWidth / 6), leftEyeTop - (faceHeight / 10), NULL);
    LineTo(hdc, leftEyeRight + (faceWidth / 10), leftEyeTop - (faceHeight / 10));

// ������ ����
    MoveToEx(hdc, rightEyeLeft - (faceWidth / 12), rightEyeTop - (faceHeight / 13), NULL);
    LineTo(hdc, rightEyeRight + (faceWidth / 10), rightEyeTop - (faceHeight / 13));

    MoveToEx(hdc, rightEyeLeft - (faceWidth / 12), rightEyeTop - (faceHeight / 11), NULL);
    LineTo(hdc, rightEyeRight + (faceWidth / 10), rightEyeTop - (faceHeight / 11));

    MoveToEx(hdc, rightEyeLeft - (faceWidth / 12), rightEyeTop - (faceHeight / 10), NULL);
    LineTo(hdc, rightEyeRight + (faceWidth / 10), rightEyeTop - (faceHeight / 10));

  

    DeleteObject(black);
    DeleteObject(white);
    DeleteObject(face);
    SelectObject(hdc, hOldPen); // ���� �� ����
    DeleteObject(hPen); // �� ����
}

