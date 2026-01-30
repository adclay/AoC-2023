#include "header.h"

extern map<string, shared_ptr<Module>> modules;

int part1(std::istream &fin) {
	read_modules(fin);

	// Press buttons
	int low_pulses = 0, high_pulses = 0;
	for (int button_presses = 0; button_presses != 1000; ++button_presses) {
		++low_pulses;
		deque<pair<string, bool>> pulses{ make_pair("broadcaster", false) };

		while (!pulses.empty()) {
			string name = pulses.front().first;
			bool pulse = pulses.front().second;
			pulses.pop_front();

			auto ss = modules.at(name)->get_dest();
			for (auto &start = ss.first, &stop = ss.second; start != stop; ++start) {
				++(pulse ? high_pulses : low_pulses);
				int next_pulse = modules.at(*start)->pulse(name, pulse);
				if (next_pulse) {
					pulses.push_back(make_pair(*start, next_pulse == 1 ? false : true));
				}
			}
		}
	}
	return low_pulses * high_pulses;
}
