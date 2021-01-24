#include <stdio.h>
#include <stdlib.h>
#include <stack>

using namespace std;

int main() {
	stack<int> nums;
	nums.push(0);
	bool check = true;
	int n;
	int max = 0;
	scanf_s("%d", &n);
	for (int i = 0; i < n; ++i) {
		int rev;
		scanf_s("%d", &rev);
		if (rev < nums.top())
			check = false;
		else if (rev == nums.top())
			nums.pop();
		else if (rev > max) {
			for (int j = max + 1; j <= rev; ++j) {
				nums.push(j);
			}
			max = rev;
			nums.pop();
		}
	}
	if (check)
		printf("Not a proof");
	else
		printf("Cheater");
	return 0;
}