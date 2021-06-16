#include <stdio.h>
#include <stdlib.h>

int bin_pow(int num, int power) {
	if (power == 0) return 1;
	else if (power == 1) return num;
	else if (power & 1) return bin_pow(num, power >> 1) * bin_pow(num, power >> 1) * num;
	else return bin_pow(num, power >> 1) * bin_pow(num, power >> 1);
}

int main() {
    char buf[13], *ptr;
    int n;
    gets(buf);
    n = atoi(buf);
    int* dp = (int*)calloc(n + 1, sizeof(int));
    for(int i = 1, bound = 0xea60; i < n + 1; ++i) {
        int index = 1;
        while (bin_pow(index, 2) <= i) {
            if (dp[i - bin_pow(index, 2)] < bound) bound = dp[i - bin_pow(index, 2)];
            ++index;
        }
        dp[i] = (++bound);
    }
    itoa(dp[n], buf, 0xa);
    free(dp);
    puts(buf);
    return 0;
}