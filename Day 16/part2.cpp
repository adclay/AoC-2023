#include "header.h"

inline void move_forward(char dir, int &y, int &x) {
	switch (dir) {
	case '^':
		--y;
		break;
	case '<':
		--x;
		break;
	case 'v':
		++y;
		break;
	case '>':
		++x;
		break;
	default:
		return;
	}
}

static int get_energized(const vector<string> &tiles, char dir, int y, int x) {
	const int N = tiles.size(), M = tiles[0].size();

	// Find which directions and locations light is traveling
	vector<vector<set<char>>> light(N, vector<set<char>>(M, set<char>()));
	vector<pair<char, pair<int, int>>> heads = { make_pair(dir, make_pair(y, x)) };
	while (!heads.empty()) {
		char dir = heads.back().first;
		int y = heads.back().second.first, x = heads.back().second.second;
		heads.pop_back();

		if (y >= 0 && x >= 0 && y < N && x < M && !light[y][x].contains(dir)) {
			light[y][x].insert(dir);

			switch (tiles[y][x]) {
			case '.':
				move_forward(dir, y, x);
				heads.push_back(make_pair(dir, make_pair(y, x)));
				break;
			case '/':
				if (dir == '^') dir = '>';
				else if (dir == '<') dir = 'v';
				else if (dir == 'v') dir = '<';
				else if (dir == '>') dir = '^';
				move_forward(dir, y, x);
				heads.push_back(make_pair(dir, make_pair(y, x)));
				break;
			case '\\':
				if (dir == '^') dir = '<';
				else if (dir == '<') dir = '^';
				else if (dir == 'v') dir = '>';
				else if (dir == '>') dir = 'v';
				move_forward(dir, y, x);
				heads.push_back(make_pair(dir, make_pair(y, x)));
				break;
			case '|':
				if (dir == '^' || dir == 'v') {
					move_forward(dir, y, x);
					heads.push_back(make_pair(dir, make_pair(y, x)));
				}
				else {
					heads.push_back(make_pair('^', make_pair(y - 1, x)));
					heads.push_back(make_pair('v', make_pair(y + 1, x)));
				}
				break;
			case '-':
				if (dir == '<' || dir == '>') {
					move_forward(dir, y, x);
					heads.push_back(make_pair(dir, make_pair(y, x)));
				}
				else {
					heads.push_back(make_pair('<', make_pair(y, x - 1)));
					heads.push_back(make_pair('>', make_pair(y, x + 1)));
				}
				break;
			default:
				return -1;
			}
		}
	}

	// Calculate number of energized tiles
	int energized = 0;
	for (int y = 0; y != N; ++y) {
		for (int x = 0; x != M; ++x) {
			if (!light[y][x].empty()) {
				++energized;
			}
		}
	}
	return energized;
}

int part2(std::istream &fin) {
	vector<string> tiles;
	for (string line; getline(fin, line); tiles.push_back(line)) {}
	const int N = tiles.size(), M = tiles[0].size();

	int max_energized = 0;
	for (int y = 0; y != N; ++y) {
		int temp = get_energized(tiles, '>', y, 0);
		if (temp > max_energized) max_energized = temp;
		temp = get_energized(tiles, '<', y, M - 1);
		if (temp > max_energized) max_energized = temp;
	}
	for (int x = 0; x != M; ++x) {
		int temp = get_energized(tiles, 'v', 0, x);
		if (temp > max_energized) max_energized = temp;
		temp = get_energized(tiles, '^', N - 1, x);
		if (temp > max_energized) max_energized = temp;
	}
	return max_energized;
}
