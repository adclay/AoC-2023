#include "header.h"

/* ********************************************************************************************** *
 *                                             Notes:                                             *
 * Each starting node hits an end node for the first time after some numbers of steps n, which is *
 * a multiple of the instruction length. Each of these end nodes loop back to themselves after n  *
 * steps, hitting no other end nodes in the process. Thus, the solution is the least common       *
 * multiple of the different values of n for each starting node.                                  *
 *                                                                                                *
 * The number of steps n for each starting node happens to be a prime number p times the length   *
 * of the instruction sequence. Thus, the solution is the product of the length of the            *
 * instruction sequence with these primes.                                                        *
 * ********************************************************************************************** */

long long part2(std::istream &fin) {
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

	// Find starting nodes
	vector<string> nodes;
	for (auto beg = network.cbegin(), end = network.cend(); beg != end; ++beg) {
		if (beg->first.back() == 'A') {
			nodes.push_back(beg->first);
		}
	}

	// Follow instructions for each node
	vector<int> steps;
	for (string &node : nodes) {
		int step = 0;
		while (node.back() != 'Z') {
			if (instr[step++ % instr.size()] == 'L') {
				node = network.at(node).first;
			}
			else {
				node = network.at(node).second;
			}
		}
		steps.push_back(step);
	}

	// Return least common multiple of steps
	return std::accumulate(steps.cbegin(), steps.cend(), instr.size(),
		[&instr](long long a, long long b) {return a * (b / instr.size()); });
}
