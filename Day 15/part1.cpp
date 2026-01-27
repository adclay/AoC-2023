#include "header.h"

static int hash(const string &s) {
	int retval = 0;
	for (char c : s) {
		retval = (retval + c) * 17 % 256;
	}
	return retval;
}

int part1(std::istream &fin) {
	int retval = 0;
	for (string line; getline(fin, line);) {
		retval += hash(line);
	}
	return retval;
}
