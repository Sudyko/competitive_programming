#include <stdio.h>
#include <stdlib.h>

struct pair { int x; int y; };

void swap(int& a, int& b) {
    a ^= b;
    b ^= a;
    a ^= b;
}

int cmp(const void* l, const void* r) { return (((const pair*)l)->x - ((const pair*)r)->x); }

int main() {
    int n, ptr = 0, count = 1;
    scanf("%d", &n);
    pair* arr = (pair*)malloc(sizeof(pair) * n);
    for (size_t i = 0; i < n; ++i) {
        scanf("%d %d", &arr[i].x, &arr[i].y);
        if (arr[i].x > arr[i].y) swap(arr[i].x, arr[i].y);
    }
    qsort(arr, n, sizeof(pair), cmp);
    for (size_t i = 1; i < n; ++i) {
        if (arr[ptr].y <= arr[i].x) {
            ptr = i;
            ++count;
        }
        else {
            if (arr[ptr].y < arr[i].y) arr[i].x = 0x400;
            else {
                arr[ptr].x = 0x400;
                ptr = i;
            }
        }
    }
    printf("%d\n", count);
    for (size_t i = 0; i < n; ++i) if (arr[i].x ^ 0x400) printf("%d %d\n", arr[i].x, arr[i].y);
    free(arr);
    return 0;
}