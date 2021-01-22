#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int FindMax(vector<int>& nums, int& size) {
    int max = 0;
    for (int i = 0; i < size; ++i) {
        if (nums[i] > max) {
            max = nums[i];
        }
    }
    return max;
}

int main() {
    int n, num;
    cin >> n;
    vector<int> source_input = {};
    while (cin >> num) {
        if (num == -1) break;
        source_input.push_back(num);
    }
    while (n) {
        if (source_input.size() == n - 1) return 0;
        cout << FindMax(source_input, n) << endl;
        source_input.erase(source_input.begin());
    }
    return 0;
}