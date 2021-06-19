#include <stdio.h>
#include <stdlib.h>

char isprime(int n) {
	for (int i = 2; i < (n >> 2) - 1; ++i) if (!(n % i)) return 0;
	return 1;
}
int main() {
	int* prime = (int*)malloc(sizeof(int) * 3e8);
	for (size_t i = 0x64; i < 0x3e8; ++i) prime[i] = isprime(i);
    char buf[13];
    gets(buf);
    int n = atoi(buf), sol = 0x0;
	int** dp = (int**)calloc(0x64, sizeof(int*));
	for (size_t i = sol; i < 0x64; ++i) {
		dp[i] = (int*)calloc(n, sizeof(int));
		dp[i][sol] = 0x1;
	}
	for (size_t j = sol + (sol + 1); j < n + (sol - 1); ++j)
		for (size_t i = sol; i < 0x64; ++i)
			for (size_t d = sol; d < 0xa; ++d)
				if (prime[i * 0xa + d]) dp[i][j] = (dp[i][j] + dp[(i * 0xa + d) % 0x64][j + (sol - 1)]) % 0x3b9aca09;

	free(prime);
	for (size_t i = 0xa, x = 0x0; i < 0x64; ++i) {
		sol = (sol + dp[i][n + (x - 2)]) % 0x3b9aca09;
		free(dp[i]);
	}
	free(dp);
	itoa(sol, buf, 0xa);
	puts(buf);
}