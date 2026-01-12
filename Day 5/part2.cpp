#include "header.h"

int part2(std::istream& fin) {
	string ignore;
	long long destination, source, n;
	vector<long long> labels, ranges;

	// Read seeds
	fin >> ignore;
	while (fin >> source >> n) {
		labels.push_back(source);
		ranges.push_back(n);
	}
	fin.clear();

	// Convert to location
	for (int number_of_conversions = 0; number_of_conversions < 7; ++number_of_conversions) {
		vector<long long> new_labels, new_ranges;
		vector<bool> converted(labels.size(), false);

		getline(fin, ignore);
		while (fin >> destination >> source >> n) {
			const int end = labels.size();
			for (int i = 0; i < end; ++i) {
				if (!converted[i]) {
					if (source <= labels[i]) {
						if (labels[i] + ranges[i] <= source + n) { // Convert all
							new_labels.push_back(labels[i] + destination - source);
							new_ranges.push_back(ranges[i]);
							converted[i] = true;
						}
						else if (labels[i] < source + n) { // Convert beginning
							new_labels.push_back(labels[i] + destination - source);
							new_ranges.push_back(source + n - labels[i]);
							ranges[i] -= source + n - labels[i];
							labels[i] = source + n;
						}
					}
					else if (source < labels[i] + ranges[i]) {
						if (labels[i] + ranges[i] <= source + n) { // Convert end
							new_labels.push_back(destination);
							new_ranges.push_back(labels[i] + ranges[i] - source);
							ranges[i] = source - labels[i];
						}
						else { // Convert middle
							new_labels.push_back(destination);
							new_ranges.push_back(n);
							ranges[i] = source - labels[i];
							labels.push_back(source + n);
							ranges.push_back(labels[i] + ranges[i] - source - n);
							converted.push_back(false);
						}
					}
				}
			}
		}
		fin.clear();

		for (int i = 0; i < labels.size(); ++i) {
			if (!converted[i]) {
				new_labels.push_back(labels[i]);
				new_ranges.push_back(ranges[i]);
			}
		}
		labels = new_labels;
		ranges = new_ranges;
	}

	return *min_element(labels.begin(), labels.end());
}
