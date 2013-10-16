//
//  Pack_test.cpp
//  proj3
//
//  Created by John West on 10/14/13.
//  Copyright (c) 2013 John West. All rights reserved.
//

/* Pack_test.cpp
 *
 * Unit tests for Card
 *
 */

#include "Pack.h"
#include "Card.h"
#include <cassert>
#include <iostream>
using namespace std;

int main() {

	Card king_diamonds = {KING, DIAMONDS};
	Card nine_clubs = {NINE, CLUBS};

	////////////////////////////////////////
	// Pack_init() unit tests
	Pack pack;
	Pack pack2;

	Pack_init(&pack, "pack.in");
	Pack_init(&pack2, "pack2.in");

	Card nine_spades = {NINE, SPADES};
	Card first_card = *(pack.next);
	assert(Card_compare(&first_card, &nine_spades) == 0);
	
	Card ace_diamonds = {ACE, DIAMONDS};
	Card last_card = *(pack.cards + PACK_SIZE - 1);
	assert(Card_compare(&last_card, &ace_diamonds) == 0);

	Card first_card2 = pack2.cards[0];
	Card seventh_card2 = pack2.cards[6];
	Card last_card2 = pack2.cards[23];

	Card ten_diamonds = {TEN, DIAMONDS};
	Card queen_hearts = {QUEEN, HEARTS};
	Card queen_spades = {QUEEN, SPADES};

	assert(Card_compare(&first_card2, &ten_diamonds) == 0);
	assert(Card_compare(&seventh_card2, &queen_hearts) == 0);
	assert(Card_compare(&last_card2, &queen_spades) == 0);

	////////////////////////////////////////
	// Pack_print() unit tests (unchecked)
	Pack_print(&pack);
	Pack_print(&pack2);
	
	////////////////////////////////////////
	// Pack_deal_one() unit tests
	Card c = Pack_deal_one(&pack);
	assert( Card_compare(&c, &nine_spades) == 0 );
	assert(Card_compare(&first_card, &nine_spades) == 0);
	
	Card ten_spades = {TEN, SPADES};
	c = Pack_deal_one(&pack);
	assert( Card_compare(&c, &ten_spades) == 0 );

	for (int i = 0; i < PACK_SIZE - 2; i++) {
		c = Pack_deal_one(&pack);
	}

	assert(Card_compare(&c, &ace_diamonds) == 0);

	for (int i = 0; i < 7; i++) {
		c = Pack_deal_one(&pack2);
	}

	assert(Card_compare(&c, &queen_hearts) == 0);

	for (int i = 0; i < 17; i++) {
		c = Pack_deal_one(&pack2);
	}

	assert(Card_compare(&c, &queen_spades) == 0);

	////////////////////////////////////////
	// Pack_reset() unit tests
	Pack_reset(&pack);
	first_card = *(pack.next);
	assert(Card_compare(&first_card, &nine_spades) == 0);

	Pack_reset(&pack2);
	Card reset_first = *(pack2.next);
	assert(Card_compare(&reset_first, &ten_diamonds) == 0);
	
	////////////////////////////////////////
	// Pack_shuffle() unit tests
	Pack_deal_one(&pack);
	Pack_shuffle(&pack);
	Pack_print(&pack);

	first_card = *(pack.next);
	assert(Card_compare(&first_card, &queen_spades) == 0);
	
	Card jack_spades = {JACK, SPADES};
	last_card = *(pack.cards + PACK_SIZE - 1);
	assert(Card_compare(&last_card, &jack_spades) == 0);

	Pack_deal_one(&pack2);
	Pack_shuffle(&pack2);
	Pack_print(&pack2);

	first_card2 = *(pack2.next);
	assert(Card_compare(&first_card2, &king_diamonds) == 0);

	Card card_four = *(pack2.cards + 3);
	assert(Card_compare(&card_four, &queen_hearts) == 0);

	last_card2 = *(pack2.cards + PACK_SIZE - 1);
	assert(Card_compare(&last_card2, &nine_clubs) == 0);

	// if we got to the end without calling an assert(), the tests passed
	cout << endl << "Pack_test PASS" << endl;
	
	return 0;
}