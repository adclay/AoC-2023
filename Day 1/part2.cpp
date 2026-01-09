#include "header.h"

int part2(std::istream &fin) {
	int retval = 0;

	string line;
	while (getline(fin, line)) {
		int prev_digit = -1;

		for (size_t i = 0; i < line.size(); ++i) {
			int cur_digit;
			if (isdigit(line[i]))
				cur_digit = line[i] - '0';
			else if (0 == line.compare(i, 3, "one"))
				cur_digit = 1;
			else if (0 == line.compare(i, 3, "two"))
				cur_digit = 2;
			else if (0 == line.compare(i, 5, "three"))
				cur_digit = 3;
			else if (0 == line.compare(i, 4, "four"))
				cur_digit = 4;
			else if (0 == line.compare(i, 4, "five"))
				cur_digit = 5;
			else if (0 == line.compare(i, 3, "six"))
				cur_digit = 6;
			else if (0 == line.compare(i, 5, "seven"))
				cur_digit = 7;
			else if (0 == line.compare(i, 5, "eight"))
				cur_digit = 8;
			else if (0 == line.compare(i, 4, "nine"))
				cur_digit = 9;
			else
				continue;

			if (-1 == prev_digit)
				retval += 11 * cur_digit;
			else
				retval += cur_digit - prev_digit;
			prev_digit = cur_digit;
		}
	}

	return retval;
}
