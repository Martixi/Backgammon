//
// Created by admin on 26.11.2023.
//

#ifndef BACKGAMMON_MECHANICS_H
#define BACKGAMMON_MECHANICS_H
#include "players.h"
#include "Tokens.h"
struct pole;


void Dice(int currentPlayer, pole *poles, token *tokens, player *players);
void WinnerCase(player *players, token *tokens,pole *poles, int currentPlayer);
bool HasPlayerWon(int currentPlayer, token *tokens);
bool IsOtherPlayerNotInHouse(int currentPlayer, token *tokens);
bool IsEnemyTokenOnBar(int currentPlayer, token *tokens);
void Move(int diceOne, int diceTwo, int currentPlayer, pole *poles, token *tokens, player *players);
int pickAmount();
void MovingToken(int currentPlayer, int movingValue, pole *poles, token *tokens);
void optionOne(int diceOne, int diceTwo, int currentPlayer, pole *poles, token *tokens, player *players);
void optionOneContinuation(int diceTwo, int currentPlayer, pole *poles, token *tokens);
bool checkIfCorrect(int currentPlayer, token *tokens, int Input);
bool checkingAllConditions(int currentPlayer, int movingValue, pole *poles, token *tokens, int input);
void Double(int diceOne, int currentPlayer, pole *poles, token *tokens, player *players);
bool strikeCondition(int currentPlayer, int movingValue, token *tokens, int input);
void strikeToken(int currentPlayer, int movingValue, token *tokens, int input);
bool noTokensOnBar(token *tokens, int currentPlayer);
void TakeTokenOffBar(int currentPlayer, int movingValue, pole *poles, token *tokens);
void TakeFromBar(token *tokens, int movingValue, int currentPlayer);
void FreeMovement(int currentPlayer, int movingValue, pole *poles, token *tokens);
bool strikeConditionFromBar(int currentPlayer, int movingValue, token *tokens);
void strikeTokenFromBar(int currentPlayer, int movingValue, token *tokens);
bool IsNextPoleEnemies(int currentPlayer, int movingValue, token *tokens, int currentPole);
int PossibilityToStrike(int currentPlayer, int movingValue, pole *poles, token *tokens);
void ForcedStrike(int currentPlayer, int movingValue, token *tokens, int input);
bool FreeMovementPossible(int currentPlayer, int movingValue, token *tokens);
bool ReadyToTakeOffTokens(int currentPlayer, token *tokens);
int FurthestIndex(int currentPlayer, token *tokens);
bool MovingValueFits(int currentPlayer, int movingValue,token *tokens);
bool TakeFurthest(int currentPlayer, int movingValue,token *tokens, int FurthestIndex);
void MovingTokensToHome(int currentPlayer, int movingValue, pole *poles, token *tokens);

#endif //BACKGAMMON_MECHANICS_H
