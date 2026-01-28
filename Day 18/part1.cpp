#include "header.h"

/* ********************************************************************************************** *
 * I implemented this solution using Green's Theorem, a corollary of which is the fact that the   *
 * area enclosed by a curve is $\oint x dy$. Note that this implementation assumes the tunnel	  *
 * doesn't intersect itself, and every instruction is followed by a 90 degree turn. Some		  *
 * important details are:																		  *
 * - We're using coordinates with the +y direction pointing downward, so a positively oriented	  *
 *   curve is clockwise, not counterclockwise.													  *
 * - We actually use the integral to calculate the area enclosed by a curve that goes through the *
 *   center of the tunnel. Since we don't know the orientation of the curve a priori, we don't	  *
 *   know which side of the tunnel is the outside/inside before we calculate the integral.		  *
 * - The area of the tunnel which lies outside the curve can be calculated from its perimeter and *
 *   the number of exterior/interior corners (e.g. a right turn is an exterior corner for a		  *
 *   positively oriented curve).																  *
 * ********************************************************************************************** */

static int get_area(vector<pair<char, int>> &dig_plan) {
	// Evaluate line integral, perimeter, and exterior/interior corners
	int area = 0, perimeter = 0, right_turns = 0, left_turns = 0;
	int x = 0, y = 0;
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

int part1(std::istream &fin) {
	vector<pair<char, int>> dig_plan;
	for (string line; getline(fin, line);) {
		std::istringstream sin(line);
		char c;
		int i;
		sin >> c >> i;
		dig_plan.push_back(pair<char, int>(c, i));
	}

	return get_area(dig_plan);
}
