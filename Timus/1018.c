#include <stdio.h>
#include <stdlib.h>

typedef struct { int first; int second; }Pair;

int dfs(int a, int b, int* sizes, int n, int* tree, Pair** nodes, int** pre) {
    for (int i = 0; i < sizes[a]; ++i) {
		if (nodes[a][i].first != b) tree[a] += dfs(nodes[a][i].first, a, sizes, n, tree, nodes, pre);
	}
    for (int i = 0; i < sizes[a]; ++i) {
		int v = nodes[a][i].first, w = nodes[a][i].second;
		if (v != b)
            for (int i = tree[a]; i > 0; --i)
                for (int j = 1; j < i && j <= tree[v]; ++j)
                    pre[a][i] = (pre[a][i]) > (pre[a][i - j] + w + pre[v][j]) ? pre[a][i] : (pre[a][i - j] + w + pre[v][j]);
	}
	return tree[a];
}

int main() {
    char buf[0xd], *ptr;
    int n, q, u, v, w;
	gets(buf);
    n = strtol(buf, &ptr, 0xa);
	q = strtol(ptr, 0, 0xa);
    int* tree = (int*)calloc(++n, sizeof(int));
    int* sizes = (int*)calloc(n, sizeof(int));
    Pair** nodes = (Pair**)calloc(n, sizeof(Pair*));
    int** pre = (int**)calloc(n, sizeof(int*));
    for (int i = 0; i < n; ++i) {
        pre[i] = (int*)calloc(n, sizeof(int));
        ++tree[i];
    }
    for (int i = 0; i < n - 2; ++i) {
        gets(buf);
        u = strtol(buf, &ptr, 0xa);
        v = strtol(ptr, &ptr, 0xa);
        w = strtol(ptr, 0, 0xa);
        nodes[u] = (Pair*)realloc(nodes[u], ++sizes[u] * sizeof(Pair));
        nodes[u][sizes[u] - 1].first = v; nodes[u][sizes[u] - 1].second = w;
        nodes[v] = (Pair*)realloc(nodes[v], ++sizes[v] * sizeof(Pair));
        nodes[v][sizes[v] - 1].first = u; nodes[v][sizes[v] - 1].second = w;
    }
    dfs(1, -1, sizes, n, tree, nodes, pre);
    puts(itoa(pre[1][++q], buf, 10));
    for (int i = 0; i < n; ++i) {
        free(nodes[i]);
        free(pre[i]);
    }
    free(nodes);
    free(pre);
    free(tree);
    free(sizes);
    return 0;
}