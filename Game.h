#ifndef GAME_H
#define GAME_H
/* Game.h
 *
 * Euchre card game driver
 *
 * by Andrew DeOrio
 * awdeorio@umich.edu
 * 2013-09-06
 */

#include "Pack.h"
#include "Player.h"


////////////////////////////////////////////////////////////////////////////////
const int NUM_PLAYERS = 4;
const int NUM_PARTNERSHIPS = NUM_PLAYERS / 2;

// A game keeps track of a Pack, and whether it should be shuffled, the score
// and how many points it takes to win, and the Players in the game
struct Game {
  Pack pack;                    // Pack of cards
  bool shuffle;                 // Shuffle the pack after each hand
  int score[NUM_PARTNERSHIPS];  // Score for each partnership
  int points_to_win;            // Number of points to win the game
  Player players[NUM_PLAYERS];  // Players in this game, in order around table
};

//REQUIRES pack_filename file contains a well-formed Euchre pack
//MODIFIES game_ptr, stdout
//EFFECTS  Initializes Game pointed to by game_ptr, including initializing 
//  the Pack and each Player.
void Game_init
(
 Game *game_ptr, 
 const char *pack_filename,
 bool shuffle,
 int points_to_win,
 const char *player_names[]
);

//MODIFIES game_ptr, stdout
//EFFECTS  Plays one game of Euchre
void Game_play(Game *game_ptr);


#endif
