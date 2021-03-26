#include <stdlib.h>
#include <stdio.h>

int arr[200];

void swap(int& l, int& r) {
    l ^= r;
    r ^= l;
    l ^= r;
}

int main() {
    int n;
    scanf("%d", &n);
    int counter = 0;
    int count = n;
    for (size_t i = 0; i < n; ++i) {
        char check = 1;
        int l, r;
        scanf("%d %d", &l, &r);
        if (l > r) swap(l, r);
        for(size_t j = 0; j < counter << 1; j += 2) {
            if (arr[j] & 1024) continue;
            if (arr[j] >= l && arr[j + 1] <= r) {
                arr[j] = 1024;
                --count;
            }
            else if(arr[j] <= l && arr[j + 1] >= r) {
                check = 0;
                break;
            }
            else if(arr[j] <= l && arr[j + 1] >= l) {
                if (r - l > arr[j + 1] - arr[j]) {
                    check = 0;
                    break;
                }
                else {
                    arr[j] = 1024;
                    --count;
                }
            } 
            else if(arr[j] <= r && arr[j + 1] >= r) {
                if (r - l > arr[j + 1] - arr[j]) {
                    check = 0;
                    break;
                }
                else {
                    arr[j] = 1024;
                    --count;
                }
            }

        }
        if (check) {
            arr[counter << 1] = l;
            arr[(counter++ << 1) + 1] = r;
        }
    }
    
    return 0;
}