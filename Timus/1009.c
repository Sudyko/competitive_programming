#include <stdio.h>
#include <stdlib.h>

int numbers(int n, int k) {
    if (n == 0) return 1;
    else if (n == 1) return k - 1;
    else if (n == 2) return k * (k - 1);
    int num1 = k - 1, num2 = k * num1;
    for (int i = 0; i < n - 2; ++i) {
        int tmp = num1;
        num1 = num2;
        num2 = (k - 1) * (tmp + num2);
    }
    return num2;
}

int main() {
    int n, k;
    char buf[10], *ptr;
    gets(buf);
    n = strtol(buf, &ptr, 10);
    gets(buf);
    k = strtol(buf, &ptr, 10);
    itoa(numbers(n, k), buf, 10);
    puts(buf);
    return 0;
}