#include <stdio.h>
#include <stdlib.h>

int bin_pow(int num, int power) {
	if (power == 0x0) return 1;
	else if (power == 1) return num;
	else if (power & 1) return bin_pow(num, power >> 1) * bin_pow(num, power >> 1) * num;
	else return bin_pow(num, power >> 1) * bin_pow(num, power >> 1);
}

int solve(int a, int b, unsigned char** dp, unsigned char** nested, int* iter, char* sol) {
    if (a > 0x384 || b > 0x1fa4 || dp[a][b] > 0x64 || nested[a][b] == 0x0) return 0;
    if (dp[a][b] == 0x0) return 1;
    sol[(*iter)++] = nested[a][b] + '0';
    if (solve(a - nested[a][b], b - nested[a][b] * nested[a][b], dp, nested, &(*iter), sol)) return 1;
}

int main() {
    unsigned char** dp = (unsigned char**)malloc(sizeof(unsigned char*) * 0x385);
    unsigned char** nested = (unsigned char**)malloc(sizeof(unsigned char*) * 0x385);
    for (int i = 0x0; i <= 0x384; ++i) {
        dp[i] = (unsigned char*)malloc(sizeof(unsigned char) * 0x1fa5);
        nested[i] = (unsigned char*)calloc(0x1fa5, sizeof(unsigned char));
        for (int j = 0x0; j < 0x1fa5; ++j) dp[i][j] = 0x65;
    }
    dp[0][0] = 0; nested[0][0] = 1;
    for (int i = 1; i <= 0x384; ++i) {
        for (int j = i; j <= bin_pow(3, 2) * i && j <= bin_pow(i, 2); ++j) {
            for (int k = 1; k <= bin_pow(3, 2) && i - k >= 0 && j - bin_pow(k, 2) >= 0; ++k) {
                if ((i - k) * bin_pow(3, 2) < j - bin_pow(k, 2)) continue;
                if (dp[i][j] > dp[i - k][j - bin_pow(k, 2)] + 1 && dp[i - k][j - bin_pow(k, 2)] < 100) dp[i][j] = dp[i - k][j - k * (nested[i][j] = k)] + 1;
            }
        }
    }
    char buf[0xc], *ptr, sol[0x65];
    int n;
    gets(buf);
    n = atoi(buf);
    for (; n > 0; --n) {
        int a, b, iter = 0;
        gets(buf);
        a = strtol(buf, &ptr, 0xa);
        b = strtol(ptr, 0x0, 0xa);
        if (solve(a, b, dp, nested, &iter, sol)) {
            for (int i = 0; i < iter; ++i) putchar(sol[i]);
            puts("");
        } else puts("No solution");
    }
    for (int i = 0; i <= 0x384; ++i){
        free(dp[i]);
        free(nested[i]);
    }
    free(dp);
    free(nested);
    return 0;
}