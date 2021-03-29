#include <stdio.h>
#include <stdlib.h>

struct pair { int x; int y; };

int cmp(const void* l, const void* r) { return (((const pair*)l)->x - ((const pair*)r)->x); }

int main() {
    int m = 0, a = 0, b = 0, size = 0;
    scanf("%d", &m);
    pair* arr = (pair*)malloc(sizeof(pair) * 100000);
    do {
        scanf("%d %d", &a, &b);
        if (b <= 0 || a >= m) continue;
        arr[size].x = a;
        arr[size++].y = b;
    } while (!(a == 0 && b == 0));
    arr = (pair*)realloc(arr, sizeof(pair) * size);
    qsort(arr, size, sizeof(pair), cmp);
    int prev = -1, ptr = 0, i = 0, count = 1;
    if (size == 0 || arr[0].x > 0) goto finish;
    while (arr[i].y < m && ++i < size) {
        if (arr[ptr].y < arr[i].x) goto finish;
        else {
            if (arr[ptr].y < arr[i].y) {
                if (arr[i].x <= 0 || (prev != -1 && (arr[prev].y >= arr[i].x))) arr[ptr].x = 0x10000;
                else { ++count; prev = ptr; }
                ptr = i;
            }
            else arr[i].x = 0x10000;
        }
    }
    size = ++i;
    if (prev != -1 && arr[prev].y >= m) {
        --count;
        size = ++prev;
    }
    if (arr[size - 1].y < m) goto finish;
    printf("%d\n", count);
    for (size_t i = 0; i < size; ++i) if (arr[i].x ^ 0x10000) printf("%d %d\n", arr[i].x, arr[i].y);
    free(arr);
    return 0;
    finish:
    puts("No solution");
    free(arr);
    return 0;
}