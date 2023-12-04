
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
            printf("qwer 화이팅\n");
        }
        else if (strcmp(input, "w") == 0) {
            printf("과제 너무 좋다\n");
        }
        else if (strcmp(input, "e") == 0) {
            printf("담주부턴 과제량 3배다\n");
        }
        else if (strcmp(input, "r") == 0) {
            printf("행복합니다.\n");
        }
        else {
            printf("다시 입력해 주세요\n");
        }

        memset(input, 0, sizeof(input));
        i = 0;
    }

}
