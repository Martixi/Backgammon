//
// Created by admin on 29.11.2023.
//

#ifndef BACKGAMMON_PLAYERS_H
#define BACKGAMMON_PLAYERS_H

struct player{
	int id;
	int score;
};

void PlayerSetUp(player *players);
int RoundControl(int currentPlayer);


#endif //BACKGAMMON_PLAYERS_H
