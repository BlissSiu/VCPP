
#include <stdio.h>
#include <conio.h>
#include <string.h>

int main() {
    char input[100] = "";
    int i = 0;
    char ch;

    while (1) {
        printf("Command>");

        while (1) {
            ch = getch();

            if (ch == '\r') {
                input[i] = '\0';
                break;
            }
            else if (ch == 27) {
                return 0;
            }
            else {
                input[i] = ch;
                printf("%c", ch);
                i++;
            }
        }

        printf("\n");

        if (strcmp(input, "q") == 0) {
            printf("qwer ȭ����\n");
        }
        else if (strcmp(input, "w") == 0) {
            printf("���� �ʹ� ����\n");
        }
        else if (strcmp(input, "e") == 0) {
            printf("���ֺ��� ������ 3���\n");
        }
        else if (strcmp(input, "r") == 0) {
            printf("�ູ�մϴ�.\n");
        }
        else {
            printf("�ٽ� �Է��� �ּ���\n");
        }

        memset(input, 0, sizeof(input));
        i = 0;
    }

}
