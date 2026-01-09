#include "header.h"

int part1(std::istream &fin) {
	int retval = 0;

	string line;
	while (getline(fin, line)) {
		int last_digit = -1;

		for (const char c : line) {
			if (isdigit(c)) {
				if (-1 == last_digit) {
					last_digit = c - '0';
					retval += 11 * last_digit;
				}
				else {
					retval -= last_digit;
					retval += (last_digit = c - '0');
				}
			}
		}
	}

	return retval;
}
