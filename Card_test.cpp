//
//  Card_test.cpp
//  proj3
//
//  Created by John West on 10/9/13.
//  Copyright (c) 2013 John West. All rights reserved.
//


#include "Card.h"
#include <cassert>
#include <iostream>

using namespace std;

const Rank Ranks[] = { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };
const Suit Suits[] = { SPADES, HEARTS, CLUBS, DIAMONDS };

int main()
{

	const char *SUIT_NAME[] = {"Spades", "Hearts", "Clubs", "Diamonds"};
	const char *RANK_NAME[] = {"Two", "Three", "Four", "Five", "Six",
		"Seven", "Eight", "Nine", "Ten", "Jack",
		"Queen", "King", "Ace"};

	////////////////////////////////////////
	// Suit_next() unit tests
	Suit s = Suit_next(HEARTS);
	assert(s == DIAMONDS);

	////////////////////////////////////////
	// Card_init() unit tests
	Card two_spades;
	Card_init(&two_spades, TWO, SPADES);
	assert(two_spades.rank == TWO && two_spades.suit == SPADES);


	Card deck[52];

	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 4; j++) {
			Card_init(&deck[(4 * i) + j], RANK_NAME[i], SUIT_NAME[j]);
		}
	}

	for (int k = 0; k < 13; k++) {
		for (int m = 0; m < 4; m++) {
			assert(deck[(4 * k) + m].rank == Ranks[k] && deck[(4 * k) + m].suit == Suits[m]);
		}
	}

	////////////////////////////////////////
	// Card_print() unit tests (unchecked)
	Card_print(&two_spades);
	cout << endl;

	////////////////////////////////////////
	// Card_is_right_bower() unit tests
	Card jack_spades, jack_clubs;
	Card_init(&jack_spades, JACK, SPADES);
	Card_init(&jack_clubs, JACK, CLUBS);
	assert(Card_is_right_bower(&jack_spades, SPADES));
	assert(!Card_is_right_bower(&jack_spades, HEARTS));
	 
	////////////////////////////////////////
	// Card_is_left_bower() unit tests
	assert(Card_is_left_bower(&jack_clubs, SPADES));
	assert(!Card_is_left_bower(&jack_clubs, HEARTS));
	
	////////////////////////////////////////
	// Card_is_trump() unit tests
	assert(Card_is_trump(&jack_clubs, SPADES));
	assert(!Card_is_trump(&jack_clubs, HEARTS));
	
	////////////////////////////////////////
	// Card_compare() unit tests
	Card ace_diamonds, ace_hearts, jack_diamonds;
	Card_init(&ace_diamonds, ACE, DIAMONDS);
	Card_init(&ace_hearts, ACE, HEARTS);
	Card_init(&jack_diamonds, JACK, DIAMONDS);
	assert(Card_compare(&ace_diamonds, &ace_hearts) > 0);
	assert(Card_compare(&ace_hearts, &ace_diamonds) < 0);
	assert(Card_compare(&ace_diamonds, &jack_diamonds) > 0);
	 
	////////////////////////////////////////
	// Card_is_face() unit tests
	assert(Card_is_face(&two_spades) == false);
	assert(Card_is_face(&ace_diamonds) == true);
	
	////////////////////////////////////////
	// Card_compare_suit() unit tests
	assert(Card_compare_suit(&ace_diamonds, HEARTS, SPADES) > 0);
	assert(Card_compare_suit(&jack_spades, SPADES, SPADES) == 0);
	assert(Card_compare_suit(&jack_spades, CLUBS, CLUBS) == 0);
	assert(Card_compare_suit(&jack_spades, CLUBS, DIAMONDS) < 0);
	assert(Card_compare_suit(&jack_spades, SPADES, CLUBS) > 0);
	
	////////////////////////////////////////
	// Card_compare() unit tests
	// these tests will pass once you code
	// int Card_compare(const Card *a, const Card *b, Suit trump);
	assert(Card_compare(&ace_diamonds, &ace_hearts, DIAMONDS) > 0);
	assert(Card_compare(&ace_diamonds, &ace_hearts, HEARTS) < 0);
	assert(Card_compare(&ace_hearts, &ace_diamonds, DIAMONDS) < 0);
	assert(Card_compare(&ace_diamonds, &jack_diamonds, SPADES) > 0);
	assert(Card_compare(&ace_diamonds, &jack_diamonds, DIAMONDS) < 0);
	assert(Card_compare(&jack_clubs, &jack_spades, CLUBS) > 0);
	assert(Card_compare(&jack_clubs, &jack_spades, SPADES) < 0);

	////////////////////////////////////////
	// Card_compare() unit tests
	// these tests will pass once you code
	// int Card_compare(const Card *a, const Card *b, Suit trump, Suit led);
	assert(Card_compare(&ace_diamonds, &ace_hearts, DIAMONDS, CLUBS) > 0);
	assert(Card_compare(&ace_diamonds, &ace_hearts, HEARTS, CLUBS) < 0);
	assert(Card_compare(&ace_hearts, &ace_diamonds, DIAMONDS, CLUBS) < 0);
	assert(Card_compare(&ace_diamonds, &jack_diamonds, SPADES, CLUBS) > 0);
	assert(Card_compare(&ace_diamonds, &jack_diamonds, DIAMONDS, CLUBS) < 0);
	assert(Card_compare(&jack_clubs, &jack_spades, CLUBS, DIAMONDS) > 0);
	assert(Card_compare(&jack_clubs, &jack_spades, SPADES, DIAMONDS) < 0);
	assert(Card_compare(&ace_diamonds, &ace_hearts, DIAMONDS, HEARTS) > 0);
	assert(Card_compare(&ace_diamonds, &ace_hearts, HEARTS, DIAMONDS) < 0);
	assert(Card_compare(&ace_diamonds, &ace_hearts, CLUBS, HEARTS) < 0);
	assert(Card_compare(&ace_diamonds, &ace_hearts, CLUBS, DIAMONDS) > 0);

	// if we got to the end without calling an assert(), the tests passed
    cout << "Card_test PASS" << endl;
    
    return 0;
}
