#include "header.h"

static bool is_valid_arrangement_from_front(const string &arrangement, const vector<int> &record) {
	vector<int> r;
	int contiguous_damaged = 0;

	// Create reference record with regions of question marks denoted by 0s or -1s depending on
	// whether or not they can extend a contiguous region of damaged springs
	for (char c : arrangement) {
		if (c == '?') {
			if (contiguous_damaged) {
				r.push_back(contiguous_damaged);
				r.push_back(0);
			}
			else if (r.empty() || r.back() != -1) {
				r.push_back(-1);
			}
			contiguous_damaged = 0;
		}
		else if (c == '#') {
			++contiguous_damaged;
		}
		else if (contiguous_damaged) {
			r.push_back(contiguous_damaged);
			contiguous_damaged = 0;
		}
	}
	if (contiguous_damaged) {
		r.push_back(contiguous_damaged);
	}

	// Check that front matches
	for (int i = 0; i != r.size() && i != record.size(); ++i) {
		if (r[i] <= 0) {
			break;
		}
		if (r[i] > record[i]) {
			return false;
		}
		if (r[i] < record[i] && i != r.size() - 1 && r[i + 1] != 0) {
			return false;
		}
	}
	return true;
}

static bool is_valid_arrangement(const string &arrangement, const vector<int> &record) {
	if (!is_valid_arrangement_from_front(arrangement, record)) {
		return false;
	}

	const string r_arrangement(arrangement.crbegin(), arrangement.crend());
	const vector<int> r_record(record.crbegin(), record.crend());
	return is_valid_arrangement_from_front(r_arrangement, r_record);
}

static int count_arrangements(const string &arrangement, const vector<int> &record) {
	// Verify it can potentially be completed
	if (!is_valid_arrangement(arrangement, record)) {
		//cout << "Bad:  " << arrangement << endl;
		return 0;
	}

	// Verify the number of broken parts makes sense
	int unknown = accumulate(arrangement.cbegin(), arrangement.cend(), 0,
		[](int x, char c) {return x + (c == '?'); });
	int known_broken = accumulate(arrangement.cbegin(), arrangement.cend(), 0,
		[](int x, char c) {return x + (c == '#'); });
	int total_broken = accumulate(record.cbegin(), record.cend(), 0);
	if (known_broken > total_broken || known_broken + unknown < total_broken) {
		return 0;
	}

	// Find first '?' to recurse on
	auto it = find(arrangement.cbegin(), arrangement.cend(), '?');
	if (it == arrangement.cend()) {
		return 1;
	}

	// Recurse
	int retval = 0;
	if (known_broken < total_broken) {
		string r(arrangement);
		r[it - arrangement.cbegin()] = '#';
		retval += count_arrangements(r, record);
	}
	if (known_broken + unknown > total_broken) {
		string r(arrangement);
		r[it - arrangement.cbegin()] = '.';
		retval += count_arrangements(r, record);
	}
	return retval;
}

int part1(std::istream &fin) {
	int retval = 0;
	string line;
	while (getline(fin, line)) {
		std::stringstream sin(line);

		// Read condition record format 1
		string arrangement;
		sin >> arrangement;

		// Read condition record format 2
		vector<int> record;
		for (int num; sin >> num;) {
			record.push_back(num);
			char ignore;
			sin >> ignore;
		}

		// Calculate number of possible arrangements
		retval += count_arrangements(arrangement, record);
	}
	return retval;
}
