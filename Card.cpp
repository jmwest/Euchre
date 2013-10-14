//
//  Card.cpp
//  proj3
//
//  Created by John West on 10/9/13.
//  Copyright (c) 2013 John West. All rights reserved.
//

#include "Card.h"
#include <cassert>
#include <cstring>
#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
const char *SUIT_NAMES[] = {"Spades", "Hearts", "Clubs", "Diamonds"};
const int SUIT_NAMES_SIZE = 4;
const char *RANK_NAMES[] = {"Two", "Three", "Four", "Five", "Six",
    "Seven", "Eight", "Nine", "Ten", "Jack",
    "Queen", "King", "Ace"};
const int RANK_NAMES_SIZE = 13;


////////////////////////////////////////////////////////////////////////////////
void Suit_print(Suit suit) {
    cout << SUIT_NAMES[suit];
}

Suit Suit_next(Suit suit) {
    switch (suit) {
        case SPADES:   return CLUBS;
        case HEARTS:   return DIAMONDS;
        case CLUBS:    return SPADES;
        case DIAMONDS: return HEARTS;
        default:       assert(0); // should never get here
    }
}


////////////////////////////////////////////////////////////////////////////////
// Card

void Card_init(Card *card_ptr, Rank rank, Suit suit) {
    card_ptr->rank = rank;
    card_ptr->suit = suit;
}

void Card_print(const Card *card_ptr) {
    cout << RANK_NAMES[card_ptr->rank] << " of " << SUIT_NAMES[card_ptr->suit];
}

bool Card_is_face(const Card *card_ptr) {
    return
    card_ptr->rank == JACK ||
    card_ptr->rank == QUEEN ||
    card_ptr->rank == KING ||
    card_ptr->rank == ACE;
}

bool Card_is_right_bower(const Card *card_ptr, Suit trump) {
    return card_ptr->rank == JACK && card_ptr->suit == trump; // JACK of trump suit
}

bool Card_is_left_bower(const Card *card_ptr, Suit trump) {
    return card_ptr->rank == JACK &&
    card_ptr->suit == Suit_next(trump); // JACK of trump's color
}

bool Card_is_trump(const Card *card_ptr, Suit trump) {
    return card_ptr->suit == trump ||
    Card_is_left_bower(card_ptr,trump);
}

int Card_compare_suit(const Card *a, Suit s, Suit trump) {
    assert(a);
    
    // one suit is trump
    if (Card_is_trump(a,trump) && s != trump) return 1;
    if (!Card_is_trump(a,trump) && s == trump) return -1;
    
    // both trump
    if (Card_is_trump(a,trump) && s == trump) return 0;
    
    // neither trump
    return a->suit - s;
}

int Card_compare(const Card *a, const Card *b) {
    
    // sanity check for NULL pointers
    assert(a);
    assert(b);
    
    // To simplify debugging and ensure that every correct solution will get the
    // same output, we’ve added an additional rule here.  In addition to being
    // ordered by rank, cards are also ordered by suit.
    return (a->rank + a->suit + a->rank*SUIT_NAMES_SIZE)
			-  (b->rank + b->suit + b->rank*SUIT_NAMES_SIZE);
}


void Card_init(Card *card_ptr, const char* rank, const char* suit)
{
    for (int i = 0; i < RANK_NAMES_SIZE; i++) {
		for (int j = 0; (*(RANK_NAMES[i] + j) == *(rank + j)) && (j < 3); j++) {
			if (j == 2)
			{
				card_ptr->rank = static_cast<Rank>(i);
			}
		}
    }

    for (int i = 0; i < SUIT_NAMES_SIZE; i++) {
		if (*SUIT_NAMES[i] == *suit)
		{
			card_ptr->suit = static_cast<Suit>(i);
		}
    }

    return;
}


int Card_compare(const Card *a, const Card *b, Suit trump)
{
	assert(a);
	assert(b);

	if (Card_is_trump(a, trump) and !Card_is_trump(b, trump)) {
		return 1;
	}
	else if (!Card_is_trump(a, trump) and Card_is_trump(b, trump)) {
		return -1;
	}
	else {
		if (Card_is_right_bower(a, trump) and !Card_is_right_bower(b, trump))
		{
			return 1;
		}
		else if (!Card_is_right_bower(a, trump) and Card_is_right_bower(b, trump))
		{
			return -1;
		}
		else if (Card_is_left_bower(a, trump) and !Card_is_left_bower(b, trump))
		{
			return 1;
		}
		else if (!Card_is_left_bower(a, trump) and Card_is_left_bower(b, trump))
		{
			return -1;
		}

		return (a->rank + a->suit + a->rank*SUIT_NAMES_SIZE)
				- (b->rank + b->suit + b->rank*SUIT_NAMES_SIZE);
	}
}


int Card_compare(const Card *a, const Card *b, Suit trump, Suit led)
{
	assert(a);
	assert(b);
	
	if (Card_is_trump(a, trump) and !Card_is_trump(b, trump))
	{
		return 1;
	}
	else if (!Card_is_trump(a, trump) and Card_is_trump(b, trump))
	{
		return -1;
	}
	else if (Card_is_trump(a, trump) or Card_is_trump(b, trump))
	{
		if (Card_is_right_bower(a, trump) and !Card_is_right_bower(b, trump))
		{
			return 1;
		}
		else if (!Card_is_right_bower(a, trump) and Card_is_right_bower(b, trump))
		{
			return -1;
		}
		else if (Card_is_left_bower(a, trump) and !Card_is_left_bower(b, trump))
		{
			return 1;
		}
		else if (!Card_is_left_bower(a, trump) and Card_is_left_bower(b, trump))
		{
			return -1;
		}

		return (a->rank + a->suit + a->rank*SUIT_NAMES_SIZE)
				- (b->rank + b->suit + b->rank*SUIT_NAMES_SIZE);
	}
	else
	{
		if ((a->suit == led) and !(b->suit == led))
		{
			return 1;
		}
		else if (!(a->suit == led) and (b->suit == led))
		{
			return -1;
		}
		else
		{
			return (a->rank + a->suit + a->rank*SUIT_NAMES_SIZE)
					- (b->rank + b->suit + b->rank*SUIT_NAMES_SIZE);

		}
	}
}