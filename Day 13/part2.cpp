#include "header.h"

static int find_smudged_symmetry(const vector<string> &ground) {
	const int N = ground.size();
	const int M = ground[0].size();

	// Reflection across horizontal line
	for (int row = 1; row != N; ++row) {
		int smudge = 0;
		for (int offset = 0;; ++offset) {
			for (int i = 0; i != M; ++i) {
				if (ground[row + offset][i] != ground[row - 1 - offset][i]) {
					++smudge;
				}
			}
			if (smudge > 1) {
				break;
			}
			if (row - 1 - offset == 0 || row + offset == N - 1) {
				if (smudge == 1) {
					return 100 * row;
				}
				break;
			}
		}
	}

	// Reflection across vertical line
	for (int col = 1; col != M; ++col) {
		int smudge = 0;
		for (int offset = 0;; ++offset) {
			for (int i = 0; i != N; ++i) {
				if (ground[i][col + offset] != ground[i][col - 1 - offset]) {
					++smudge;
				}
			}
			if (smudge > 1) {
				break;
			}
			if (col - 1 - offset == 0 || col + offset == M - 1) {
				if (smudge == 1) {
					return col;
				}
				break;
			}
		}
	}

	// Should never get here
	return 0x80000000;
}

int part2(std::istream &fin) {
	int retval = 0;

	while (fin) {
		// Create map of the ground
		vector<string> ground;
		string line;
		while (getline(fin, line) && !line.empty()) {
			ground.push_back(line);
		}

		// Find smudged symmetry
		retval += find_smudged_symmetry(ground);
	}

	return retval;
}
