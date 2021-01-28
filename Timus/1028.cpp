#include <stdio.h>

#define MAXN 32001
#define MAXL 15000

int counter[MAXN];
int level[MAXL];

int Lowbit(int x) {
	return x & (-x);
}

void Update(int x) {
	for (int i = x; i < MAXN; i += Lowbit(i)) {
		counter[i]++;
	}
}

int Sum(int x) {
	int sum = 0;
	for (int i = x; i > 0; i -= Lowbit(i)) {
		sum += counter[i];
	}
	return sum;
}

int main() {
	int n;
	scanf_s("%d", &n);
	for (int i = 0; i < n; ++i) {
		int x, y;
		scanf_s("%d%d", &x, &y);
		level[Sum(++x)] += 1;
		Update(x);
	}
	for (int i = 0; i < n; ++i)
		printf("%d\n", level[i]);
	return 0;
}