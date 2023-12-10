//
// Created by admin on 21.11.2023.
//
#ifndef BACKGAMMON_VISUALS_H
#define BACKGAMMON_VISUALS_H
#include "../Mechanics/Tokens.h"
#include "Board.h"

bool Begining(token *tokens, player *players, pole *poles, int *leading);
void currentBoard(token *tokens, player *players, pole *poles, int leading);
void SetVisuals();
void Options(int selected);
void Name();
void Board_data();
const char *SearchPoles(token *pawns, int index);
void  TokenUpdate(token *tokens, player *players, pole *poles, int leading);
void TokensOnBar(token *tokens);
void CountBeatenTokens(token *tokens);
void OpeningMenuTitle();
void OpeningMenu();
void heightControlBottom(pole *poles, token *tokens, int i, int count);
void heightControlUpper(pole *poles, token *tokens, int i, int count);
void optionsDice();
void Score(player *players, int currentPlayer);
void wrongInput();
void DisplayInformation();
void colorChange(int text, int background);
void MovingToHomeInformation(int movingValue);
#endif //BACKGAMMON_VISUALS_H
