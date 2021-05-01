#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    char str[10000000];
    while (n--) {
        scanf("%s", str);
        int len = -1;
        while (str[++len]);
        int ptr = len;
        char flag = 0;
        while (ptr > 0) {
            --ptr;
            if (str[ptr] == 'e') {
                ptr -= 2;
                if (ptr < 0) {
                    flag = 1;
                    break;
                }
                if(strcmp(&str[ptr], "one") == 0) {
                    str[ptr] = '\0';
                }
                else {
                    flag = 1;
                    break;
                }
            }
            else if (str[ptr] == 'n') {
                --ptr;
                if (ptr < 0) {
                    flag = 1;
                    break;
                }
                if(strcmp(&str[ptr], "in") == 0) {
                    str[ptr] = '\0';
                }
                else {
                    ptr -= 3;
                    if (ptr < 0) {
                        flag = 1;
                        break;
                    }
                    if (strcmp(&str[ptr], "puton") == 0) {
                        str[ptr] = '\0';
                    }
                    else {
                        flag = 1;
                        break;
                    }
                }
            }
            else if (str[ptr] == 't') {
                ptr -= 2;
                if (ptr < 0) {
                    flag = 1;
                    break;
                }
                if (strcmp(&str[ptr], "out") == 0) {
                    str[ptr] = '\0';
                }
                else {
                    ptr -= 2;
                    if (ptr < 0) {
                        flag = 1;
                        break;
                    }
                    if (strcmp(&str[ptr], "input") == 0) {
                        str[ptr] = '\0';
                    }
                    else {
                        --ptr;
                        if (ptr < 0) {
                            flag = 1;
                            break;
                        }
                        if (strcmp(&str[ptr], "output") == 0) {
                            str[ptr] = '\0';
                        }
                        else {
                            flag = 1;
                            break;
                        }
                    }
                }
            }
            else {
                flag = 1;
                break;
            }
        }
        if (flag) puts("NO");
        else puts("YES");
    }
    //free(str);
    return 0;
}