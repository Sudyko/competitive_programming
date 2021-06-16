	#include <stdio.h>
	#include <stdlib.h>

	typedef struct { int idx, weight; }Node;

	void dfs(int from, int u, int level, Node** nodes, int* sizes, int* ancestor, int** lvls, int** len) {
		(*lvls)[u] = level;
		for (int i = 0, v; i < sizes[u]; ++i) {
			if (nodes[u][i].idx == (ancestor[u] = from)) continue;
			(*len)[nodes[u][i].idx] = (*len)[u] + nodes[u][i].weight;
			dfs(u, nodes[u][i].idx, level + 1, nodes, sizes, ancestor, lvls, len);
		}
	}

	void initLCA(int n, int* ancestor, int** slab) {
		for (int i = 0; i < n; ++i) slab[i][0] = ancestor[i];
		for (int j = 1; (1 << j) < n; ++j) 
			for (int i = 0; i < n; ++i) if (slab[i][j - 1] != -3) slab[i][j] = slab[slab[i][j - 1]][j - 1];
	}

	int LCA(int u, int v, int* ancestor, int* lvls, int** slab) {
		int jmp = 1;
		if (lvls[u] < lvls[v]) { u ^= v ^= u ^= v; } // swap
		do { if ((1 << (jmp + 1)) > lvls[u]) break; } while (++jmp);
		for (int i = jmp; i >= 0; --i) if (lvls[u] - (1 << i) >= lvls[v]) u = slab[u][i];
		if((u ^ v) == 0) return v;
		for (; jmp >= 0; --jmp) {
			if (slab[u][jmp] != slab[v][jmp] && slab[u][jmp] != -3) {
				u = slab[u][jmp];
				v = slab[v][jmp];
			}
		}
		return ancestor[u];
	}

	int main() {
		int n, q, u, v, w;
		char buf[0xd], *ptr;
		gets(buf);
		n = atoi(buf);
		Node** nodes = (Node**)calloc(n, sizeof(Node*));
		int* sizes = (int*)calloc(n, sizeof(int));
		for (size_t i = 0; i < n - 1; ++i) {
			gets(buf);
			u = strtol(buf, &ptr, 0xa);
			v = strtol(ptr, &ptr, 0xa);
			w = strtol(ptr, 0, 0xa);
			nodes[u] = (Node*)realloc(nodes[u], ++sizes[u] * sizeof(Node));
        	nodes[u][sizes[u] - 1].idx = v; nodes[u][sizes[u] - 1].weight = w;
			nodes[v] = (Node*)realloc(nodes[v], ++sizes[v] * sizeof(Node));
			nodes[v][sizes[v] - 1].idx = u; nodes[v][sizes[v] - 1].weight = w;
		}
		int* ancestor = (int*)calloc(n, sizeof(int));
		int* lvls = (int*)calloc(n, sizeof(int));
		int* len = (int*)calloc(n, sizeof(int));
		dfs(0x0, 0x0, 0x0, nodes, sizes, ancestor, &lvls, &len);
		int** slab = (int**)calloc(n, sizeof(int*));
		for (int i = 0; i < n; ++i) {
			slab[i] = (int*)calloc(1 << 4, sizeof(int));
			for (int j = 0; j < 1 << 4; ++j) slab[i][j] = -3;
			free(nodes[i]);
		}
		free(nodes);
		free(sizes);
		initLCA(n, ancestor, slab);
		gets(buf);
		q = atoi(buf);
		for (;q > 0; --q) {
			gets(buf);
			u = strtol(buf, &ptr, 0xa);
			v = strtol(ptr, 0x0, 0xa);
			printf("%d\n", len[v] - (len[LCA(u, v, ancestor, lvls, slab)] << 1) + len[u]);
		}
		for (int i = 0; i < n; ++i) free(slab[i]);
		free(slab);
		free(len);
		free(lvls);
		free(ancestor);
		return 0;
	}