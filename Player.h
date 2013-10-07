#ifndef PLAYER_H
#define PLAYER_H
/* Player.h
 *
 * Representation of a Euchre player
 *
 * by Andrew DeOrio
 * awdeorio@umich.edu
 * 2013-09-06
 */


#include "Card.h"

// Maximum C-string length.  Use this for creating temporary string variables.
const int MAX_STR_LEN = 1024;

// Maximum number of cards in a hand
const int MAX_HAND_SIZE = 5;

// Player has a name and a hand of cards
struct Player {
  char name[MAX_STR_LEN];   // This Player's name
  Card hand[MAX_HAND_SIZE]; // Cards in this Player's hand
  int hand_size;            // Number of cards in hand
};

// When making trump a response includes a decision and the trump suit
struct Make_response {
  bool orderup; //true to order up, false to pass
  Suit trump;   //proposed trump
};

//REQUIRES name is less than MAX_STR_LEN characters
//MODIFIES player_ptr
//EFFECTS  Initializes Player pointed to by player_ptr with name and an empty
//  hand.
void Player_init(Player *player_ptr, const char *name);

//MODIFIES stdout
//EFFECTS: Prints Player to stdout.  This function is for debugging, so any
//  format is OK.
void Player_print(const Player *player_ptr);

//REQUIRES player has less than MAX_HAND_SIZE cards
//MODIFIES player_ptr
//EFFECTS  adds Card c to Player's hand
void Player_add_card(Player *player_ptr, const Card *c);

//REQUIRES round is 1 or 2
//EFFECTS Orders up a trump suit or passes according to the strategy in the
//  project spec.
Make_response Player_make_trump(const Player *player_ptr, const Card *upcard, Player *dealer, int round);

//REQUIRES Player has at least one card
//MODIFIES player_ptr
//EFFECTS  Player adds one card to hand and removes one card from hand.
//  See spec for determining which.
void Player_add_and_discard(Player *player_ptr, const Card *upcard, Suit trump);

//REQUIRES Player has at least one card
//MODIFIES player_ptr
//EFFECTS  Leads one Card from Player's hand according to the strategy in the
//  project spec.  "Lead" means to play the first Card in a trick.
Card Player_lead_card(Player *player_ptr, Suit trump);

//REQUIRES Player has at least one card
//MODIFIES player_ptr
//EFFECTS  Plays one Card from Player's hand according to the strategy in the
//  project spec.
Card Player_play_card(Player *player_ptr, Suit led_suit, Suit trump);


#endif
