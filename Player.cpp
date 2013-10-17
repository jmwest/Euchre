//
//  Player.cpp
//  proj3
//
//  Created by John West on 10/14/13.
//  Copyright (c) 2013 John West. All rights reserved.
//

#include "Player.h"
#include <iostream>

using namespace std;

const char *SUIT_NAME[] = {"Spades", "Hearts", "Clubs", "Diamonds"};
const char *RANK_NAME[] = {"Two", "Three", "Four", "Five", "Six",
    "Seven", "Eight", "Nine", "Ten", "Jack",
    "Queen", "King", "Ace"};

void Player_init(Player *player_ptr, const char *name)
{
	int last_index = 0;

	for (int i = 0; name[i] != '\0'; i++) {
		last_index = i;

		player_ptr->name[i] = name[i];
	}

	player_ptr->name[last_index + 1] = '\0';

	player_ptr->hand_size = 0;

	return;
}

void Player_print(const Player *player_ptr)
{
	cout << endl << player_ptr->name << " has "
		<< player_ptr->hand_size << " cards." << endl;

	for (int i = 0; i < player_ptr->hand_size; i++)
	{
		cout << RANK_NAME[player_ptr->hand[i].rank] << " of "
			<< SUIT_NAME[player_ptr->hand[i].suit] << endl;
	}

	return;
}

void Player_add_card(Player *player_ptr, const Card *c)
{
	player_ptr->hand[player_ptr->hand_size] = *c;

	player_ptr->hand_size++;

	return;
}

Make_response Player_make_trump(const Player *player_ptr, const Card *upcard, Player *dealer, int round)
{
	Make_response player_response;
	
	player_response.orderup = false;

	if (round == 1)
	{
		int trump_face = 0;
		player_response.trump = upcard->suit;

		for (int i = 0; i < 5; i++)
		{
			if (Card_is_trump(&player_ptr->hand[i], upcard->suit)
				&& (player_ptr->hand[i].rank >= 9))
			{
				trump_face++;
			}
		}

		if (trump_face >= 2)
		{
			player_response.orderup = true;

			return player_response;
		}
		else
		{
			return player_response;
		}
	}
	else
	{
		player_response.trump = Suit_next(upcard->suit);

		if (player_ptr == dealer)
		{
			player_response.orderup = true;

			return player_response;
		}

		for (int i = 0; i < 5; i++)
		{
			if (Card_is_trump(&player_ptr->hand[i], upcard->suit)
				&& (player_ptr->hand[i].rank >= 9))
			{
				player_response.orderup = true;

				return player_response;
			}
		}

		return player_response;
	}
}

void Player_add_and_discard(Player *player_ptr, const Card *upcard, Suit trump)
{
	int card_to_discard = 0;

	for (int i = 1; i < player_ptr->hand_size; i++)
	{
		if (Card_compare(&player_ptr->hand[card_to_discard], &player_ptr->hand[i], trump) > 0)
		{
			card_to_discard = i;
		}
	}

	if (Card_compare(&player_ptr->hand[card_to_discard], upcard, trump) > 0)
	{
		return;
	}
	else
	{
		player_ptr->hand[card_to_discard] = *upcard;
	}

	return;
}

Card Player_lead_card(Player *player_ptr, Suit trump)
{
	Card card_to_lead = player_ptr->hand[0];
	int index_of_lead_card = 0;

	for (int i = 1; i < player_ptr->hand_size; i++)
	{
		if ((Card_is_trump(&card_to_lead, trump))
			&& Card_is_trump(&player_ptr->hand[i], trump))
		{
			if (Card_compare(&card_to_lead, &player_ptr->hand[i], trump) < 0)
			{
				card_to_lead = player_ptr->hand[i];
				index_of_lead_card = i;
			}
		}
		else if (Card_is_trump(&card_to_lead, trump)
				 && !Card_is_trump(&player_ptr->hand[i], trump))
		{
			card_to_lead = player_ptr->hand[i];
			index_of_lead_card = i;
		}
		else if (!Card_is_trump(&card_to_lead, trump)
				 && !Card_is_trump(&player_ptr->hand[i], trump))
		{
			if (Card_compare(&card_to_lead, &player_ptr->hand[i]) < 0)
			{
				card_to_lead = player_ptr->hand[i];
				index_of_lead_card = i;
			}
		}
	}

	player_ptr->hand[index_of_lead_card] = player_ptr->hand[player_ptr->hand_size - 1];
	player_ptr->hand[player_ptr->hand_size - 1] = card_to_lead;

	player_ptr->hand_size--;

	return card_to_lead;
}

Card Player_play_card(Player *player_ptr, Suit led_suit, Suit trump)
{
	bool can_follow_lead = false;
	int cards_following_led[5];
	int number_cards_following_led = 0;
	Card card_to_play;
	int index_of_played_card;
	
	for (int i = 0; i < player_ptr->hand_size; i++)
	{
		if (player_ptr->hand[i].suit == led_suit)
		{
			can_follow_lead = true;
			cards_following_led[number_cards_following_led] = i;
			number_cards_following_led++;
		}
	}

	if (can_follow_lead)
	{
		card_to_play = player_ptr->hand[cards_following_led[0]];
		index_of_played_card = cards_following_led[0];

		for (int j = 1; j < number_cards_following_led; j++)
		{
			if (Card_compare(&card_to_play, &player_ptr->hand[cards_following_led[j]]) < 0)
			{
				card_to_play = player_ptr->hand[cards_following_led[j]];
				index_of_played_card = cards_following_led[j];
			}
		}
	}
	else
	{
		card_to_play = player_ptr->hand[0];
		index_of_played_card = 0;

		for (int k = 1; k < player_ptr->hand_size; k++)
		{
			if (Card_compare(&card_to_play, &player_ptr->hand[k], trump, led_suit) > 0)
			{
				card_to_play = player_ptr->hand[k];
				index_of_played_card = k;
			}
		}
	}

	player_ptr->hand[index_of_played_card] = player_ptr->hand[player_ptr->hand_size - 1];
	player_ptr->hand[player_ptr->hand_size - 1] = card_to_play;
	
	player_ptr->hand_size--;

	return card_to_play;
}