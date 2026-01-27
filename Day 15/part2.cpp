#include "header.h"

inline int hash(string::const_iterator start, size_t length) {
	return accumulate(start, start + length, 0, [](int x, char c) { return (x + c) * 17 % 256; });
}

void remove_lens(vector<pair<string, int>> &v, const string &s) {
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it->first == s) {
			v.erase(it);
			return;
		}
	}
}

void add_lens(vector<pair<string, int>> &v, const string &s, int focal_length) {
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it->first == s) {
			it->second = focal_length;
			return;
		}
	}
	v.push_back(make_pair(s, focal_length));
}

int part2(std::istream &fin) {
	// Create empty boxes
	vector<vector<pair<string, int>>> boxes(256, vector<pair<string, int>>());

	// Fill boxes with lenses
	for (string line; getline(fin, line);) {
		size_t op = line.find_first_of("-=");
		int box_i = hash(line.cbegin(), op);

		// Remove lens
		if (line[op] == '-') {
			line.erase(op);
			remove_lens(boxes[box_i], line);
		}

		// Add lens
		else {
			int focal_length = line[op + 1] - '0';
			line.erase(op);
			add_lens(boxes[box_i], line, focal_length);
		}
	}

	// Calculate focusing power
	int focusing_power = 0;
	for (int box_i = 0; box_i != 256; ++box_i) {
		for (int lens_i = 0; lens_i != boxes[box_i].size(); ++lens_i) {
			focusing_power += (box_i + 1) * (lens_i + 1) * boxes[box_i][lens_i].second;
		}
	}
	return focusing_power;
}
