#include <stdio.h>
#include <stack>

using namespace std;

int main() {
	int n, rev, max = 0;
	stack<int> nums;
	nums.push(0);
	scanf("%d", &n);
	for (; n > 0; --n) {
		scanf("%d", &rev);
		if (rev < nums.top()) break;
		else if (rev == nums.top()) nums.pop();
		else if (rev > max) {
			for (int j = max + 1; j <= rev; ++j) nums.push(j);
			max = rev;
			nums.pop();
		}
	}
	if (rev < nums.top()) puts("Cheater");
	else puts("Not a proof");
	return 0;
}
