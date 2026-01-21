#include "header.h"

int part1(std::istream &fin) {
	// Create map of the pipes
	vector<vector<char>> pipes;
	string line;
	while (getline(fin, line)) {
		pipes.push_back(vector<char>(line.cbegin(), line.cend()));
	}

	// Find start position
	int sy, sx;
	for (sy = 0; sy != pipes.size(); ++sy) {
		for (sx = 0; sx != pipes[sy].size(); ++sx) {
			if ('S' == pipes[sy][sx]) break;
		}
		if (sx != pipes[sy].size()) break;
	}

	// Find first adjacent pipe
	char dir;
	if (0 != sy && ('|' == pipes[sy - 1][sx] || 'F' == pipes[sy - 1][sx] || '7' == pipes[sy - 1][sx]))
		dir = 'N';
	else if (0 != sx && ('-' == pipes[sy][sx - 1] || 'F' == pipes[sy][sx - 1] || 'L' == pipes[sy][sx - 1]))
		dir = 'W';
	else
		dir = 'S';

	// Get pipe length
	int length = 0, y = sy, x = sx;
	do {
		++length;

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

	return length / 2;
}
