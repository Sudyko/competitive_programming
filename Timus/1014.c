#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d", &n);
    int n2 = 0, n3 = 0, n5 = 0, n7 = 0;
    if (n == 0) puts("10");
    else if (n<10) printf("%d", n);
    else {
        char flag = 0;
        while (n != 1) {
            if (!(n & 1)) {
                ++n2;
                n >>= 1;
            } else if (n % 3 == 0) {
                ++n3;
                n /= 3;
            } else if (n % 5 == 0) {
                ++n5;
                n /= 5;
            } else if (n % 7 == 0) {
                ++n7;
                n /= 7;
            } else n = flag = 1;
        }
        if (flag) {
            puts("-1");
            return 0;
        } else {
            int len = 0;
            char* str = (char*)malloc(sizeof(char));;
            while (n3 >> 1){
                ++len;
                realloc(str, sizeof(char) * len);
                str[len - 1] = '9';
                n3 -= 2;
            }
            while (n2 / 3) {
                ++len;
                realloc(str, sizeof(char) * len);
                str[len - 1] = '8';
                n2 -= 3;
            }
            while (n7) {
                ++len;
                realloc(str, sizeof(char) * len);
                str[len - 1] = '7';
                --n7;
            } 
            if (n3 && n2) {
                ++len;
                realloc(str, sizeof(char) * len);
                str[len - 1] = '6';
                --n3;
                --n2;
            } 
            while (n5) {
                ++len;
                realloc(str, sizeof(char) * len);
                str[len - 1] = '5';
                --n5;
            } 
            if (n2 == 2) {
                ++len;
                realloc(str, sizeof(char) * len);
                str[len - 1] = '4';
                n2 = 0;
            } 
            if (n3) {
                ++len;
                realloc(str, sizeof(char) * len);
                str[len - 1] = '3';
            } 
            if (n2) {
                ++len;
                realloc(str, sizeof(char) * len);
                str[len - 1] = '2';
            } 
            char* reverse = (char*)malloc(sizeof(char) * (len + 1));
            for (int i = len - 1; i >= 0; --i) reverse[len - i - 1] = str[i];
            reverse[len] = '\0';
            printf("%s", reverse);
        }
    }
    return 0;
}