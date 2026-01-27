#include "header.h"

static int horizontal_symmetry(const vector<string> &ground) {
	for (int row = 1; row != ground.size(); ++row) {
		for (int offset = 0;; ++offset) {
			if (ground[row + offset] != ground[row - 1 - offset]) {
				break;
			}
			if (row - 1 - offset == 0 || row + offset == ground.size() - 1) {
				return row;
			}
		}
	}
	return 0;
}

int part1(std::istream &fin) {
	int retval = -1;

	while (fin) {
		// Create map of the ground
		vector<string> ground;
		string line;
		while (getline(fin, line) && !line.empty()) {
			ground.push_back(line);
		}

		// Determine if there's a horizontal line symmetry
		int symm = horizontal_symmetry(ground);
		if (symm) {
			retval += 100 * symm;
			continue;
		}

		// Transpose the map of the ground
		vector<string> transposed_ground;
		for (int x = 0; x != ground[0].size(); ++x) {
			transposed_ground.push_back(accumulate(
				ground.cbegin(), ground.cend(), string(),
				[x](string s, string e) { return s + e[x]; }
			))
		}

		// Determine if there's a vertical line symmetry

		cout << endl << "Start" << endl;
		for (auto line : ground) {
			cout << line << endl;
		}
		cout << "Vertical: " << horizontal_symmetry(ground) << endl;
		cout << "End" << endl;
	}

	return retval;
}
