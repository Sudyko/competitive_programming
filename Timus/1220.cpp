#include <stdio.h>

#define MAX_STACKS 1000
#define MAX_OPS 100001

int values[MAX_OPS];
int stack_ptr[MAX_STACKS];
unsigned short int counter[MAX_OPS];

int main() {
	int n;
	int ptr = 0;
	scanf_s("%d", &n);
	for (int i = 0; i < n; ++i) {
		char str[5];
		int a;
		scanf_s("%s %d", str, 5, &a);
		a -= 1;
		if (str[2] == 'S') {
			int b;
			scanf_s("%d", &b);
			values[ptr] = b;
			counter[ptr] = ptr - stack_ptr[a];
			stack_ptr[a] = ptr;
			ptr += 1;
		}
		else {
			printf("%d\n", values[stack_ptr[a]]);
			stack_ptr[a] = stack_ptr[a] - counter[stack_ptr[a]];
		}
	}
	return 0;
}