#include "header.h"

extern map<string, shared_ptr<Module>> modules;

/*
There are nine Conjunction modules that feed into rx:
	{bn -> mk, cz -> hf, gp -> pm, rt -> pk} -> vf -> rx.
All other modules (besides "broadcaster") are FlipFlop modules. Thus, rx will receive a low signal
precisely when all the FlipFlop modules that directly feed into bn, cz, gp, and rt are on.

Furthermore, the inputs upon which these four Conjunction modules (recursively) depend on partition
the FlipFlop modules. Thus, we can independently determine the state of each of those four sub-
programs to determine the overall state of the program.

These sub-programs return to their original state after a few thousand button presses n (which
depends on the sub-program). We can find which button presses (mod n) cause the corresponding
conjunction to send a low signal. Then we can use the Chinese Remainder Theorem to find the smallest
number of button presses for which all four conjunctions send low signals. We should also check that
all four conjunctions actually send low signals at the same time during that button press (it's
possible one could send low and subsequently send high before the others send low).

In actuality, we can find the answer much more simply than that. The number of button presses which
causes each of the conjunctions bn, cz, gp, and rt to send low signals is the same as the number of
button presses which causes each sub-program to return to its original state. Further, these numbers
are distinct primes, so the answer is simply their product.
*/

long long part2(std::istream &fin) {
	read_modules(fin);

	// Find modules in each sub-program
	map<string, set<string>> sub_programs;
	for (const string &endpoint : { "bn", "cz", "gp", "rt" }) {
		set<string> &dependencies = sub_programs[endpoint];
		for (vector<string> unchecked{ endpoint }; !unchecked.empty();) {
			const string name = unchecked.back();
			unchecked.pop_back();

			if (get_module_type(name) == CONJUNCTION) {
				auto ss = modules.at(name)->get_src_state();
				for (auto &start = ss.first, &stop = ss.second; start != stop; ++start) {
					if (dependencies.insert(start->first).second) {
						unchecked.push_back(start->first);
					}
				}
			}
			else {
				auto ss = modules.at(name)->get_src();
				for (auto &start = ss.first, &stop = ss.second; start != stop; ++start) {
					if (dependencies.insert(*start).second) {
						unchecked.push_back(*start);
					}
				}
			}
		}
	}

	// Run sub-programs until they loop
	long long retval = 1;
	for (const auto &endpoint_submodules : sub_programs) {
		const string &endpoint = endpoint_submodules.first;
		const set<string> &submodules = endpoint_submodules.second;

		int button_presses = 0;
		do {
			deque<pair<string, bool>> pulses{ make_pair("broadcaster", false) };

			while (!pulses.empty()) {
				string name = pulses.front().first;
				bool pulse = pulses.front().second;
				pulses.pop_front();

				auto ss = modules.at(name)->get_dest();
				for (auto &start = ss.first, &stop = ss.second; start != stop; ++start) {
					if (submodules.contains(*start)) {
						int next_pulse = modules.at(*start)->pulse(name, pulse);
						if (next_pulse) {
							pulses.push_back(make_pair(*start, next_pulse == 1 ? false : true));
						}
					}
				}
			}

			++button_presses;
		} while (!is_fresh(submodules));

		retval *= button_presses;
	}
	return retval;
}
