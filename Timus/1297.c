#include <stdio.h>
#include <stdlib.h>

char Is_Palindrom(char* str, int len) {
    int iter = (len >> 1) + (len & 1);
    for (int i = 0; i < iter; ++i) {
        if (str[i] != str[len - 1 - i]) return 0;
    }
    return 1;
}

int main() {
    char str[1001];
    int last = -1, letters[58] = { -1 }, ptr_next = 0, ptr_left = 0, ptr_right = 0, len = 1, start = 0, cur_len = 0, ptr_nright;
    scanf("%s", &str);
    while(str[++last]) {
        letters[str[last] - 65] = last;
    }
    --last;
    ptr_nright = letters[str[ptr_next] - 65];
    while (ptr_next < last) {
        if (ptr_nright == -1) {
            ++ptr_next;
            ptr_nright = letters[str[ptr_next] - 65];
        }
        else {
            cur_len = ptr_nright - ptr_next + 1;
            if (cur_len > len) {
                if (Is_Palindrom(&str[ptr_next], cur_len)) {
                    len = cur_len;
                    start = ptr_next;
                    //ptr_next += len >> 1;
                    ptr_next++;
                    ptr_nright = letters[str[ptr_next] - 65];
                }
                else {
                    while (str[--ptr_nright] != str[ptr_next]);
                }
            }
            else {
                ++ptr_next;
                ptr_nright = letters[str[ptr_next] - 65];
            }
        }
    }
    char* tmp = (char*)malloc(sizeof(char)*(len+1));
    tmp[len] = 0;
    for (int i = 0; i < len; ++i) {
        tmp[i] = str[start + i];
    }
    printf("%s", tmp);
    free(tmp);
    return 0;
}