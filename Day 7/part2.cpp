#include "header.h"

static inline int card_strength(const char c) {
	switch (c) {
	case 'A':
		return 12;
	case 'K':
		return 11;
	case 'Q':
		return 10;
	case 'T':
		return 9;
	case '9':
		return 8;
	case '8':
		return 7;
	case '7':
		return 6;
	case '6':
		return 5;
	case '5':
		return 4;
	case '4':
		return 3;
	case '3':
		return 2;
	case '2':
		return 1;
	case 'J':
		return 0;
	default:
		return -1;
	}
}

static inline int _hand_type(const int sets[5]) {
	if (sets[4]) return 6;            // Five of a kind
	if (sets[3]) return 5;            // Four of a kind
	if (sets[2] && sets[1]) return 4; // Full house
	if (sets[2]) return 3;            // Three of a kind
	if (2 == sets[1]) return 2;       // Two pair
	if (sets[1]) return 1;            // One pair
	return 0;                         // High card
}

static int get_hand_type(const string hand) {
	int cards[13] = { 0 };
	int sets[5] = { 0 };

	for (char c : hand) {
		cards[card_strength(c)] += 1;
	}
	for (int i = 1; i < 13; ++i) {
		if (cards[i]) {
			sets[cards[i] - 1] += 1;
		}
	}
	if (cards[0]) {
		if (5 == cards[0]) {
			sets[4] = 1;
		}
		else {
			for (int i = 4 - cards[0]; i >= 0; --i) {
				if (sets[i]) {
					sets[i + cards[0]] += 1;
					sets[i] -= 1;
					break;
				}
			}
		}
	}
	return _hand_type(sets);
}

static bool cmp(const hand_bid &a, const hand_bid &b) {
	int cards[13] = { 0 };
	int sets[5] = { 0 };
	
	int a_type = get_hand_type(a.hand);
	int b_type = get_hand_type(b.hand);

	// Return if a and b are different hand types
	if (a_type < b_type) {
		return true;
	}
	else if (a_type > b_type) {
		return false;
	}

	// Find first different card
	for (int i = 0; i < a.hand.size(); ++i) {
		if (card_strength(a.hand[i]) < card_strength(b.hand[i])) {
			return true;
		}
		else if (card_strength(a.hand[i]) > card_strength(b.hand[i])) {
			return false;
		}
	}
	return false;
}

int part2(std::istream &fin) {
	vector<hand_bid> hands;
	string word;
	int bid;

	while (fin >> word >> bid) {
		hands.push_back({ word, bid });
	}
	sort(hands.begin(), hands.end(), cmp);

	int retval = 0;
	for (int i = 0; i < hands.size(); ++i) {
		retval += (i + 1) * hands[i].bid;
	}
	return retval;
}
