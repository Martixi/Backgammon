//
// Created by admin on 29.11.2023.
//
// lol
#include "../Defines.h"
#include "players.h"

void PlayerSetUp(player *players){
	for (int i = 0; i < PLAYERS; i++) {
		players[i] = {i+1, 0};
	}
}

int RoundControl(int currentPlayer){
	if(currentPlayer == 1) return 2;
	else return 1;
}