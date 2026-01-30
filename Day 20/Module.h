#pragma once

#include "header.h"

/* ********************************************************************************************** *
 *                                  Module - Abstract Base Class                                  *
 * ********************************************************************************************** */

class Module {
protected:
	vector<string> dest;
	const bool src_is_set;
	union {
		set<string> src;
		map<string, bool> src_state;
	};

	void add_src(const string &name);

	Module(bool src_is_set);
	~Module();

public:
	pair<vector<string>::const_iterator, vector<string>::const_iterator> get_dest();
	pair<set<string>::const_iterator, set<string>::const_iterator> get_src();
	pair<map<string, bool>::const_iterator, map<string, bool>::const_iterator> get_src_state();

	virtual bool get_state() = 0;
	virtual int pulse(string name, bool pulse) = 0; // no out = 0, low out = 1, high out = 2

	friend void read_modules(std::istream &);
};

/* ********************************************************************************************** *
 *                         Broadcast, Receive, FlipFlop - Derived Classes                         *
 * ********************************************************************************************** */

class Broadcast : public Module {
public:
	Broadcast() : Module(true) { }
	bool get_state() override;
	int pulse(string name, bool pulse) override;
};
class Receive : public Module {
public:
	Receive() : Module(true) { }
	bool get_state() override;
	int pulse(string name, bool pulse) override;
};
class FlipFlop : public Module {
	bool state = false;

public:
	FlipFlop() : Module(true) { }
	bool get_state() override;
	int pulse(string name, bool pulse) override;
};
class Conjunction : public Module {
public:
	Conjunction() : Module(false) { }
	bool get_state() override;
	int pulse(string name, bool pulse) override;
};

/* ********************************************************************************************** *
 *                                  Related Types and Functions                                   *
 * ********************************************************************************************** */

enum MODULE_TYPE : int { BROADCAST, RECEIVE, FLIPFLOP, CONJUNCTION, MODULE_TYPE_ERROR = -1 };
MODULE_TYPE get_module_type(const string &);

void read_modules(std::istream &);
bool is_fresh(set<string>);
