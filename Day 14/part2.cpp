#include "header.h"

static void cycle(vector<string> &p) {
	const int N = p.size(), M = p[0].size();

	// Push north
	for (int col = 0; col != M; ++col) {
		for (int i = 0, row = 0; row != N; ++row) {
			if (p[row][col] == 'O') {
				p[row][col] = '.';
				p[i][col] = 'O';
				++i;
			}
			else if (p[row][col] == '#') {
				i = row + 1;
			}
		}
	}

	// Push west
	for (int row = 0; row != N; ++row) {
		for (int i = 0, col = 0; col != M; ++col) {
			if (p[row][col] == 'O') {
				p[row][col] = '.';
				p[row][i] = 'O';
				++i;
			}
			else if (p[row][col] == '#') {
				i = col + 1;
			}
		}
	}

	// Push south
	for (int col = 0; col != M; ++col) {
		for (int i = N - 1, row = N - 1; row != -1; --row) {
			if (p[row][col] == 'O') {
				p[row][col] = '.';
				p[i][col] = 'O';
				--i;
			}
			else if (p[row][col] == '#') {
				i = row - 1;
			}
		}
	}

	// Push east
	for (int row = 0; row != N; ++row) {
		for (int i = M - 1, col = M - 1; col != -1; --col) {
			if (p[row][col] == 'O') {
				p[row][col] = '.';
				p[row][i] = 'O';
				--i;
			}
			else if (p[row][col] == '#') {
				i = col - 1;
			}
		}
	}
}

static int get_load(const vector<string> &p) {
	int retval = 0;
	int load = p.size();
	for (const string &s : p) {
		for (char c : s) {
			if (c == 'O') {
				retval += load;
			}
		}
		--load;
	}
	return retval;
}

int part2(std::istream &fin) {
	// Read input
	vector<string> platform;
	for (string line; getline(fin, line) && !line.empty();) {
		platform.push_back(line);
	}

	// Cycle until we find a cycle
	int cycle_length = 0;
	vector<vector<string>> platforms;
	while (!cycle_length) {
		platforms.push_back(platform);
		cycle(platform);
		cycle_length = platforms.cend() - find(platforms.cbegin(), platforms.cend(), platform);
	}

	// Find which platform corresponds to the billionth cycle
	int index_in_cycle = (1000000000 - (platforms.size() - cycle_length)) % cycle_length;
	return get_load(platforms[platforms.size() - cycle_length + index_in_cycle]);
}
