#include "header.h"

static bool contains(vector<int> vec, int x) {
	for (int i : vec) {
		if (x == i) {
			return true;
		}
	}
	return false;
}

int part1(std::istream &fin) {
	int width = 0;
	vector<int> numbers, number_pos, symbol_pos;

	// Fill in values and positions of numbers and symbols
	string line;
	for (int row = 0, num = 0; getline(fin, line); ++row) {
		width = line.size() + 1; // +1 so when we try to index to the left or right of the
								 // schematic, we get an invalid position

		for (int col = 0; col < line.size(); ++col) {
			// Handle digits
			if (isdigit(line[col])) {
				if (0 == num) {
					number_pos.push_back(row * width + col);
				}
				num = num * 10 + line[col] - '0';
				continue;
			}

			// Handle non-digits
			if (num) {
				numbers.push_back(num);
				num = 0;
			}
			if ('.' != line[col]) {
				symbol_pos.push_back(row * width + col);
			}
		}

		// Handle numbers that appear at the end of a line
		if (num) {
			numbers.push_back(num);
			num = 0;
		}
	}

	// Sum part numbers
	int retval = 0;
	for (decltype(number_pos.size()) i = 0; i < number_pos.size(); ++i) {
		// Calculate length of number
		int temp = numbers[i], length = 0;
		while (temp != 0) ++length, temp /= 10;

		// Determine if number is adjacent to a symbol
		int pos = number_pos[i];
		bool adjacent = contains(symbol_pos, pos - 1) || contains(symbol_pos, pos + length);
		for (int i = -1; !adjacent && i <= length; ++i) {
			adjacent = contains(symbol_pos, pos - width + i) || contains(symbol_pos, pos + width + i);
		}
		if (adjacent) {
			retval += numbers[i];
		}
	}

	return retval;
}
