#include "header.h"

static int process(const string &L0, const string &L1, const string &L2) {
	int retval = 0;

	for (int i = 0; i < L1.size(); ++i) {
		// Check for '*' symbol
		if (L1[i] != '*') continue;
		
		// Check if adjacent to exactly two numbers
		int count = 0;

		if (isdigit(L0[i])) ++count;
		else {
			if (i > 0 && isdigit(L0[i - 1])) ++count;
			if (i < L1.size() - 1 && isdigit(L0[i + 1])) ++count;
		}

		if (i > 0 && isdigit(L1[i - 1])) ++count;
		if (i < L1.size() - 1 && isdigit(L1[i + 1])) ++count;

		if (isdigit(L2[i])) ++count;
		else {
			if (i > 0 && isdigit(L2[i - 1])) ++count;
			if (i < L1.size() - 1 && isdigit(L2[i + 1])) ++count;
		}

		if (2 != count) continue;

		// Find adjacent number locations
		const string *str0 = 0, *str1 = 0;
		size_t str_i0 = 0, str_i1 = 0;

		if (isdigit(L0[i])) {
			str0 = &L0;
			str_i0 = i;
		}
		else {
			if (i > 0 && isdigit(L0[i - 1])) {
				str0 = &L0;
				str_i0 = i - 1;
			}
			if (i < L1.size() - 1 && isdigit(L0[i + 1])) {
				if (str0) {
					str1 = &L0;
					str_i1 = i + 1;
				}
				else {
					str0 = &L0;
					str_i0 = i + 1;
				}
			}
		}

		if (i > 0 && isdigit(L1[i - 1])) {
			if (str0) {
				str1 = &L1;
				str_i1 = i - 1;
			}
			else {
				str0 = &L1;
				str_i0 = i - 1;
			}
		}
		if (i < L1.size() - 1 && isdigit(L1[i + 1])) {
			if (str0) {
				str1 = &L1;
				str_i1 = i + 1;
			}
			else {
				str0 = &L1;
				str_i0 = i + 1;
			}
		}

		if (isdigit(L2[i])) {
			str1 = &L2;
			str_i1 = i;
		}
		else {
			if (i > 0 && isdigit(L2[i - 1])) {
				if (str0) {
					str1 = &L2;
					str_i1 = i - 1;
				}
				else {
					str0 = &L2;
					str_i0 = i - 1;
				}
			}
			if (i < L1.size() - 1 && isdigit(L2[i + 1])) {
				str1 = &L2;
				str_i1 = i + 1;
			}
		}

		while (str_i0 > 0 && isdigit((*str0)[str_i0 - 1])) --str_i0;
		while (str_i1 > 0 && isdigit((*str1)[str_i1 - 1])) --str_i1;

		// Get number values
		retval += stoi(str0->substr(str_i0)) * stoi(str1->substr(str_i1));
	}

	return retval;
}

int part2(std::istream& fin) {
	// Read three consecutive lines
	string L0, L1, L2;
	getline(fin, L1), getline(fin, L2);

	// Process lines
	int retval = 0;

	retval += process(string(L0.size(), '.'), L1, L2);
	while (L0 = L1, L1 = L2, getline(fin, L2))
		retval += process(L0, L1, L2);
	retval += process(L0, L1, string(L0.size(), '.'));

	return retval;
}
