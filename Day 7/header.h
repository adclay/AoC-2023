#pragma once

/* ********************************************************************************************** *
 *                                        Standard Library                                        *
 * ********************************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout; using std::cerr; using std::endl;
using std::string; using std::vector; using std::begin; using std::end;

/* ********************************************************************************************** *
 *                                         Advent of Code                                         *
 * ********************************************************************************************** */

int part1(std::istream &);
int part2(std::istream &);

struct hand_bid {
	string hand;
	int bid;
};
