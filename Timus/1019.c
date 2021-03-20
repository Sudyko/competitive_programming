#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    Node* next;
    Node* prev;
};

struct Node_list {
    int len;
    Node* head;
};

Node* get_node(Node_list& list, int index) {
    if (index + 1 > list.len) {
        printf("Index out of range.");
        exit(2);
    }
    Node* result = list.head;
    for (size_t i = 0; i < index; ++i) {
        result = result->next;
    }
    return result;
}

void add_node(Node_list& list, int index, int val) {
    Node* tmp = new Node { val, 0, 0 };
    if (index == 0) {
        tmp->next = list.head;
        list.head = tmp;
    }
    else if (index == list.len) {
        Node* prev = get_node(list, index - 1);
        prev->next = tmp;
        tmp->prev = prev;
    } 
    else {
        Node* prev = get_node(list, index - 1);
        Node* current = prev->next;
        tmp->next = current;
        prev->next = tmp;
        tmp->prev = prev;
        current->prev = tmp;
    }
    ++list.len;
}

void remove_node(Node_list& list, int index) {
    if (index == 0) {
        list.head = list.head->next;
        list.head->prev = 0;
    }
    else {
        Node* prev = get_node(list, index - 1);
        prev->next = prev->next->next;
        prev->next->prev = prev;
    }
    --list.len;
}

int main() {
    Node_list list = { 0, 0 };
    add_node(list, 0, 0);
    add_node(list, 1, 1000000000);
    size_t n = 0;
    scanf("%d", &n);
    for (n; n > 0; --n) {
        int l, r;
        char color;
        scanf("%d %d %c", &l, &r, &color);
        if (color == 'w') color = 0;
        else color = 1;
        Node* here = list.head;
        for (int i = 0; i < list.len - 1; ++i) {
            char no_new = 0;
            int del = 0;
            if ((here->val <= l) && (here->next->val > l)) {
                if (here->val == l && ((i & 1) ^ color)) {
                    here = here->prev;
                    remove_node(list, i);
                    --i;
                    ++del;
                }
                int search = i;
                if ((i & 1) ^ color) {
                    add_node(list, i + 1, l);
                    here = here->next;
                    no_new = 1;
                    ++search;
                }
                Node* there = here;
                for (int j = search; j < list.len - 1; ++j) {
                    int val = there->val;
                    if (j > search) {
                        there = there->prev;
                        remove_node(list, j);
                        --j;
                        ++del;
                    }
                    if ((val <= r) && (there->next->val >= r)) {
                        if ((there->next->val == r && (del & 1))) {
                            remove_node(list, j + 1);
                        }
                        else if ((del & 1) ^ no_new) {
                            add_node(list, j + 1, r);
                        }
                        break;
                    }
                    there = there->next;
                }
                break;
            }
            here = here->next;
        }
    }
    int max = -1, start = -1;
    Node* here = list.head;
    for (size_t i = 0; i < list.len - 1; i += 2) {
        if (here->next->val - here->val > max) {
            max = here->next->val - here->val;
            start = i;
        }
        here = here->next->next;
    }
    here = get_node(list, start);
    printf("%d %d", here->val, here->next->val);
    return 0;
}