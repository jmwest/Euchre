//
//  euchre.cpp
//  proj3
//
//  Created by John West on 10/7/13.
//  Copyright (c) 2013 John West. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <cstring>

#include "Game.h"

using namespace std;

// EFFECTS: prints out the failure message and then exits the program using EXIT_FAILURE
static void Euchre_print_failure();

int main(int argc, char *argv[])
{
	if (argc == 8)
	{
		if (strcmp("./euchre", argv[0]))
		{
			Euchre_print_failure();
		}

		if (strcmp("shuffle", argv[2]) and strcmp("noshuffle", argv[2]))
		{
			Euchre_print_failure();
		}
		
		if ((atoi(argv[3]) < 1) or (atoi(argv[3]) > 100))
		{
			Euchre_print_failure();
		}
	}
	else
	{
		Euchre_print_failure();
	}


	const char *players[] = {argv[4], argv[5], argv[6], argv[7]};
	Game the_game;
	bool shuffle = false;
	int points_to_win = 0;

	for (int i = 0; i < argc; i++)
	{
		cout << argv[i] << " ";
	}

	if (!strcmp(argv[2], "shuffle"))
	{
		shuffle = true;
	}
	else
	{
		shuffle = false;
	}

	points_to_win = atoi(argv[3]);

	Game_init(&the_game, argv[1], shuffle, points_to_win, players);

	Game_play(&the_game);

	return EXIT_SUCCESS;
}

static void Euchre_print_failure()
{
	cout << "Usage: euchre PACK_FILENAME [shuffle|noshuffle] POINTS_TO_WIN NAME1 NAME2 NAME3 NAME4" << endl;

	exit(EXIT_FAILURE);
}