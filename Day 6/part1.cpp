#include "header.h"

int part1(std::istream &fin) {
	int retval = 1;

	string ignore;
	int num;
	vector<int> time, distance;

	fin >> ignore;
	while (fin >> num) time.push_back(num);
	fin.clear();

	fin >> ignore;
	while (fin >> num) distance.push_back(num);
	fin.clear();

	for (int i = 0; i < time.size(); ++i) {
		int t = time[i], d = distance[i];
		double min_time = (t - sqrt(t * t - 4 * d)) / 2.;
		double max_time = (t + sqrt(t * t - 4 * d)) / 2.;
		retval *= ceil(max_time) - floor(min_time) - 1;
	}

	return retval;
}
