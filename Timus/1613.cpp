#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int>> cities;

int comp(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first) return a.second < b.second;
    return a.first < b.first;
}

int main() {
    int n;
    scanf("%d", &n);
    for (size_t i = 0; i < n; ++i) {
        int num;
        scanf("%d", &num);
        cities.push_back(make_pair(num, i + 1));
    }
    sort(cities.begin(), cities.end());
    scanf("%d", &n);
    for (size_t i = 0; i < n; ++i) {
        int l, r, x;
        scanf("%d %d %d", &l, &r, &x);
        int left_bound = lower_bound(cities.begin(), cities.end(), make_pair(x, l), comp) - cities.begin();
        int right_bound = upper_bound(cities.begin(), cities.end(), make_pair(x, r), comp) - cities.begin();
        printf("%d", left_bound < right_bound);
    }
    return 0;
}
