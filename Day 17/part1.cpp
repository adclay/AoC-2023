#include "header.h"

typedef tuple<int, int, bool> vertex;

int part1(std::istream &fin) {
	vector<vector<int>> cost_map;
	for (string line; getline(fin, line);) {
		vector<int> cost_line;
		transform(line.cbegin(), line.cend(), back_inserter(cost_line), [](char c) { return c - '0'; });
		cost_map.push_back(cost_line);
	}
	const int N = cost_map.size(), M = cost_map[0].size();

	/* Create digraph
	   - The vertices represent the x,y coordinates of a city block and the directionality (north-
	     south (true) or east-west (false)) the crucible is facing.
	   - An edge uv exists if a crucible can change from position u to position v by moving in a
	     straight line and subsequently turning 90 degrees.
	   - The graph is represented as a list of neighbor,cost pairs for each vertex.               */
	map<vertex, vector<pair<vertex, int>>> digraph;
	for (int n = 0; n != N; ++n) {
		for (int m = 0; m != M; ++m) {
			// North-South
			vertex v = vertex(n, m, true);
			for (int offset = 1, cost = 0; offset != 4 && n - offset != -1; ++offset) {
				cost += cost_map[n - offset][m];
				digraph[v].push_back(make_pair(vertex(n - offset, m, false), cost));
				digraph[v].push_back(make_pair(vertex(n - offset, m, false), cost));
			}
			for (int offset = 1, cost = 0; offset != 4 && n + offset != N; ++offset) {
				cost += cost_map[n + offset][m];
				digraph[v].push_back(make_pair(vertex(n + offset, m, false), cost));
				digraph[v].push_back(make_pair(vertex(n + offset, m, false), cost));
			}

			// East-West
			get<2>(v) = false;
			for (int offset = 1, cost = 0; offset != 4 && m - offset != -1; ++offset) {
				cost += cost_map[n][m - offset];
				digraph[v].push_back(make_pair(vertex(n, m - offset, true), cost));
				digraph[v].push_back(make_pair(vertex(n, m - offset, true), cost));
			}
			for (int offset = 1, cost = 0; offset != 4 && m + offset != M; ++offset) {
				cost += cost_map[n][m + offset];
				digraph[v].push_back(make_pair(vertex(n, m + offset, true), cost));
				digraph[v].push_back(make_pair(vertex(n, m + offset, true), cost));
			}
		}
	}

	// Do Dijkstra
	map<vertex, int> distance;
	transform(digraph.cbegin(), digraph.cend(), inserter(distance, distance.end()), [](pair<const vertex, vector<pair<vertex, int>>> x) { return make_pair(x.first, 0x7fffffff); });
	set<vertex> frontier;
	for (bool dir : { true, false }) {
		vertex v = vertex(0, 0, dir);
		distance[v] = 0;
		for (const auto &e : digraph[v]) {
			distance[e.first] = e.second;
			frontier.insert(e.first);
		}
	}
	while (!frontier.empty()) {
		// Find closest unvisited vertex
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

		// Update neighbors' costs
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
