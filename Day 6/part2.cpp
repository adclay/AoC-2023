#include "header.h"

long long part2(std::istream& fin) {
	string line;
	long long t = 0, d = 0;
	char c;

	fin >> line;
	getline(fin, line);
	for (char c : line) if (isdigit(c)) t = t * 10 + c - '0';

	fin >> line;
	getline(fin, line);
	for (char c : line) if (isdigit(c)) d = d * 10 + c - '0';

	double min_time = (t - sqrt(t * t - 4 * d)) / 2.;
	double max_time = (t + sqrt(t * t - 4 * d)) / 2.;

	return ceil(max_time) - floor(min_time) - 1;
}
