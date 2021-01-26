#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <stack>

using namespace std;

struct Segment {
	int x1, x2;
};

int main() {
	int n;
	int cur_seg = 1;
	stack<int> stack;
	scanf_s("%d", &n);
	vector<Segment> segments(n + 1);
	for (int i = 1; i < n + 1; ++i) {
		Segment s;
		scanf_s("%d %d", &s.x1, &s.x2);
		segments[i] = s;
	}
	segments.push_back({ 1000000000 , 1000000000 });

	scanf_s("%d", &n);
	for (int i = 0; i < n; ++i) {
		int point;
		scanf_s("%d", &point);
		bool check = true;
		while (check) {
			if (stack.empty()) {
				if (point < segments[cur_seg].x1) {
					printf("-1\n");
					check = false;
				}
				else if (point > segments[cur_seg].x2) {
					++cur_seg;
				}
				else {
					stack.push(cur_seg);
					++cur_seg;
				}
			}
			else {
				if (point >= segments[stack.top()].x1 && point <= segments[stack.top()].x2) {
					if (point >= segments[cur_seg].x1 && point <= segments[cur_seg].x2) {
						stack.push(cur_seg);
						++cur_seg;
					}
					else if (point < segments[cur_seg].x1) {
						printf("%d\n", stack.top());
						check = false;
					}
					else {
						++cur_seg;
					}
				}
				else if (point > segments[stack.top()].x2)
					stack.pop();
			}
		}
	}
	return 0;
}
