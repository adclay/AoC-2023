#include "header.h"

int part2(std::istream &fin) {
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
		next = sequence.front();
		bool minus = true;
		while (!all_zero) {
			all_zero = true;
			for (auto beg = sequence.begin(), end = sequence.end() - 1; beg != end; ++beg) {
				*beg = *(beg + 1) - *beg;
				if (*beg) {
					all_zero = false;
				}
			}
			sequence.erase(sequence.end() - 1);

			if (minus) {
				next -= sequence.front();
			}
			else {
				next += sequence.front();
			}
			minus = !minus;
		}

		// Increment by next value in sequence
		retval += next;
	}

	return retval;
}
