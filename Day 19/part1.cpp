#include "header.h"

struct Part {
	int x;
	int m;
	int a;
	int s;

	Part(string str) : x(0), m(0), a(0), s(0) {
		int x_i = str.find("x=");
		int m_i = str.find("m=");
		int a_i = str.find("a=");
		int s_i = str.find("s=");
		if (x_i != string::npos && m_i != string::npos && a_i != string::npos && s_i != string::npos) {
			x = stoi(str.substr(x_i + 2));
			m = stoi(str.substr(m_i + 2));
			a = stoi(str.substr(a_i + 2));
			s = stoi(str.substr(s_i + 2));
		}
	}

	int rating() {
		return x + m + a + s;
	}
};

bool accept_part(const Part &part, const string &wf, const map<string, string> &workflows) {
	const string &instr = workflows.at(wf);

	for (auto first = instr.cbegin(), last = find(first, instr.cend(), ','); first != last;) {
		if (*first == 'A') {
			return true;
		}
		else if (*first == 'R') {
			return false;
		}
		else if (*(first + 1) == '<' || *(first + 1) == '>') {
			int val = *first == 'x' ? part.x : *first == 'm' ? part.m : *first == 'a' ? part.a : part.s;
			if ((*(first + 1) == '<' && val < stoi(string(first + 2, last))) ||
				(*(first + 1) == '>' && val > stoi(string(first + 2, last)))) {
				first = find(first, last, ':') + 1;
			}
			else {
				first = last + 1;
				last = find(first, instr.cend(), ',');
			}
		}
		else {
			return accept_part(part, string(first, last), workflows);
		}
	}

	// Should never reach here
	cerr << "ERROR: Failed to complete workflow \"" << wf << "\"." << endl;
	return false;
}

int part1(std::istream &fin) {
	// Read workflows
	map<string, string> workflows;
	for (string line; getline(fin, line) && !line.empty();) {
		size_t n = line.find('{');
		workflows[line.substr(0, n)] = line.substr(n + 1, line.size() - n - 2);
	}

	// Process parts
	int retval = 0;
	for (string line; getline(fin, line);) {
		Part part(line);
		if (accept_part(part, "in", workflows)) {
			retval += part.rating();
		}
	}
	return retval;
}
