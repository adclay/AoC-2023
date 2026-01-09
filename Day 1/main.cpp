#include "header.h"

int main(int argc, char **argv) {
	std::ifstream fin;
	const char *part1_fn = "puzzle_input.txt";
	const char *part2_fn = "puzzle_input.txt";

	// Part 1
	fin.open(part1_fn);
	if (fin) {
		cout << "Answer to part 1 = " << part1(fin) << endl;
		fin.close();
	}
	else {
		cerr << "ERROR: failed to open \"" << part1_fn << '"' << endl;
	}

	// Part 2
	fin.open(part2_fn);
	if (fin) {
		cout << "Answer to part 2 = " << part2(fin) << endl;
		fin.close();
	}
	else {
		cerr << "ERROR: failed to open \"" << part2_fn << '"' << endl;
	}
}
