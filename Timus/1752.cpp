#include <stdio.h>
#include <stdlib.h>

typedef struct { int left, right; } PAIR;

typedef struct { int *val; int size; } Stack;

int stack_pop(Stack* stack) {
    int result = (*stack).val[--((*stack).size)];
    (*stack).val = (int*)realloc((*stack).val, (*stack).size * sizeof(int));
    return result;
}

int stack_top(Stack* stack) {
    return (*stack).val[(*stack).size - 1];
}

void stack_push(Stack* stack, int num) {
    (*stack).val = (int*)realloc((*stack).val, ++((*stack).size) * sizeof(int));
    (*stack).val[(*stack).size - 1] = num;
}

void swap(int& a, int& b) { a ^= b ^= a ^= b; }

void swap_pair(PAIR* a, PAIR* b) {
    (*a).left ^= (*b).left ^= (*a).left ^= (*b).left;
    (*a).right ^= (*b).right ^= (*a).right ^= (*b).right;
}

void dfs(int current, int previous, int lvl, int** tree, int* sizes, PAIR** flow, int** level, int** PTR, int n) {
    
    int cur_lvl = 0, last_pop = 0;
    char* visited = (char*)calloc(n + 1, sizeof(char));
    Stack nexts = { 0, 0 };
    stack_push(&nexts, current);
    while (nexts.size) {
        int next = stack_top(&nexts);
        int prv = nexts.size > 1 ? nexts.val[nexts.size - 2] : -1;
        
        if (visited[next] == 0) {
            visited[next] = 1;
            flow[next][0] = { next, 0 };
            flow[next][1] = { 0, 0 };
        }
        else {
            if (1 + flow[last_pop][0].right > flow[next][1].right) {
                flow[next][1] = flow[last_pop][0];
                ++flow[next][1].right;

                if (flow[next][1].right > flow[next][0].right)
                    swap_pair(&flow[next][0], &flow[next][1]);
            }
        }
        PTR[0][next] = prv;
        (*level)[next] = cur_lvl;
        char flag = 0;
        for (int i = sizes[next] - 1, nxt; i >= 0; --i) {
            nxt = tree[next][i];
            if (visited[nxt] == 0) {
                stack_push(&nexts, nxt);
                flag = 1;
                ++cur_lvl;
                break;
            }
        }
        if (flag) continue;
        last_pop = stack_pop(&nexts);
        --cur_lvl;
    }
    free(visited);
}

void dfs2(int current, int prev, int** tree, int* sizes, PAIR** flow, PAIR** parent, int n) {
    char* visited = (char*)calloc(n + 1, sizeof(char));
    Stack nexts = { 0, 0 };
    stack_push(&nexts, current);
    while (nexts.size) {
        int next = stack_top(&nexts);
        int prv = nexts.size > 1 ? nexts.val[nexts.size - 2] : -1;
        if (visited[next] == 0) {
            parent[next][0] = flow[next][0];
            parent[next][1] = flow[next][1];
            if (prv != -1) {
                for (int i = 0; i < 2; ++i) {
                    if (parent[prv][i].left != flow[next][0].left) {
                        if (1 + parent[prv][i].right > parent[next][1].right) {
                            parent[next][1] = parent[prv][i];
                            ++parent[next][1].right;
                        }

                        if (parent[next][1].right > parent[next][0].right)
                            swap_pair(&parent[next][0], &parent[next][1]);
                        break;
                    }
                }
            }
            visited[next] = 1;
        }
        char flag = 0;
        for (int i = sizes[next] - 1, nxt; i >= 0; --i) {
            nxt = tree[next][i];
            if (visited[nxt] == 0) {
                flag = 1;
                stack_push(&nexts, nxt);
                break;
            }
        }
        if (flag) continue;
        stack_pop(&nexts);
    }
    free(visited);
}

