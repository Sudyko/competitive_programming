#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Team {
	int team_id;
	int score;
};

bool operator<(const Team& lhs, const Team& rhs)
{
	return lhs.score > rhs.score; // wrong definition of operator< for boosting performance
}

int main() {
	int n;
	scanf_s("%d", &n);
	vector<Team> teams;
	for (int i = 0; i < n; ++i) {
		Team t;
		scanf_s("%d %d", &t.team_id, &t.score);
		teams.push_back(t);
	}

	stable_sort(teams.begin(), teams.end());

	for (const Team& item:teams) {
		printf("%d %d\n", item.team_id, item.score);
	}

	return 0;
}

/*
Complexity:
O(N·log(N)2), where N = std::distance(first, last) applications of cmp. If additional memory is available, then the complexity is O(N·log(N)).
*/
