#include <stdio.h>

char Is_Palindrom(char* str, int len) {
    int iter = (len >> 1) + (len & 1);
    for (int i = 0; i < iter; ++i) {
        if (str[i] != str[len - 1 - i]) return 0;
    }
    return 1;
}

int main() {
    char str[20001];
    int len = -1, start = 1;
    scanf("%s", &str);
    while (str[++len]);
    while (start < len - 1) {
        if (Is_Palindrom(&str[start], len - start)) {
            break;
        }
        ++start;
    }
    int index = len;
    for (int i = start - 1; i >= 0; --i) {
        str[index++] = str[i];
    }
    str[index] = '\0';
    puts(str);
    return 0;
}