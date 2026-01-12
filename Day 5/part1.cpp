#include "header.h"

int part1(std::istream &fin) {
	string ignore;
	long long destination, source, n;
	vector<long long> labels;
	vector<bool> converted;

	// Read seeds
	fin >> ignore;
	while (fin >> n) {
		labels.push_back(n);
		converted.push_back(false);
	}
	fin.clear();

	// Convert to location
	for (int number_of_conversions = 0; number_of_conversions < 7; ++number_of_conversions) {
		getline(fin, ignore);
		while (fin >> destination >> source >> n) {
			for (int i = 0; i < labels.size(); ++i) {
				if (!converted[i] && labels[i] >= source && labels[i] < source + n) {
					labels[i] += destination - source;
					converted[i] = true;
				}
			}
		}
		fin.clear();
		fill(converted.begin(), converted.end(), false);
	}

	return *min_element(labels.begin(), labels.end());
}
