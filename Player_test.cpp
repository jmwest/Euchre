//
//  Player_test.cpp
//  proj3
//
//  Created by John West on 10/15/13.
//  Copyright (c) 2013 John West. All rights reserved.
//

/* Player_test.cpp
 *
 * Unit tests for Player
 *
 */

#include "Player.h"
#include "Pack.h"
#include "Card.h"
#include <cassert>
#include <cstring>
#include <iostream>
using namespace std;

int main() {

	////////////////////////////////////////
	// Player_init() unit tests
	Player alice;
	Player_init(&alice, "Alice");
	assert( strcmp(alice.name, "Alice") == 0 );
	assert( alice.hand_size == 0 );

	////////////////////////////////////////
	// Player_add_card() unit tests
	
	// Create player Bob and give him an awesome hand for Spades trump
	Card awesome_spades_hand[MAX_HAND_SIZE] =
    { {QUEEN, SPADES},
		{KING, SPADES},
		{ACE, SPADES},
		{JACK, CLUBS},
		{JACK, SPADES}, };
	Card crappy_hand_for_alice[MAX_HAND_SIZE] =
	{
		{TEN, HEARTS},
		{NINE, SPADES},
		{TEN, SPADES},
		{NINE, DIAMONDS},
		{NINE, CLUBS},
	};

	Player bob;
	Player_init(&bob, "Bob");
	for (int i=0; i<MAX_HAND_SIZE; ++i) {
		Player_add_card(&bob, &awesome_spades_hand[i]);
		assert(bob.hand_size == i+1);

		Player_add_card(&alice, &crappy_hand_for_alice[i]);
		assert(alice.hand_size == i + 1);
	}
	
	// Check that Bob's hand actually has all those spades
	assert(bob.hand_size == MAX_HAND_SIZE);
	for (int i=0; i<MAX_HAND_SIZE; ++i) {
		assert(Card_compare(&bob.hand[i], &awesome_spades_hand[i]) == 0);

		assert(Card_compare(alice.hand + i, crappy_hand_for_alice + i) == 0);
	}

	////////////////////////////////////////
	// Player_print() unit tests (unchecked)
	Player_print(&alice);

	Player_print(&bob);

	////////////////////////////////////////
	// Player_make_trump() unit tests
	// Bob should order up Spades if the upcard is a low Spade
	Card nine_spades;
	Card_init(&nine_spades, NINE, SPADES);
	Make_response bob_response = Player_make_trump
    (&bob,            //Player calling trump
     &nine_spades,    //upcard
     &bob,            //Bob is also the dealer
     1);              //first round
	assert (bob_response.orderup == true);
	assert (bob_response.trump == SPADES);

	Make_response alice_response = Player_make_trump(&alice, &awesome_spades_hand[4], &bob, 1);
	assert(alice_response.orderup == false);
	assert(alice_response.trump == SPADES);
	
	////////////////////////////////////////
	// Player_add_and_discard() unit tests
	// Bob will throw away the upcard if it's lower than the cards in his hand
	Player_add_and_discard(&bob, &nine_spades, SPADES);
	assert(bob.hand_size == 5);
	for (int i=0; i<bob.hand_size; ++i)
		assert(Card_compare(&bob.hand[i], &awesome_spades_hand[i]) == 0);

	Player_add_and_discard(&alice, &awesome_spades_hand[4], SPADES);
	assert(alice.hand_size == 5);
	Player_print(&alice);
	for (int i = 0; i < alice.hand_size - 1; i++) {
		assert(Card_compare(&alice.hand[i], &crappy_hand_for_alice[i]) == 0);
	}
	assert(Card_compare(&alice.hand[4], &awesome_spades_hand[4]) == 0);
	
	////////////////////////////////////////
	// Card Player_lead_card() unit tests
	// Bob has the right bower, the max, which he should play if spades is led
	Card card_led = Player_lead_card(&bob, SPADES);
	Card jack_spades;
	Card_init(&jack_spades, JACK, SPADES);
	assert(Card_compare(&card_led, &jack_spades) == 0);
	bob.hand_size = 5;

	card_led = Player_lead_card(&bob, CLUBS);
	Card ace_spades;
	Card_init(&ace_spades, ACE, SPADES);
	assert(Card_compare(&card_led, &ace_spades) == 0);
	bob.hand_size = 5;

	card_led = Player_lead_card(&bob, HEARTS);
	assert(Card_compare(&card_led, &ace_spades) == 0);
	bob.hand_size = 5;

	card_led = Player_lead_card(&bob, DIAMONDS);
	assert(Card_compare(&card_led, &ace_spades) == 0);

	card_led = Player_lead_card(&alice, SPADES);
	Card ten_hearts;
	Card_init(&ten_hearts, TEN, HEARTS);
	assert(Card_compare(&card_led, &ten_hearts) == 0);
	alice.hand_size = 5;

	card_led = Player_lead_card(&alice, CLUBS);
	assert(Card_compare(&card_led, &ten_hearts) == 0);
	alice.hand_size = 5;

	card_led = Player_lead_card(&alice, HEARTS);
	assert(Card_compare(&card_led, &jack_spades) == 0);
	alice.hand_size = 5;

	card_led = Player_lead_card(&alice, DIAMONDS);
	assert(Card_compare(&card_led, &jack_spades) == 0);

	Player_print(&alice);

	////////////////////////////////////////
	// Player_play_card() unit tests
	// Bob has all spades, so he should play the min if Diamonds is led
	Card card_played = Player_play_card
    (&bob,      //Bob plays the card
     DIAMONDS,  //Diamonds is led
     SPADES);   //Spades is trump
	Card queen_spades;
	Card_init(&queen_spades, QUEEN, SPADES);
	assert(Card_compare(&card_played, &queen_spades) == 0);

	card_played = Player_play_card(&alice, DIAMONDS, SPADES);
	assert(Card_compare(&card_played, &crappy_hand_for_alice[3]) == 0);
	alice.hand_size = 4;

	card_played = Player_play_card(&alice, CLUBS, SPADES);
	assert(Card_compare(&card_played, &crappy_hand_for_alice[3]) == 0);
	alice.hand_size = 4;

	card_played = Player_play_card(&alice, SPADES, SPADES);
	assert(Card_compare(&card_played, &crappy_hand_for_alice[2]) == 0);

	Player_print(&alice);

	card_played = Player_play_card(&alice, SPADES, SPADES);
	assert(Card_compare(&card_played, &crappy_hand_for_alice[1]) == 0);

	Player_print(&alice);

	card_played = Player_play_card(&alice, HEARTS, SPADES);
	assert(Card_compare(&card_played, &crappy_hand_for_alice[0]) == 0);

	Player_print(&alice);

	card_played = Player_play_card(&alice, SPADES, HEARTS);
	assert(Card_compare(&card_played, &crappy_hand_for_alice[3]) == 0);

	Player_print(&alice);

	// if we got to the end without calling an assert(), the tests passed
	cout << endl << "Player_test PASS" << endl;
	
	return 0;
}