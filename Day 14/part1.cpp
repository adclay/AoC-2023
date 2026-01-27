#include "header.h"

int part1(std::istream &fin) {
	// Read input
	vector<string> platform;
	for (string line; getline(fin, line) && !line.empty();) {
		platform.push_back(line);
	}

	// Calculate load
	int retval = 0;
	const int N = platform.size(), M = platform[0].size();
	for (int col = 0; col != M; ++col) {
		for (int i = 0, row = 0; row != N; ++row) {
			if (platform[row][col] == 'O') {
				retval += N - i;
				++i;
			}
			else if (platform[row][col] == '#') {
				i = row + 1;
			}
		}
	}
	return retval;
}
