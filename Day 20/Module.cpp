#include "header.h"

/* ********************************************************************************************** *
 *                                        Global Variables                                        *
 * ********************************************************************************************** */

map<string, shared_ptr<Module>> modules;

/* ********************************************************************************************** *
 *                                    Module Member Functions                                     *
 * ********************************************************************************************** */

void Module::add_src(const string &name) {
	if (src_is_set) {
		src.insert(name);
	}
	else {
		src_state[name] = false;
	}
}

Module::Module(bool src_is_set) : dest(), src_is_set(src_is_set) {
	if (src_is_set) {
		new (&src) set<string>();
	}
	else {
		new (&src_state) map<string, bool>();
	}
}
Module::~Module() {
	dest.~vector<string>();
	if (src_is_set) {
		src.~set<string>();
	}
	else {
		src_state.~map<string, bool>();
	}
}

pair<vector<string>::const_iterator, vector<string>::const_iterator> Module::get_dest() {
	return make_pair(dest.cbegin(), dest.cend());
}
pair<set<string>::const_iterator, set<string>::const_iterator> Module::get_src() {
	return make_pair(src.cbegin(), src.cend());
}
pair<map<string, bool>::const_iterator, map<string, bool>::const_iterator> Module::get_src_state() {
	return make_pair(src_state.cbegin(), src_state.cend());
}

/* ********************************************************************************************** *
 *                                   bool get_state() override;                                   *
 * ********************************************************************************************** */

bool Broadcast::get_state() {
	return false;
}
bool Receive::get_state() {
	return false;
}
bool FlipFlop::get_state() {
	return state;
}
bool Conjunction::get_state() {
	for (const auto &ss : src_state) {
		if (ss.second) {
			return true;
		}
	}
	return false;
}

/* ********************************************************************************************** *
 *                          int pulse(string name, bool pulse) override;                          *
 * ********************************************************************************************** */

int Broadcast::pulse(string name, bool pulse) {
	return pulse + 1;
}
int Receive::pulse(string name, bool pulse) {
	return 0;
}
int FlipFlop::pulse(string name, bool pulse) {
	if (!pulse) {
		state = !state;
		return state + 1;
	}
	return 0;
}
int Conjunction::pulse(string name, bool pulse) {
	src_state[name] = pulse;
	for (const auto &src_state : src_state) {
		if (!src_state.second) {
			return 2;
		}
	}
	return 1;
}

/* ********************************************************************************************** *
 *                                       Related Functions                                        *
 * ********************************************************************************************** */

MODULE_TYPE get_module_type(const string &name) {
	const type_info &type = typeid(*modules.at(name));

	if (type == typeid(Broadcast)) {
		return BROADCAST;
	}
	if (type == typeid(Receive)) {
		return RECEIVE;
	}
	if (type == typeid(FlipFlop)) {
		return FLIPFLOP;
	}
	if (type == typeid(Conjunction)) {
		return CONJUNCTION;
	}
	return MODULE_TYPE_ERROR;
}

void read_modules(std::istream &fin) {
	// Read module names and types
	for (string line; getline(fin, line);) {
		std::istringstream sin(line);
		string name;

		sin >> name;
		if (name.front() == '%') {
			name.erase(name.cbegin());
			modules[name] = make_shared<FlipFlop>();
		}
		else if (name.front() == '&') {
			name.erase(name.cbegin());
			modules[name] = make_shared<Conjunction>();
		}
		else {
			modules[name] = make_shared<Broadcast>();
		}
	}

	// Read destinations and sources
	fin.clear();
	fin.seekg(0);
	for (string line; getline(fin, line);) {
		std::istringstream sin(line);
		string name, dest;

		sin >> name >> dest;
		if (name.front() == '%' || name.front() == '&') {
			name.erase(name.cbegin());
		}

		while (sin >> dest) {
			if (dest.back() == ',') {
				dest.pop_back();
			}
			modules.at(name)->dest.push_back(dest);

			if (!modules.contains(dest)) {
				modules[dest] = make_shared<Receive>();
			}
			modules.at(dest)->add_src(name);
		}
	}
}

bool is_fresh(set<string> sub_modules) {
	for (const string &name : sub_modules) {
		if (modules.at(name)->get_state()) {
			return false;
		}
	}
	return true;
}