PAIR LCA(int x, int y, int* level, int** PTR) {
    if (level[x] < level[y]) swap(x, y);

    int dist = level[x] - level[y];

    for (int i = 14; i >= 0; --i)
        if (dist & (1 << i))
            x = PTR[i][x];

    for (int i = 14; i >= 0; --i) {
        if (PTR[i][x] != PTR[i][y]) {
            dist += (1 << (i + 1));
            x = PTR[i][x];
            y = PTR[i][y];
        }
    }

    if (x != y) {
        x = PTR[0][x];
        y = PTR[0][y];
        dist += 2;
    }
    return { x, dist };
}

int upword(int x, int d, int** PTR) {
    for (int i = 0; i <= 14; ++i, d >>= 1)
        if (d & 1) x = PTR[i][x];
    return x;
}

int main() {
    int n, q, u, v;
    char buf[13], * ptr;
    fgets(buf, 13, stdin);
    n = strtol(buf, &ptr, 10);
    int** tree = (int**)calloc(n + 1, sizeof(int*));
    int* sizes = (int*)calloc(n + 1, sizeof(int));

    q = strtol(ptr, 0, 10);
    for (int i = 1; i < n; ++i) {
        fgets(buf, 13, stdin);
        u = strtol(buf, &ptr, 10);
        v = strtol(ptr, 0, 10);
        tree[u] = (int*)realloc(tree[u], ++sizes[u] * sizeof(int));
        tree[u][sizes[u] - 1] = v;
        tree[v] = (int*)realloc(tree[v], ++sizes[v] * sizeof(int));
        tree[v][sizes[v] - 1] = u;
    }
    PAIR** flow = (PAIR**)calloc(n + 1, sizeof(PAIR*));
    PAIR** parent = (PAIR**)calloc(n + 1, sizeof(PAIR*));
    for (int i = 0; i <= n; ++i) {
        flow[i] = (PAIR*)calloc(2, sizeof(PAIR));
        parent[i] = (PAIR*)calloc(2, sizeof(PAIR));
    }
    int** PTR = (int**)calloc(15, sizeof(int*));
    for (int i = 0; i < 15; ++i) {
        PTR[i] = (int*)calloc(n + 1, sizeof(int));
    }
    int* level = (int*)calloc(n + 1, sizeof(int));

    dfs(1, -1, 0, tree, sizes, flow, &level, PTR, n);
    dfs2(1, -1, tree, sizes, flow, parent, n);
    for (int i = 0; i <= n; ++i) free(tree[i]);
    free(tree);
    free(sizes);
    for (int i = 1; (1 << i) < n; ++i) // initialization of lca
        for (int j = 1; j <= n; ++j)
            if (PTR[i - 1][j] != -1)
                PTR[i][j] = PTR[i - 1][PTR[i - 1][j]];

    int* to = (int*)calloc(n + 1, sizeof(int));
    for (int i = 1; i <= n; ++i)
        to[i] = parent[i][0].left;
    for (int i = 0; i <= n; ++i) {
        free(flow[i]);
        free(parent[i]);
    }
    free(flow);
    free(parent);
    int* dest = (int*)calloc(n + 1, sizeof(int));
    int* final_dest = (int*)calloc(n + 1, sizeof(int));
    for (int i = 1; i <= n; ++i) {
        PAIR aux = LCA(i, to[i], level, PTR);

        dest[i] = level[i] - level[aux.left];
        final_dest[i] = level[to[i]] - level[aux.left];
    }
    free(level);
    for (int i = 0, x, d; i < q; ++i) {
        fgets(buf, 13, stdin);
        x = strtol(buf, &ptr, 10);
        d = strtol(ptr, 0, 10);

        if (d > dest[x] + final_dest[x]) puts("0");
        else if (d <= dest[x]) printf("%d\n", upword(x, d, PTR));
        else printf("%d\n", upword(to[x], final_dest[x] + dest[x] - d, PTR));
    }
    for (int i = 0; i < 15; ++i) free(PTR[i]);
    free(PTR);
    free(dest);
    free(to);
    free(final_dest);
    return 0;
}