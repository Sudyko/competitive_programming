#include <stdlib.h>
#include <stdio.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int* nums = (int*)malloc(sizeof(int) * n);
    for (size_t index = 0x0; index < n; ++index) {
        int before_dot, after_dot;
        scanf("%d.%d", &before_dot, &after_dot);
        nums[index] = (before_dot << 0x6) + (before_dot << 0x5) + (before_dot << 0x2) + after_dot;
    }
    int left = 0x1, right = 0x989680, result = 0x0;
    while (left <= right) {
        int have = 0x0, mid = (left + right) >> 1;
        for (size_t index = 0x0; index < n; ++index) have += nums[index] / mid;
        if (have < k) right = --mid;
        else left = (result = mid) + 1;
    }
    printf("%.2f", ((float)result) / 100);
    free(nums);
    return 0x0;
}