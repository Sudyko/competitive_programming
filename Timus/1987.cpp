#include <stdlib.h>
#include <stdio.h>
#include <vector>

#define MAXN 1000000000

using namespace std;

struct Segment {
	long x1, x2;
	int pos;

	int GetLength() {
		return x2 - x1;
	}
};

bool in_line(Segment& v, long& point) {
	if (point >= v.x1 && point <= v.x2)
		return true;
	return false;
}

int main() {
	vector<Segment> lines;
	long n;
	scanf_s("%ld", &n);
	for (int i = 0; i < n; ++i) {
		Segment line;
		line.pos = i + 1;
		scanf_s("%ld %ld", &line.x1, &line.x2);
		lines.push_back(line);
	}
	scanf_s("%ld", &n);
	vector<int> result;
	for (int i = 0; i < n; ++i) {
		long point;
		scanf_s("%ld", &point);
		vector<Segment> points_lines;
		for (int j = 0; j < lines.size(); ++j) {
			if (in_line(lines[j], point))
				points_lines.push_back(lines[j]);
		}
		Segment min_seg = { 0, MAXN };
		for (int j = 0; j < points_lines.size(); ++j) {
			if (points_lines[j].GetLength() < min_seg.GetLength())
				min_seg = points_lines[j];
		}
		if (points_lines.size() == 0)
			result.push_back(-1);
		else
			result.push_back(min_seg.pos);
	}
	for (int i = 0; i < result.size() - 1; ++i)
		printf("%d\n", result[i]);
	printf("%d", result[result.size() - 1]);
	return 0;
}