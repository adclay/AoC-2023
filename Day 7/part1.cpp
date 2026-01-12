#include "header.h"

static inline int card_strength(char c) {
	switch (c) {
		case 'A':
			return 12;
		case 'K':
			return 11;
		case 'Q':
			return 10;
		case 'J':
			return 9;
		case 'T':
			return 8;
		case '9':
			return 7;
		case '8':
			return 6;
		case '7':
			return 5;
		case '6':
			return 4;
		case '5':
			return 3;
		case '4':
			return 2;
		case '3':
			return 1;
		case '2':
			return 0;
		default:
			return -1;
	}
}

static inline int hand_type(int sets[5]) {
	if (sets[4]) return 6;            // Five of a kind
	if (sets[3]) return 5;            // Four of a kind
	if (sets[2] && sets[1]) return 4; // Full house
	if (sets[2]) return 3;            // Three of a kind
	if (2 == sets[1]) return 2;       // Two pair
	if (sets[1]) return 1;            // One pair
	return 0;                         // High card
}

static bool cmp(const hand_bid &a, const hand_bid &b) {
	int cards[13] = { 0 };
	int sets[5] = { 0 };

	// Determine type of a
	for (char c : a.hand) {
		cards[card_strength(c)] += 1;
	}
	for (int &card : cards) {
		if (card) {
			sets[card - 1] += 1;
			card = 0;
		}
	}
	int a_type = hand_type(sets);

	// Determine type of b
	for (int &set : sets) {
		set = 0;
	}
	for (char c : b.hand) {
		cards[card_strength(c)] += 1;
	}
	for (int card : cards) {
		if (card) {
			sets[card - 1] += 1;
		}
	}
	int b_type = hand_type(sets);

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

int part1(std::istream &fin) {
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
