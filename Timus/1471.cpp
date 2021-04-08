#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{ int parent; int weight; }Node;
typedef struct{ int* val; int size; }Stack;

int stack_pop(Stack* stack){
    int result = (*stack).val[--((*stack).size)];
    (*stack).val = (int*)realloc((*stack).val, (*stack).size * sizeof(int));
    return result;
}

void stack_push(Stack* stack, int num) {
    (*stack).val = (int*)realloc((*stack).val, ++((*stack).size) * sizeof(int));
    (*stack).val[(*stack).size - 1] = num;
}

int in_arr(Node* arr, int len, int point) {
    for (int i = 0; i < len; ++i) {
        if (arr[i].parent == point) return i;
    }
    return -1;
}

int main() {
    int n;
    scanf("%d", &n);
    Node** arr = (Node**)calloc(n, sizeof(Node*));
    int* sizes = (int*)calloc(n, sizeof(int));
    for (size_t i = 1; i < n; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        arr[a] = (Node*)realloc(arr[a], ++sizes[a] * sizeof(Node));
        arr[b] = (Node*)realloc(arr[b], ++sizes[b] * sizeof(Node));
        arr[a][sizes[a] - 1] = { b, c };
        arr[b][sizes[b] - 1] = { a, c };
    }
    //convert to one dimension
    Node* nodes = (Node*)calloc(n, sizeof(Node));
    nodes[0] = { -1, 0 };
    Stack stack = { 0, 0 };
    for (int i = 1; i < n; ++i) {
        nodes[i] = { -1, -1 };
    }
    stack_push(&stack, 0);
    while(stack.size) {
        int p = stack_pop(&stack);
        for(int i = 0; i < sizes[p]; i++) {
            if (nodes[arr[p][i].parent].weight == -1) {
                nodes[arr[p][i].parent] = { p, arr[p][i].weight };
                stack_push(&stack, arr[p][i].parent);
            }
        }
    }
    free(arr);
    free(sizes);
    scanf("%d", &n);
    for (size_t i = 0; i < n; ++i) {
        int from, to, len_path = 1;
        scanf("%d %d", &from, &to);
        Node* path = (Node*)malloc(len_path * sizeof(Node));
        path[0] = {from, 0};
        while(nodes[from].parent != -1) {
            path = (Node*)realloc(path, ++len_path * sizeof(Node));
            path[len_path - 1] = { nodes[from].parent , path[len_path - 2].weight + nodes[from].weight };
            from = nodes[from].parent;
        }
        int intersect = 0, sum = 0;
        while ((intersect = in_arr(path, len_path, to)) == -1) {
            sum += nodes[to].weight;
            to = nodes[to].parent;
        }
        printf("%d\n", sum + path[intersect].weight);
        free(path);
    }
    
    free(nodes);
    return 0;
}