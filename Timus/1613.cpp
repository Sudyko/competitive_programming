#include <stdio.h>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

vector<pair<int, int>> cities;

int comp(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first)
        return a.second < b.second;
    return a.first < b.first;
}

int main() {
    int n;
    scanf_s("%d", &n);
    for (int i = 0; i < n; ++i) {
        int num;
        scanf_s("%d", &num);
        cities.push_back(make_pair(num, i + 1));
    }
    sort(cities.begin(), cities.end());
    int q;
    scanf_s("%d", &q);
    vector<int> result;
    for (int i = 0; i < q; ++i) {
        int l, r, x;
        scanf_s("%d %d %d", &l, &r, &x);
        int left_bound = lower_bound(cities.begin(), cities.end(), make_pair(x, l), comp) - cities.begin();
        int right_bound = upper_bound(cities.begin(), cities.end(), make_pair(x, r), comp) - cities.begin();
        result.push_back(left_bound < right_bound);
    }
    for (int i = 0; i < q; ++i) {
        printf("%d", result[i]);
    }
    return 0;
}
