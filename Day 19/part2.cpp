#include "header.h"

class PartRange {
	int xmas_min[4];
	int xmas_max[4];

	static int xmas_index(char c) {
		switch (c) {
		case 'x':
			return 0;
		case 'm':
			return 1;
		case 'a':
			return 2;
		case 's':
			return 3;
		default:
			return -1;
		}
	}

public:
	PartRange() : xmas_min{ 1,1,1,1 }, xmas_max{ 4001,4001,4001,4001 } { }

	bool empty() {
		for (int i = 0; i != 4; ++i) {
			if (xmas_max[i] <= xmas_min[i]) {
				return true;
			}
		}
		return false;
	}

	long long count() {
		long long retval = 1;
		for (int i = 0; i != 4; ++i) {
			int length = xmas_max[i] - xmas_min[i];
			if (length <= 0) {
				return 0;
			}
			retval *= length;
		}
		return retval;
	}

	pair<PartRange, PartRange> split(const string &str) {
		auto retval = pair<PartRange, PartRange>(*this, *this);

		int i = xmas_index(str[0]);
		char op = str[1];
		int val = stoi(str.substr(2));

		if (op == '<') {
			if (retval.first.xmas_max[i] > val) {
				retval.first.xmas_max[i] = val;
			}
			if (retval.second.xmas_min[i] < val) {
				retval.second.xmas_min[i] = val;
			}
		}
		else {
			if (retval.first.xmas_min[i] < val + 1) {
				retval.first.xmas_min[i] = val + 1;
			}
			if (retval.second.xmas_max[i] > val + 1) {
				retval.second.xmas_max[i] = val + 1;
			}
		}

		return retval;
	}
};

long long accept_part_range(PartRange &pr, const string &instr, const map<string, string> &workflows) {
	auto first = instr.cbegin();
	auto last = find(first, instr.cend(), ',');

	if (*first == 'A') {
		return pr.count();
	}
	else if (*first == 'R') {
		return 0;
	}
	else if (*(first + 1) != '<' && *(first + 1) != '>') {
		return accept_part_range(pr, workflows.at(string(first, last)), workflows);
	}

	auto mid = find(first, last, ':');
	auto split_pr = pr.split(string(first, mid));

	long long retval = 0;
	if (!split_pr.first.empty()) {
		retval += accept_part_range(split_pr.first, string(mid + 1, last), workflows);
	}
	if (!split_pr.second.empty()) {
		retval += accept_part_range(split_pr.second, string(last + 1, instr.cend()), workflows);
	}
	return retval;
}

long long part2(std::istream &fin) {
	// Read workflows
	map<string, string> workflows;
	for (string line; getline(fin, line) && !line.empty();) {
		size_t n = line.find('{');
		workflows[line.substr(0, n)] = line.substr(n + 1, line.size() - n - 2);
	}

	// Process parts
	PartRange pr;
	return accept_part_range(pr, "in", workflows);
}
