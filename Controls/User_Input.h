//
// Created by admin on 01.12.2023.
//

#ifndef BACKGAMMON_USER_INPUT_H
#define BACKGAMMON_USER_INPUT_H
#include "../Defines.h"
#include "../Mechanics/Tokens.h"
#include "../Mechanics/players.h"
#include "../GameBoard/Board.h"

void control(int input, token *tokens, player *players,pole *poles, int currentPlayer);
char save(token *tokens, player *players, int activePlayer);
void ReadSave(token *tokens, player *players, int *leading);
void ScanTokens(token *tokens, int j, int id, int player, char symbol[3], int index);


#endif //BACKGAMMON_USER_INPUT_H
