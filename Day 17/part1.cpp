#include "header.h"

/*
Note: This solution takes about a minute to run. One way to optimize this approach would be to only
include 2 vertices for each city block instead of 4. An optimal path to reach a city block facing
a certain direction is also optimal to reach it facing the opposite direction, so those vertices can
be merged.
*/

typedef tuple<int, int, char> vertex;

int part1(std::istream &fin) {
	vector<vector<int>> cost_map;
	for (string line; getline(fin, line);) {
		vector<int> cost_line;
		transform(line.cbegin(), line.cend(), back_inserter(cost_line), [](char c) { return c - '0'; });
		cost_map.push_back(cost_line);
	}
	const int N = cost_map.size(), M = cost_map[0].size();

	/* Create digraph
	   - The vertices represent the x,y coordinates of a city block and the direction (^<v>) the
	     crucible is facing.
	   - An edge uv exists if a crucible can change from position u to position v by moving in a
	     straight line and subsequently turning 90 degrees.
	   - The graph is represented as a list of neighbor,cost pairs for each vertex.               */
	map<vertex, vector<pair<vertex, int>>> digraph;
	for (int n = 0; n != N; ++n) {
		for (int m = 0; m != M; ++m) {
			vertex v;
			int cost;

			// Left
			v = make_tuple(n, m, '<');
			cost = 0;
			for (int offset = 1; offset < 4 && m - offset >= 0; ++offset) {
				cost += cost_map[n][m - offset];
				digraph[v].push_back(make_pair(vertex(n, m - offset, '^'), cost));
				digraph[v].push_back(make_pair(vertex(n, m - offset, 'v'), cost));
			}

			// Right
			v = make_tuple(n, m, '>');
			cost = 0;
			for (int offset = 1; offset < 4 && m + offset < M; ++offset) {
				cost += cost_map[n][m + offset];
				digraph[v].push_back(make_pair(vertex(n, m + offset, '^'), cost));
				digraph[v].push_back(make_pair(vertex(n, m + offset, 'v'), cost));
			}

			// Up
			v = make_tuple(n, m, '^');
			cost = 0;
			for (int offset = 1; offset < 4 && n - offset >= 0; ++offset) {
				cost += cost_map[n - offset][m];
				digraph[v].push_back(make_pair(vertex(n - offset, m, '<'), cost));
				digraph[v].push_back(make_pair(vertex(n - offset, m, '>'), cost));
			}

			// Down
			v = make_tuple(n, m, 'v');
			cost = 0;
			for (int offset = 1; offset < 4 && n + offset < N; ++offset) {
				cost += cost_map[n + offset][m];
				digraph[v].push_back(make_pair(vertex(n + offset, m, '<'), cost));
				digraph[v].push_back(make_pair(vertex(n + offset, m, '>'), cost));
			}
		}
	}

	// Do Dijkstra
	map<vertex, int> distance;
	transform(digraph.cbegin(), digraph.cend(), inserter(distance, distance.end()), [](pair<const vertex, vector<pair<vertex, int>>> x) { return make_pair(x.first, 0x7fffffff); });
	set<vertex> frontier;
	for (char c : { '<', '>', '^', 'v' }) {
		vertex v = vertex(0, 0, c);
		distance[v] = 0;
		for (const auto &e : digraph[v]) {
			distance[e.first] = e.second;
			frontier.insert(e.first);
		}
	}
	while (!frontier.empty()) {
		// Find closest vertex
		vertex v;
		int d = 0x7fffffff;
		for (const vertex &u : frontier) {
			if (distance[u] < d) {
				v = u;
				d = distance[u];
			}
		}
		frontier.erase(v);

		// Return if we've reached the end
		if (get<0>(v) == N - 1 && get<1>(v) == M - 1) {
			return d;
		}

		// Remove vertex from frontier and update neighbors' costs
		for (const auto &e : digraph[v]) {
			int new_d = d + e.second;
			if (new_d < distance[e.first]) {
				distance[e.first] = new_d;
				frontier.insert(e.first);
			}
		}
	}
	return -1;
}
