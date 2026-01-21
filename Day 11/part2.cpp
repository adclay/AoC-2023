#include "header.h"

// 82000210 is too low

long long part2(std::istream &fin) {
	// empty_row : indices of rows with no galaxies
	// empty_col : indices of cols with no galaxies
	// galaxies  : (y,x) coordinates of galaxies
	vector<int> empty_row, empty_col;
	vector<pair<int, int>> galaxies;

	// Read input
	string line;
	getline(fin, line);
	for (int x = 0; x != line.size(); ++x) empty_col.push_back(x);
	for (int y = 0; fin; getline(fin, line), ++y) {
		bool is_empty = true;
		for (int x = 0; x != line.size(); ++x) {
			if (line[x] == '#') {
				is_empty = false;
				galaxies.push_back({ y,x });
				auto it = find(empty_col.cbegin(), empty_col.cend(), x);
				if (it != empty_col.cend()) empty_col.erase(it);
			}
		}
		if (is_empty) empty_row.push_back(y);
	}

	// Get distances
	long long retval = 0;
	for (int i = 0; i != galaxies.size() - 1; ++i) {
		for (int j = i + 1; j != galaxies.size(); ++j) {
			int y1 = galaxies[i].first, x1 = galaxies[i].second,
				y2 = galaxies[j].first, x2 = galaxies[j].second;
			if (x1 > x2) x1 ^= x2, x2 ^= x1, x1 ^= x2;
			if (y1 > y2) y1 ^= y2, y2 ^= y1, y1 ^= y2;
			retval += x2 - x1 + y2 - y1;

			auto beg = find_if(empty_col.cbegin(), empty_col.cend(), [x1](int a) { return a > x1; }),
				end = find_if(beg, empty_col.cend(), [x2](int a) { return a > x2; });
			retval += 999999LL * (end - beg);

			beg = find_if(empty_row.cbegin(), empty_row.cend(), [y1](int a) { return a > y1; });
			end = find_if(beg, empty_row.cend(), [y2](int a) { return a > y2; });
			retval += 999999LL * (end - beg);
		}
	}
	return retval;
}
