#include "header.h"

int part1(std::istream &fin) {
	int retval = 0;

	string line;
	while (getline(fin, line)) {
		std::istringstream sin(line);
		string word;
		vector<int> winning_numbers;
		int num;

		// Read winning numbers
		sin >> word >> word;
		while (sin >> num) {
			winning_numbers.push_back(num);
		}
		sin.clear();
		sin >> word;

		// Calculate points
		int points = 1;
		while (sin >> num) {
			for (int x : winning_numbers) {
				if (num == x) {
					points <<= 1;
					break;
				}
			}
		}
		retval += points >> 1;
	}

	return retval;
}
