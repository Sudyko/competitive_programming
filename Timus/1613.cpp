#include <stdio.h>
#include <stdlib.h>

int __fastcall BinarySearch(long*& array, int array_size, int key)
{
	unsigned int bot, mid, top;

	bot = 0;
	top = array_size;

	while (top > 1) {
		mid = top / 2;
		if (key >= array[bot + mid])
			bot += mid;
		top -= mid;
	}
	if (key == array[bot])
		return bot;
	return -1;
}

bool __fastcall FindElement(long*& arr, int size, int key) {
	int low = 0, high = size - 1;
	if (BinarySearch(arr, size, key) == -1) return false;
	else return true;
}

void __fastcall swap(long& a, long& b) {
	long tmp = a;
	a = b;
	b = tmp;
}

int __fastcall partition(long*& nums, int start, int end) {
	long pivot = nums[(start + end) / 2];
	while (start <= end) {
		while (nums[start] < pivot)
			start++;
		while (nums[end] > pivot)
			end--;
		if (start >= end)
			break;
		swap(nums[start++], nums[end--]);
	}
	return end;
}

int __fastcall quicksort(long*& nums, int start, int end) {
	if (start >= end)
		return 0;
	int q = partition(nums, start, end);
	quicksort(nums, start, q);
	quicksort(nums, q + 1, end);
}

int main() {
	int n;
	scanf_s("%d", &n);
	int* nums = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; ++i) {
		scanf_s("%ld", &nums[i]);
	}

	scanf_s("%d", &n);
	bool* result = (bool*)malloc(n * sizeof(bool));
	for (int i = 0; i < n; ++i) {
		int l, r;
		long x;
		bool check = true;

		scanf_s("%d %d %ld", &l, &r, &x);

		if (r == l) {
			if (nums[r - 1] == x)
				result[i] = 1;
			else
				result[i] = 0;
			check = false;
		}

		if (check) {
			long* triplet = (long*)malloc((r - l + 1) * sizeof(long));
			int k = 0;
			for (int j = l - 1; j < r; ++j, ++k) {
				triplet[k] = nums[j];
			}

			quicksort(triplet, 0, r - l);

			if (FindElement(triplet, r - l + 1, x))
				result[i] = 1;
			else
				result[i] = 0;
			free(triplet);
		}
	}
	free(nums);
	for (int i = 0; i < n; ++i) {
		printf("%d", result[i]);
	}
	free(result);
	return 0;
}