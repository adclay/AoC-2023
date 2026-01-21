#include "header.h"

int part2(std::istream &fin) {
	// Create large map of the pipes
	vector<string> pipes;
	string line;
	while (getline(fin, line)) {
		string top, mid, bot;
		for (char c : line) {
			switch (c) {
				case '|':
					top += ".|.";
					mid += ".|.";
					bot += ".|.";
					break;
				case '-':
					top += "...";
					mid += "---";
					bot += "...";
					break;
				case 'L':
					top += ".|.";
					mid += ".L-";
					bot += "...";
					break;
				case 'J':
					top += ".|.";
					mid += "-J.";
					bot += "...";
					break;
				case '7':
					top += "...";
					mid += "-7.";
					bot += ".|.";
					break;
				case 'F':
					top += "...";
					mid += ".F-";
					bot += ".|.";
					break;
				case '.':
					top += "...";
					mid += "...";
					bot += "...";
					break;
				case 'S':
					top += "...";
					mid += ".S.";
					bot += "...";
					break;
				default:
					return -1;
			}
		}
		pipes.push_back(top);
		pipes.push_back(mid);
		pipes.push_back(bot);
	}

	// Find and mend start position
	int sy, sx;
	for (sy = 0; sy != pipes.size(); ++sy) {
		for (sx = 0; sx != pipes[sy].size(); ++sx) {
			if ('S' == pipes[sy][sx]) break;
		}
		if (sx != pipes[sy].size()) break;
	}
	if (1 != sy && '.' != pipes[sy - 2][sx]) pipes[sy - 1][sx] = '|';
	if (1 != sx && '.' != pipes[sy][sx - 2]) pipes[sy][sx - 1] = '-';
	if (pipes.size() - 2 != sy && '.' != pipes[sy + 2][sx]) pipes[sy + 1][sx] = '|';
	if (pipes[sy].size() - 2 != sx && '.' != pipes[sy][sx + 2]) pipes[sy][sx + 1] = '-';

	// Find first adjacent pipe
	char dir;
	if (0 != sy && ('|' == pipes[sy - 1][sx] || 'F' == pipes[sy - 1][sx] || '7' == pipes[sy - 1][sx]))
		dir = 'N';
	else if (0 != sx && ('-' == pipes[sy][sx - 1] || 'F' == pipes[sy][sx - 1] || 'L' == pipes[sy][sx - 1]))
		dir = 'W';
	else
		dir = 'S';

	// Replace loop with 'X'
	int not_enclosed = 0, y = sy, x = sx;
	do {
		if (y % 3 == 1 && x % 3 == 1) ++not_enclosed;
		pipes[y][x] = 'X';

		if ('N' == dir) {
			--y;
			switch (pipes[y][x]) {
			case '|':
				dir = 'N';
				break;
			case 'F':
				dir = 'E';
				break;
			case '7':
				dir = 'W';
				break;
			}
		}
		else if ('E' == dir) {
			++x;
			switch (pipes[y][x]) {
			case 'J':
				dir = 'N';
				break;
			case '-':
				dir = 'E';
				break;
			case '7':
				dir = 'S';
				break;
			}
		}
		else if ('S' == dir) {
			++y;
			switch (pipes[y][x]) {
			case 'L':
				dir = 'E';
				break;
			case '|':
				dir = 'S';
				break;
			case 'J':
				dir = 'W';
				break;
			}
		}
		else {
			--x;
			switch (pipes[y][x]) {
			case 'L':
				dir = 'N';
				break;
			case 'F':
				dir = 'S';
				break;
			case '-':
				dir = 'W';
				break;
			}
		}
	} while (y != sy || x != sx);

	// Replace everything else with '.'
	for (y = 1; y < pipes.size(); y += 3) {
		for (x = 1; x < pipes[y].size(); x += 3) {
			if (pipes[y][x] != 'X') {
				for (int dy = -1; dy != 2; ++dy)
					for (int dx = -1; dx != 2; ++dx)
						pipes[y + dy][x + dx] = '.';
			}
		}
	}

	// Finish finding the number of non-enclosed tiles
	set<pair<int, int>> outside = { {0, 0} };
	while (outside.size() != 0) {
		auto last = --outside.end();
		int y = last->first, x = last->second;
		outside.erase(last);

		if (y < 0 || x < 0 || y >= pipes.size() || x >= pipes[y].size() || '.' != pipes[y][x]) continue;
		pipes[y][x] = 'X';
		outside.insert({ make_pair(y - 1, x), make_pair(y + 1, x), make_pair(y, x - 1), make_pair(y, x + 1) });

		if (y % 3 == 1 && x % 3 == 1) ++not_enclosed;
	}
	return (pipes.size() / 3) * (pipes[0].size() / 3) - not_enclosed;
}
