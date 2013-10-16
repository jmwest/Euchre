//
//  Pack.cpp
//  proj3
//
//  Created by John West on 10/12/13.
//  Copyright (c) 2013 John West. All rights reserved.
//

#include "Pack.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const char *SUITS[] = {"Spades", "Hearts", "Clubs", "Diamonds"};
const char *RANKS[] = {"Two", "Three", "Four", "Five", "Six",
    "Seven", "Eight", "Nine", "Ten", "Jack",
    "Queen", "King", "Ace"};

void Pack_init(Pack *pack_ptr, const char* pack_filename)
{
	ifstream pack_in;
	string rank_string;
	string of_string;
	string suit_string;

	pack_in.open(pack_filename);

	if (pack_in.fail())
	{
		cout << "Error opening " << pack_filename << endl;
		
		exit(EXIT_FAILURE);
	}

	for (int i = 0; !pack_in.eof(); i++)
	{
		if (pack_in.fail())
		{
			cout << "Error opening " << pack_filename << endl;

			exit(EXIT_FAILURE);
		}

		pack_in >> rank_string >> of_string >> suit_string;

		Card_init((pack_ptr->cards + i), rank_string.c_str(), suit_string.c_str());
	}

	pack_ptr->next = pack_ptr->cards;

	pack_in.close();

	return;
}

void Pack_print(const Pack *pack_ptr)
{
	cout << endl;

	for (int i = 0; i < 24; i++)
	{
		cout << RANKS[pack_ptr->cards[i].rank]
			 << " of " << SUITS[pack_ptr->cards[i].suit]
			 << endl;
	}

	return;
}

Card Pack_deal_one(Pack *pack_ptr)
{
	Card next;

	next = *(pack_ptr->next);
	pack_ptr->next++;

	return next;
}

void Pack_reset(Pack *pack_ptr)
{
	pack_ptr->next = pack_ptr->cards;

	return;
}

void Pack_shuffle(Pack *pack_ptr)
{
	Card last_seven[7];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			last_seven[6 - j] = pack_ptr->cards[23 - j];
		}

		for (int k = 0; k < 17; k++)
		{
			pack_ptr->cards[23 - k] = pack_ptr->cards[16 - k];
		}

		for (int m = 0; m < 7; m++)
		{
			pack_ptr->cards[m] = last_seven[m];
		}
	}

	pack_ptr->next = pack_ptr->cards;

	return;
}