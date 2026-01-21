#include "header.h"

int part1(std::istream &fin) {
	int retval = 0;

	string line;
	while (getline(fin, line)) {
		vector<int> sequence;
		std::istringstream sin(line);

		// Read initial sequence
		bool all_zero = true;
		int next;
		while (sin >> next) {
			sequence.push_back(next);
			if (next) {
				all_zero = false;
			}
		}
		if (sequence.empty()) {
			continue;
		}

		// Iterate differentiation until we get all zeros
		while (!all_zero) {
			all_zero = true;
			for (auto beg = sequence.begin(), end = sequence.end() - 1; beg != end; ++beg) {
				*beg = *(beg + 1) - *beg;
				if (*beg) {
					all_zero = false;
				}
			}
			sequence.erase(sequence.end() - 1);
			next += sequence.back();
		}

		// Increment by next value in sequence
		retval += next;
	}

	return retval;
}
