//
//  Game.cpp
//  proj3
//
//  Created by John West on 10/18/13.
//  Copyright (c) 2013 John West. All rights reserved.
//

#include <iostream>
#include "Game.h"

using namespace std;

//REQUIRES: game_ptr is initialized
//MODIFIES: game_ptr
//EFFECTS: If the shuffle option is selected shuffle the pack.
//			Otherwise, reset the pack.
static void Game_shuffle(Game *game_ptr);

//
static void Game_deal_hands(Game *game_ptr, Player *dealer, const int dealer_num);

//
static void Game_deal_card(Game *game_ptr, Player *dealer, const int dealer_num);

//
static Suit Game_select_trump(Game *game_ptr, Player *dealer, const int dealer_num, Card *upcard, int &team_made);

//
static void Game_play_hand(Game *game_ptr, Suit trump, Player *dealer, int dealer_num, int team_made);

//
static void Game_print_hand_and_dealer(const int &hand, const Player *dealer);

//
static void Game_print_turnup(const Card *card);

//
static void Game_print_passes(const Player *player);

//
static void Game_print_orderup(const Player *player, const Suit &suit);

//
static void Game_print_led(const Player *player, const Card *card);

//
static void Game_print_play(const Player *player, const Card *card);

//
static void Game_print_trick_winner(const Player *player);

//
static void Game_print_hand_winner(const Game *game_ptr, const int &team_won);

//
static void Game_print_team_score(const Game *game_ptr, const int &team);

static void Game_print_winners(const Game *game_ptr, const int &team);

//
static int Player_left(int player_index);

const char *suit_names[] = {"Spades", "Hearts", "Clubs", "Diamonds"};
const char *rank_names[] = {"Two", "Three", "Four", "Five", "Six",
    "Seven", "Eight", "Nine", "Ten", "Jack",
    "Queen", "King", "Ace"};
const int TEAM_ONE = 0;
const int TEAM_TWO = 1;

void Game_init(Game *game_ptr, const char *pack_filename, bool shuffle, int points_to_win, const char *player_names[])
{
	Pack_init(&game_ptr->pack, pack_filename);

	game_ptr->shuffle = shuffle;

	game_ptr->score[0] = 0;
	game_ptr->score[1] = 0;

	game_ptr->points_to_win = points_to_win;

	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		Player_init((game_ptr->players + i), player_names[i]);
	}
}

void Game_play(Game *game_ptr)
{
	int dealer = 0;
	Card upcard;
	Suit trump;
	int team_made = 0;
	int hand = 0;

	while ((game_ptr->points_to_win > game_ptr->score[0])
		   and (game_ptr->points_to_win > game_ptr->score[1]))
	{
		Game_shuffle(game_ptr);

		Game_print_hand_and_dealer(hand, &game_ptr->players[dealer]);

		Game_deal_hands(game_ptr, &game_ptr->players[dealer], dealer);

		upcard = Pack_deal_one(&game_ptr->pack);

		Game_print_turnup(&upcard);

		trump = Game_select_trump(game_ptr, &game_ptr->players[dealer], dealer, &upcard, team_made);

		Game_play_hand(game_ptr, trump, &game_ptr->players[dealer], dealer, team_made);

		dealer = Player_left(dealer);
		hand = hand + 1;
	}

	if (game_ptr->score[TEAM_ONE] > game_ptr->score[TEAM_TWO])
	{
		Game_print_winners(game_ptr, TEAM_ONE);
	}
	else
	{
		Game_print_winners(game_ptr, TEAM_TWO);
	}

	return;
}

static void Game_shuffle(Game *game_ptr)
{
	if (game_ptr->shuffle)
	{
		Pack_shuffle(&game_ptr->pack);
	}
	else
	{
		Pack_reset(&game_ptr->pack);
	}

	return;
}

static void Game_deal_hands(Game *game_ptr, Player *dealer, const int dealer_num)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 1; j < 5; j++)
		{
			if ((i == 0) and (j % 2 == 1))
			{
				for (int k = 0; k < 3; k++)
				{
					Game_deal_card(game_ptr, dealer, ((dealer_num + j) % 4));
				}
			}
			else if ((i == 0) and (j % 2 == 0))
			{
				for (int k = 0; k < 2; k++)
				{
					Game_deal_card(game_ptr, dealer, ((dealer_num + j) % 4));
				}
			}
			else if ((i == 1) and (j % 2 == 1))
			{
				for (int k = 0; k < 2; k++)
				{
					Game_deal_card(game_ptr, dealer, ((dealer_num + j) % 4));
				}
			}
			else if ((i == 1) and (j % 2 == 0))
			{
				for (int k = 0; k < 3; k++)
				{
					Game_deal_card(game_ptr, dealer, ((dealer_num + j) % 4));
				}
			}
		}
	}

	return;
}

static void Game_deal_card(Game *game_ptr, Player *dealer, const int dealer_num)
{
	Card next_card = Pack_deal_one(&game_ptr->pack);
	
	Player_add_card(&game_ptr->players[dealer_num],
					&next_card);
}

