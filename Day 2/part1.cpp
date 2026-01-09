#include "header.h"

int part1(std::istream &fin) {
	int retval = 0;

	string line;
	while (getline(fin, line)) {
		string word;
		std::istringstream sin(line);

		// Read game ID
		int id;
		sin >> word >> id >> word;

		// Assume game is valid
		retval += id;

		// Read marble colors
		int r = -1, g = -1, b = -1, temp;
		while (sin >> temp >> word) {
			// Read group of marble colors and counts
			if      (0 == word.compare(0, 3, "red"  )) r = temp;
			else if (0 == word.compare(0, 5, "green")) g = temp;
			else if (0 == word.compare(0, 4, "blue" )) b = temp;
			else {
				cerr << "BAD" << endl;
				return -1;
			}
			if (',' == word[word.size() - 1]) continue;

			// Check if group is invalid
			if (r > 12 || g > 13 || b > 14) {
				retval -= id;
				break;
			}
			r = -1, g = -1, b = -1;
		}
	}

	return retval;
}
