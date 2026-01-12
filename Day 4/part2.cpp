#include "header.h"

int part2(std::istream& fin) {
	int retval = 0;

	string line;
	vector<int> scratchcards = { 1 };
	for (int i = 0; getline(fin, line); ++i) {
		std::istringstream sin(line);
		string word;
		vector<int> winning_numbers;
		int num;

		// Read winning numbers
		sin >> word >> word;
		while (sin >> num) {
			winning_numbers.push_back(num);
			if (0 == i) {
				scratchcards.push_back(1);
			}
		}
		sin.clear();
		sin >> word;

		// Calculate matches
		int matches = 0;
		while (sin >> num) {
			for (int x : winning_numbers) {
				if (num == x) {
					matches += 1;
					break;
				}
			}
		}

		// Update scratchard counts
		for (int j = 0; j < matches; ++j) {
			scratchcards[(i + j + 1) % scratchcards.size()] += scratchcards[i % scratchcards.size()];
		}
		retval += scratchcards[i % scratchcards.size()];
		scratchcards[i % scratchcards.size()] = 1;
	}

	return retval;
}
