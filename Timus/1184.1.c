#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    float* nums = (float*)malloc(sizeof(float) * n);
    float sum = 0;
    for (size_t i = 0; i < n; ++i) {
        scanf("%f", &nums[i]);
        sum += nums[i];
    }
    if (sum * 100 / k < 1) {
        puts("0.00");
        return 0;
    }
    sum = floor(sum / k * 100) / 100;
    int have = 0;
    while (have < k) {
        have = 0;
        float max_rest = -0.01;
        int max_i = -1;
        for (size_t i = 0; i < n; ++i) {
            have += (int)(floor(nums[i] / sum));
            float rest = remainder(nums[i], sum);
            if (rest < 0) rest += sum;
            if (rest > max_rest) {
                max_rest = rest;
                max_i = i;
            }
        }
        if (have < k) {
            sum = floor(nums[max_i] / (floor(nums[max_i] / sum) + 1) * 100) / 100;
        }
    }
    printf("%.2f", sum);
    free(nums);
    return 0;
}