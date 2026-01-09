#include "header.h"

int part2(std::istream &fin) {
	int retval = 0;

	string line;
	while (getline(fin, line)) {
		int temp;
		string word;
		std::istringstream sin(line);

		// Skip game ID
		sin >> word >> temp >> word;

		// Read marble colors
		int r = 0, g = 0, b = 0;
		while (sin >> temp >> word) {
			// Read group of marble colors and counts
			if      (0 == word.compare(0, 3, "red")   && temp > r) r = temp;
			else if (0 == word.compare(0, 5, "green") && temp > g) g = temp;
			else if (0 == word.compare(0, 4, "blue")  && temp > b) b = temp;
		}

		// Calculate minimum power
		retval += r * g * b;
	}

	return retval;
}
