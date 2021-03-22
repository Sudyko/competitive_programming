#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long u_long;

int main() {
	u_long n, q;
	scanf("%lld", &n);
	u_long* charges = (u_long*)malloc(sizeof(u_long) * n);
	for (u_long i = 0; i < n; ++i) scanf("%lld", &charges[i]);
	scanf("%lld", &q);
	for (q; q > 0; --q) {
		u_long k, l, r, d;
		scanf("%lld", &k);
		if (k & 1) {
			scanf("%lld", &l);
			printf("%lld\n", charges[l - 1]);
		}
		else {
			scanf("%lld %lld %lld", &l, &r, &d);
			for (u_long j = l; j <= r; ++j) {
				u_long tmp = n / j * j;
				for (u_long k = j; k <= tmp; k += j)
					charges[k - 1] += d;
			}
		}
	}
	free(charges);
	return 0;
}