#include "header.h"

static long long get_area(vector<pair<char, int>> &dig_plan) {
	// Evaluate line integral, perimeter, and exterior/interior corners
	long long area = 0, perimeter = 0, right_turns = 0, left_turns = 0;
	long long x = 0, y = 0;
	char dir = dig_plan.back().first;
	for (auto &instr : dig_plan) {
		// Update direction and left/right turns
		if ((dir == 'L' && instr.first == 'U') || (dir == 'R' && instr.first == 'D') ||
			(dir == 'U' && instr.first == 'R') || (dir == 'D' && instr.first == 'L')) {
			++right_turns;
		}
		else {
			++left_turns;
		}
		dir = instr.first;

		// Update perimeter, position, and area
		perimeter += instr.second;
		switch (instr.first) {
		case 'U':
			instr.second = -instr.second;
		case 'D':
			y += instr.second;
			area += x * instr.second;
			break;
		case 'L':
			instr.second = -instr.second;
		case 'R':
			x += instr.second;
			break;
		default:
			return -1;
		}
	}
	if (area < 0) {
		area = -area;
		std::swap(left_turns, right_turns);
	}

	// Add area from perimeter (right turns add 3/4, left turns add 1/4, straights add 1/2)
	area += perimeter / 2 + (right_turns - left_turns) / 4;
	return area;
}

long long part2(std::istream &fin) {
	vector<pair<char, int>> dig_plan;
	for (string line; getline(fin, line);) {
		char dir = line[line.size() - 2];
		dir = dir == '0' ? 'R' : dir == '1' ? 'D' : dir == '2' ? 'L' : 'U';

		auto it = find(line.cbegin(), line.cend(), '#');
		int length = stoi(line.substr(it - line.cbegin() + 1, 5), nullptr, 16);
		dig_plan.push_back(pair<char, int>(dir, length));
	}

	return get_area(dig_plan);
}
