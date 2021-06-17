#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { char x, y; } Cell;

typedef struct { Cell position; char count; } Neighbour;

char bounds(Cell num, char bound) { return (num.x >= 0 && num.x < bound && num.y >= 0 && num.y < bound); }

int main() {
	int n;
	char buf[0x1];
	gets(buf);
	n = atoi(buf);
	if (n == 1) puts("a1");
	else if (n < 5) puts("IMPOSSIBLE");
	else {
		const char movex[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
		const char movey[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
		Neighbour surround[8];
		char** state = (char**)malloc(sizeof(char*) * n);
		for (int i = 0; i < n; ++i) {
			state[i] = (char*)malloc(sizeof(char) * n);
			memset(state[i], 1, n);
		}
		Cell start = { 0, 0 };
		puts("a1");
		state[0][0] = 0;
		for (int i = 1; i < n * n; ++i) {
			char amount = 0;
			for (int j = 0; j < 8; ++j) {
				Cell cur = start;
				cur.x += movex[j];
				cur.y += movey[j];
				if (bounds(cur, n) && state[cur.x][cur.y]) {
					surround[amount++].position = cur;
				}
			}
			for (int j = 0; j < amount; ++j) {
				surround[j].count = 0;
				for (int k = 0; k < 8; ++k) {
					Cell cur = surround[j].position;
					cur.x += movex[k];
					cur.y += movey[k];
					if (bounds(cur, n) && state[cur.x][cur.y]) {
						surround[j].count++;
					}
				}
			}
			char min = 0, minval = surround[0].count;
			for (int j = 1; j < amount; ++j) {
				if (minval > surround[j].count) minval = surround[(min = j)].count;
			}
			start = surround[min].position;
			state[start.x][start.y] = 0;
			putchar('a' + start.x);
			putchar('1' + start.y);
			putchar('\n');
		}
		for (int i = 0; i < n; ++i) free(state[i]);
		free(state);
	}
	return 0;
}