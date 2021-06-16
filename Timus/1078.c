#include <stdio.h>
#include <stdlib.h>

typedef struct { int first; int second; }Pair;

int less(int a, int i, Pair* segments) {
    if (segments[a].first < segments[i].first) {
        if (segments[i].second < segments[a].second)
            return 1;
    }
    return 0;
}

void solve(int a, int* slv) {
    if (a != -2) {
        solve(slv[a], slv);
        printf("%d ", a);
    }
}

int depthfirstsearch(int a, int** dp, int** slv, Pair** segments, int n) {
    if ((*dp)[a] != -2) return (*dp)[a];
    else (*dp)[a] = 1;
    for (int i = 1; i <= n; ++i) {
        if (i != a && less(a, i, (*segments)) &&  1 + depthfirstsearch(i, dp, slv, segments, n) > (*dp)[a])
            (*dp)[a] = 1 + depthfirstsearch((*slv)[a] = i, dp, slv, segments, n);
    }
    return (*dp)[a];
}

int main() {
    int n, pot = 0, index = 0;
    char buf[13], *ptr;
    gets(buf);
    n = atoi(buf);
    int* dp = (int*)malloc(sizeof(int) * (n + 1));
    int* slv = (int*)malloc(sizeof(int) * (n + 1));
    Pair* segments = (Pair*)malloc(sizeof(Pair) * (n + 1));
    for (int i = 0; i < n + 1; ++i) dp[i] = slv[i] = -2;
    for (int i = 1; i <= n; ++i) {
        gets(buf);
        segments[i].first = strtol(buf, &ptr, 0xa);
        segments[i].second = strtol(ptr, 0, 0xa);
    }
    for (int i = 1; i <= n; ++i) {
        int res = depthfirstsearch(i, &dp, &slv, &segments, n);
        if (res > pot) {
            pot = res;
            index = i;
        }
    }
    free(segments);
    free(dp);
    itoa(pot, buf, 0xa);
    puts(buf);
    solve(index, slv);
    free(slv);
    return 0;
}