static Suit Game_select_trump(Game *game_ptr, Player *dealer, const int dealer_num, Card *upcard, int &team_made)
{
	Make_response player_response = {false, DIAMONDS};
	Player *current_player;
	int round = 1;

	while (!player_response.orderup and round < 3)
	{
		for (int j = 1; !player_response.orderup and j < 5; j++)
		{
			current_player = &game_ptr->players[((dealer_num + j) % 4)];

			player_response = Player_make_trump(current_player, upcard, dealer, round);

			team_made = (dealer_num + j) % 2;

			if (!player_response.orderup) {
				Game_print_passes(&game_ptr->players[(dealer_num + j) % 4]);
			}
			else
			{
				Game_print_orderup(&game_ptr->players[(dealer_num + j) % 4], player_response.trump);
			}
		}

		round++;
	}

	if (round == 1)
	{
		Player_add_and_discard(dealer, upcard, player_response.trump);
	}

	return player_response.trump;
}

static int Player_left(int player_index)
{
	return (player_index + 1) % 4;
}

static void Game_play_hand(Game *game_ptr, Suit trump, Player *dealer, int dealer_num, int team_made)
{
	int lead_player = Player_left(dealer_num);
	int highest_card = 0;
	int team_one_tricks = 0;
	int team_two_tricks = 0;
	int team_won = 0;
	Card cards_played[4];

	for (int i = 0; i < 5; i++)
	{
		cards_played[0] = Player_lead_card(&game_ptr->players[lead_player], trump);

		Game_print_led(&game_ptr->players[lead_player], &cards_played[0]);

		for (int j = 1; j < 4; j++)
		{
			cards_played[j] = Player_play_card(&game_ptr->players[(lead_player + j) % 4], cards_played[0].suit, trump);

			Game_print_play(&game_ptr->players[(lead_player + j) % 4], &cards_played[j]);

			if (Card_compare(&cards_played[highest_card], &cards_played[j], trump, cards_played[0].suit) < 0)
			{
				highest_card = j;
			}
		}

		if ((((lead_player + highest_card) % 4) % 2) == 0)
		{
			team_one_tricks = team_one_tricks + 1;
		}
		else
		{
			team_two_tricks = team_two_tricks + 1;
		}

		Game_print_trick_winner(&game_ptr->players[(lead_player + highest_card) % 4]);

		lead_player = (lead_player + highest_card) % 4;
		highest_card = 0;
	}

	if (team_one_tricks > team_two_tricks)
	{
		team_won = TEAM_ONE;
	}
	else
	{
		team_won = TEAM_TWO;
	}

	Game_print_hand_winner(game_ptr, team_won);

	if (team_won != team_made)
	{
		game_ptr->score[team_won] = game_ptr->score[team_won] + 2;
		cout << "euchred!" << endl;
	}
	else
	{
		if ((team_one_tricks == 5) or (team_two_tricks == 5))
		{
			game_ptr->score[team_won] = game_ptr->score[team_won] + 2;
			cout << "march!" << endl;
		}
		else
		{
			game_ptr->score[team_won] = game_ptr->score[team_won] + 1;
		}
	}

	Game_print_team_score(game_ptr, TEAM_ONE);
	Game_print_team_score(game_ptr, TEAM_TWO);

	return;
}

static void Game_print_hand_and_dealer(const int &hand, const Player *dealer)
{
	cout << endl << "Hand " << hand << endl;
	cout << dealer->name << " deals" << endl;

	return;
}

static void Game_print_turnup(const Card *card)
{
	cout << rank_names[card->rank] << " of " << suit_names[card->suit] << " turned up" << endl;

	return;
}

static void Game_print_passes(const Player *player)
{
	cout << player->name << " passes" << endl;

	return;
}

static void Game_print_orderup(const Player *player, const Suit &suit)
{
	cout << player->name << " orders up " << suit_names[suit] << endl;

	return;
}

static void Game_print_led(const Player *player, const Card *card)
{
	cout << endl;
	cout << rank_names[card->rank] << " of " << suit_names[card->suit] << " led by " << player->name << endl;

	return;
}

static void Game_print_play(const Player *player, const Card *card)
{
	cout << rank_names[card->rank] << " of " << suit_names[card->suit] << " played by " << player->name << endl;

	return;
}

static void Game_print_trick_winner(const Player *player)
{
	cout << player->name << " takes the trick" << endl;

	return;
}

static void Game_print_hand_winner(const Game *game_ptr, const int &team_won)
{
	cout << endl << game_ptr->players[team_won].name << " and " << game_ptr->players[team_won + 2].name << " win the hand" << endl;

	return;
}

static void Game_print_team_score(const Game *game_ptr, const int &team)
{
	cout << game_ptr->players[team].name << " and " << game_ptr->players[team + 2].name << " have " << game_ptr->score[team] << " points" << endl;

	return;
}

static void Game_print_winners(const Game *game_ptr, const int &team)
{
	cout << endl << game_ptr->players[team].name << " and " << game_ptr->players[team + 2].name << " win!" << endl;

	return;
}