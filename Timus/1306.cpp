#include <stdio.h>
#include <vector>

using namespace std;

vector<unsigned int> nums(0);
int n;

void heapify(int i, int len) {
    int largest = i;
    int a = i * 2 + 1;
    if (a<len && nums[a]>nums[largest]) {
        largest = a;
    }
    if (a + 1 < len && nums[a + 1] > nums[largest]) {
        largest = a + 1;
    }
    if (largest != i) {
        swap(nums[largest], nums[i]);
        heapify(largest, len);
    }
}

void heapSort() {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(i, n);
    }
    for (int i = n - 1; i >= 0; i--) {
        swap(nums[i], nums[0]);
        heapify(0, i);
    }   
}

int main() {
    scanf_s("%d", &n);
    nums.resize(n);
    for (int i = 0; i < n; ++i) {
        scanf_s("%d", &nums[i]);
    }
    heapSort();
    if (n % 2 == 1) {
        printf("%d", nums[(n + 1) / 2 - 1]);
    }
    else {
        printf("%.1f", (nums[n / 2] + nums[n / 2 - 1]) / 2.0);
    }
    return 0;
}