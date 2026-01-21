#include "header.h"

int part1(std::istream &fin) {
	string instr;
	fin >> instr;

	// Create network
	map<string, pair<string, string>> network;
	while (fin) {
		string node, left, right;
		if (fin >> node >> left >> left >> right) {
			network[node] = { left.substr(1, 3), right.substr(0, 3) };
		}
	}

	// Follow instructions
	int retval = 0;
	string node = "AAA";
	while (node != "ZZZ") {
		if (instr[retval++ % instr.size()] == 'L') {
			node = network.at(node).first;
		}
		else {
			node = network.at(node).second;
		}
	}
	return retval;
}
