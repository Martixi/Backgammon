//
// Created by admin on 26.11.2023.
//
#include "../conio2.h"
#include "../Defines.h"
#include "cstdlib"
#include "ctime"
#include "../Other/Other.h"
#include "players.h"
#include "Tokens.h"
#include "../GameBoard/Board.h"
#include "../GameBoard/Visuals.h"
using namespace std;

//Roll the dice
void Dice(int currentPlayer, pole *poles, token *tokens, player *players) {
	srand(time(nullptr));
	gotoxy(BOARD_X + BOARD_WIDTH + 4, BOARD_Y + (BOARD_LENGTH / 4) - 2);
	cputs("| ");
	int value_1 = rand()%6+1;
	textcolor(9);
	Translate(value_1);
	textcolor(1);
	cputs(" | Dice One");
	gotoxy(BOARD_X + BOARD_WIDTH + 4, BOARD_Y + (BOARD_LENGTH / 4) + 2);
	cputs("| ");
	int value_2 = rand()%6+1;
	textcolor(9);
	Translate(value_2);
	textcolor(1);
	cputs(" | Dice Two");
	Move(value_1, value_2, currentPlayer, poles, tokens, players);
}

//Winning mechanism
void WinnerCase(player *players, token *tokens,pole *poles, int currentPlayer){
	if (HasPlayerWon(currentPlayer, tokens)){
		int points = 1;
		if (IsOtherPlayerNotInHouse(currentPlayer, tokens)) ++points;
		if (IsEnemyTokenOnBar(currentPlayer, tokens)) ++points;
		VictoryCommunicate(currentPlayer, points);
		enter();
		players[currentPlayer-1].score += points;
		NewGame(poles, tokens);
	}
}

bool HasPlayerWon(int currentPlayer, token *tokens){
	for (int i = 0; i < TOKEN_AMOUNT; ++i) {
		if (tokens[i].player == currentPlayer and tokens[i].index != HOME_INDEX){
			return false;
		}
	}
	return true;
}

bool IsOtherPlayerNotInHouse(int currentPlayer, token *tokens){
	int otherPlayer = currentPlayer%2+1;
	for (int i = 0; i < TOKEN_AMOUNT; ++i) {
		if (tokens[i].player==otherPlayer and tokens[i].index == HOME_INDEX){
			return false;
		}
	}
	return true;
}

bool IsEnemyTokenOnBar(int currentPlayer, token *tokens){
	int otherPlayer = currentPlayer%2+1;
	for (int i = 0; i < TOKEN_AMOUNT; ++i) {
		if (tokens[i].player == otherPlayer and tokens[i].index == 0){
			return true;
		}
	}
	return false;
}

//Choosing options of movement
void Move(int diceOne, int diceTwo, int currentPlayer, pole *poles, token *tokens, player *players) {
	if (diceTwo != diceOne) {
		int OptionPicked;
		optionsDice();
		OptionPicked = pickAmount();
		if (OptionPicked == '1') optionOne(diceOne, diceTwo, currentPlayer, poles, tokens, players);
		else if (OptionPicked == '2')optionOne(diceTwo, diceOne, currentPlayer, poles, tokens, players);
	} else Double(diceOne, currentPlayer, poles, tokens, players);
}

//Options one and two processing
void optionOne(int diceOne, int diceTwo, int currentPlayer, pole *poles, token *tokens, player *players) {
	gotoxy(BOARD_X, BOARD_Y + BOARD_LENGTH + 4);
	delline();
	cputs("Move token ");
	textcolor(LIGHTBLUE);
	cputs(IntToString(diceOne));
	textcolor(BLUE);
	cputs(" time(s).");
	gotoxy(BOARD_X, BOARD_Y + BOARD_LENGTH + 5);
	clreol();
	cputs("Token from pole: ");
	MovingToken(currentPlayer, diceOne, poles, tokens);
	TokenUpdate(tokens, players, poles, currentPlayer);
	optionOneContinuation(diceTwo, currentPlayer, poles, tokens);
}

void optionOneContinuation(int diceTwo, int currentPlayer, pole *poles, token *tokens){
	gotoxy(BOARD_X, BOARD_Y + BOARD_LENGTH + 4);
	delline();
	cputs("Move token ");
	textcolor(LIGHTBLUE);
	cputs(IntToString(diceTwo));
	textcolor(BLUE);
	cputs(" time(s).");
	gotoxy(BOARD_X, BOARD_Y + BOARD_LENGTH + 5);
	clreol();
	cputs("Token from pole: ");
	MovingToken(currentPlayer, diceTwo, poles, tokens);
	gotoxy(BOARD_X, BOARD_Y + BOARD_LENGTH + 5);
	clreol();
}

//Double handling
void Double(int diceOne, int currentPlayer, pole *poles, token *tokens, player *players){
	for (int i = 0; i < 4; ++i) {
		gotoxy(BOARD_X, BOARD_Y + BOARD_LENGTH + 4);
		delline();
		cputs("Double, you get four moves: Move token ");
		textcolor(LIGHTBLUE);
		cputs(IntToString(diceOne));
		textcolor(BLUE);
		cputs(" time(s).");
		gotoxy(BOARD_X, BOARD_Y + BOARD_LENGTH + 5);
		clreol();
		cputs("Token from pole: ");
		MovingToken(currentPlayer, diceOne, poles, tokens);
		TokenUpdate(tokens, players, poles, currentPlayer);
	}
}

//Movement requirements handling
void MovingToken(int currentPlayer, int movingValue, pole *poles, token *tokens) {
	int ForcedPole = PossibilityToStrike(currentPlayer, movingValue, poles, tokens);
	if (!(noTokensOnBar(tokens, currentPlayer))){
		TakeTokenOffBar(currentPlayer, movingValue, poles, tokens);
		return;
	}
	if (ReadyToTakeOffTokens(currentPlayer, tokens)){
		MovingTokensToHome(currentPlayer, movingValue, poles, tokens);
		return;
	}
	if (ForcedPole!= 0){
		ForcedStrike(currentPlayer, movingValue, tokens, ForcedPole);
		return;
	}
	if (FreeMovementPossible(currentPlayer, movingValue, tokens)){
		FreeMovement(currentPlayer, movingValue, poles, tokens);
		return;
	}
}

//required token strike
void ForcedStrike(int currentPlayer, int movingValue, token *tokens, int input) {
	if (currentPlayer == 1){
		strikeToken(currentPlayer, movingValue, tokens, input);
		for (int i = 0; i < TOKEN_AMOUNT; ++i) {
			if (tokens[i].index == input) {
				tokens[i].index = input+movingValue;
				break;
			}
		}
	}
	if (currentPlayer == 2){
		strikeToken(currentPlayer, movingValue, tokens, input);
		for (int i = 0; i < TOKEN_AMOUNT; ++i) {
			if (tokens[i].index == input) {
				tokens[i].index = input-movingValue;
				break;
			}
		}
	}
}

//Movement free of any requirements
void FreeMovement(int currentPlayer, int movingValue, pole *poles, token *tokens){
	int PoleChosen = -1, newIndex;
	while (true) {
		PoleChosen = PlayerPoleInput();
		if (checkingAllConditions(currentPlayer, movingValue, poles, tokens, PoleChosen)) break;
		wrongInput();
	}
	if (currentPlayer == 1) newIndex = PoleChosen + movingValue;
	else newIndex = PoleChosen - movingValue;
	strikeToken(currentPlayer, movingValue, tokens, PoleChosen);
	for (int i = 0; i < TOKEN_AMOUNT; ++i) {
		if (tokens[i].index == PoleChosen) {
			tokens[i].index = newIndex;
			break;
		}
	}
}

//Looking for errors in pole selection
bool checkingAllConditions(int currentPlayer, int movingValue, pole *poles, token *tokens, int input){
	int newIndex;
	int OtherPlayer = (currentPlayer)%2 + 1;
	if(currentPlayer == 1) newIndex = input + movingValue;
	else newIndex = input - movingValue;
	if(input > INDEXES_AMOUNT) return false;
	if(input <= 0) return false;
	if(poles[input-1].TokensOn == 0) return false;
	if(!checkIfCorrect(currentPlayer, tokens, input)) return false;
	if(newIndex > 24 or newIndex <= 0) return false;
	if(checkIfCorrect(OtherPlayer, tokens, newIndex)){
		return strikeCondition(currentPlayer, movingValue, tokens, input);
	}
	return true;
}

//token striking function -
void strikeToken(int currentPlayer, int movingValue, token *tokens, int input) {
	if (strikeCondition(currentPlayer, movingValue, tokens, input)){
		int newIndex;
		if(currentPlayer == 1) newIndex = input + movingValue;
		else newIndex = input - movingValue;
		for (int i = 0; i < TOKEN_AMOUNT; ++i) {
			if (tokens[i].index == newIndex){
				tokens[i].index = 0;
			}
		}
	}
}

//Conditions for striking tokens
bool strikeCondition(int currentPlayer, int movingValue, token *tokens, int input) {
	int OtherPlayer = (currentPlayer)%2 + 1, newIndex;
	if(currentPlayer == 1) newIndex = input + movingValue;
	else newIndex = input - movingValue;
	if (SearchPolesCount(tokens, newIndex) == 1 and checkIfCorrect(OtherPlayer, tokens, newIndex)){
		return true;
	}
	return false;
}

//Prioritizing taking token off of bar - Handling
void TakeTokenOffBar(int currentPlayer, int movingValue, pole *poles, token *tokens){
	if(currentPlayer == 2) movingValue = INDEXES_AMOUNT-movingValue;
	if(poles[movingValue-1].TokensOn == 0) {
		TakeFromBar(tokens, movingValue, currentPlayer);
	}
	else{
		for (int i = 0; i < TOKEN_AMOUNT; ++i) {
			if (tokens[i].index == movingValue and tokens[i].player == currentPlayer){
				TakeFromBar(tokens, movingValue, currentPlayer);
				return;
			}else if (tokens[i].index == movingValue and tokens[i].player != currentPlayer){
				strikeTokenFromBar(currentPlayer, movingValue, tokens);
				poles[movingValue-1].TokensOn--;
				if (poles[movingValue-1].TokensOn == 0) {
					TakeFromBar(tokens, movingValue, currentPlayer);
				}else{
					DisplayInformation();
				}
				return;
			}
		}
	}
}

//Moving token off of the bar
void TakeFromBar(token *tokens, int movingValue, int currentPlayer) {
	if(currentPlayer == 1){
		for (int i = 0; i < TOKEN_AMOUNT; ++i) {
			if (tokens[i].index == 0 and tokens[i].player == currentPlayer) {
				tokens[i].index = movingValue;
				break;
			}
		}
	}else{
		for (int i = TOKEN_AMOUNT-1; i >= 0; --i) {
			if (tokens[i].index == 0 and tokens[i].player == currentPlayer) {
				tokens[i].index = movingValue;
				break;
			}
		}
	}
}

//Striking token with players token freshly taken off of bar
void strikeTokenFromBar(int currentPlayer, int movingValue, token *tokens) {
	if (strikeConditionFromBar(currentPlayer, movingValue, tokens)){
		for (int i = 0; i < TOKEN_AMOUNT; ++i) {
			if (tokens[i].index == movingValue){
				tokens[i].index = 0;
				return;
			}
		}
	}
}

//Checking if it is possible to strike an enemy token with players token from Bar
bool strikeConditionFromBar(int currentPlayer, int movingValue, token *tokens) {
	int OtherPlayer = (currentPlayer)%2 + 1;
	if (SearchPolesCount(tokens, movingValue) == 1 and checkIfCorrect(OtherPlayer, tokens, movingValue)){
		return true;
	}
	return false;
}

//Checking if the value holds - multiple use
bool checkIfCorrect(int currentPlayer, token *tokens, int Input) {
	for (int i = 0; i < TOKEN_AMOUNT; ++i) {
		if(tokens[i].index == Input){
			if(tokens[i].player == currentPlayer) return true;
			break;
		}
	}
	return false;
}

//Checking if there are any tokens on chosen pole
bool noTokensOnBar(token *tokens, int currentPlayer) {
	int count = 0;
	for (int i = 0; i < TOKEN_AMOUNT; ++i) {
		if(tokens[i].index == 0 and tokens[i].player == currentPlayer) count++;
	}
	if(count == 0)return true;
	else return false;
}

//passing the value chosen from menu (picking dices)
int pickAmount(){
	int input = 0;
	int choice = RollInput(input);
	return choice;
}

//Looking for a possibility to strike enemies token
int PossibilityToStrike(int currentPlayer, int movingValue, pole *poles, token *tokens){
	if (currentPlayer == 1){
		for (int i = 0; i < INDEXES_AMOUNT; ++i) {
			if (checkIfCorrect(currentPlayer, tokens, i+1) and IsNextPoleEnemies(currentPlayer, movingValue, tokens,
			                                                                     i + 1)){
				if (poles[i+movingValue].TokensOn == 1) return i+1;
			}
		}
	} else{
		for (int i = INDEXES_AMOUNT; i >0; --i) {
			if (checkIfCorrect(currentPlayer, tokens, i) and IsNextPoleEnemies(currentPlayer, movingValue, tokens, i)){
				if (poles[i-movingValue-1].TokensOn == 1) return i;
			}
		}
	}
	return 0;
}

//Making sure next available pole belongs to enemy
bool IsNextPoleEnemies(int currentPlayer, int movingValue, token *tokens, int currentPole) {
	int OtherPlayer = currentPlayer%2 +1;
	if (currentPlayer == 1) {
		if (checkIfCorrect(OtherPlayer, tokens, currentPole + movingValue)) {
			return true;
		}
	}
	else{
		if (checkIfCorrect(OtherPlayer, tokens, currentPole-movingValue)){
			return true;
		}
	}
	return false;
}

//skipping if no movement available
bool FreeMovementPossible(int currentPlayer, int movingValue, token *tokens) {
	if (currentPlayer == 1){
		for (int i = 0; i < INDEXES_AMOUNT; ++i) {
			if (checkIfCorrect(currentPlayer, tokens, i+1) and !(IsNextPoleEnemies(currentPlayer, movingValue, tokens,
			                                                                       i + 1))){
				if (i+1+movingValue > INDEXES_AMOUNT) return false;
				return true;
			}
		}
	} else{
		for (int i = INDEXES_AMOUNT; i >0; --i) {
			if (checkIfCorrect(currentPlayer, tokens, i) and !(IsNextPoleEnemies(currentPlayer, movingValue, tokens, i))){
				if (i - movingValue <= 0)return false;
				return true;
			}
		}
	}
	return false;
}

//Taking tokens off of board
void MovingTokensToHome(int currentPlayer, int movingValue, pole *poles, token *tokens){
	int Furthest = FurthestIndex(currentPlayer, tokens);
	if (MovingValueFits(currentPlayer, movingValue,tokens))return;
	if (TakeFurthest(currentPlayer, movingValue, tokens, Furthest))return;
	int ForcedPole = PossibilityToStrike(currentPlayer, movingValue, poles, tokens);
	if (ForcedPole!= 0) return ForcedStrike(currentPlayer, movingValue, tokens, ForcedPole);
	if (FreeMovementPossible(currentPlayer, movingValue, tokens)) return FreeMovement(currentPlayer, movingValue, poles, tokens);
}

//checks if moving value fits one of the tokens and moves it if it's true
bool MovingValueFits(int currentPlayer, int movingValue,token *tokens) {
	if (currentPlayer == 1) {
		for (int i = 0; i < TOKEN_AMOUNT; ++i) {
			if (tokens[i].player == currentPlayer and tokens[i].index + movingValue == HOME_INDEX) {
				tokens[i].index = HOME_INDEX;
				return true;
			}
		}
	} else if (currentPlayer == 2){
		for (int i = TOKEN_AMOUNT - 1; i >= 0; --i) {
			if (tokens[i].player == currentPlayer and tokens[i].index - movingValue == 0) {
				tokens[i].index = HOME_INDEX;
				return true;
			}
		}
	}
	return false;
}

//checks if player has to move the furthest token, and does it if it's true
bool TakeFurthest(int currentPlayer, int movingValue,token *tokens, int FurthestIndex){
	if (currentPlayer == 1){
		if (HOME_INDEX-FurthestIndex < movingValue){
			for (int i = 0; i < TOKEN_AMOUNT; ++i) {
				if (tokens[i].player == currentPlayer and tokens[i].index == FurthestIndex){
					tokens[i].index = HOME_INDEX;
					return true;
				}
			}
		}
	} else{
		if (FurthestIndex < movingValue){
			for (int i = TOKEN_AMOUNT - 1; i >= 0; --i) {
				if (tokens[i].player == currentPlayer and tokens[i].index == FurthestIndex) {
					tokens[i].index = HOME_INDEX;
					return true;
				}
			}
		}
	}
	return false;
}

//is player ready to take tokens off of board
bool ReadyToTakeOffTokens(int currentPlayer, token *tokens){
	if (currentPlayer == 1) {
		for (int i = 0; i < TOKEN_AMOUNT; ++i) {
			if (tokens[i].player == currentPlayer and tokens[i].index < 19) return false;
		}
	}else if (currentPlayer == 2){
		for (int i = 0; i < TOKEN_AMOUNT; ++i) {
			if (tokens[i].player == currentPlayer and tokens[i].index > 6){
				if (tokens[i].index != HOME_INDEX)return false;
			}
			if (tokens[i].player == currentPlayer and tokens[i].index == 0) return false;
		}
	}
	return true;
}

//Looking for index with tokens furthest from home
int FurthestIndex(int currentPlayer, token *tokens){
	if (currentPlayer == 1){
		for (int i = 0; i < INDEXES_AMOUNT; ++i) {
			for (int j = 0; j < TOKEN_AMOUNT; ++j) {
				if (tokens[j].index == i+1 and tokens[j].player == currentPlayer) return i+1;
			}
		}
	}
	else{
		for (int i = INDEXES_AMOUNT-1; i >= 0; --i) {
			for (int j = 0; j < TOKEN_AMOUNT; ++j) {
				if (tokens[j].index == i+1 and tokens[j].player == currentPlayer) return i+1;
			}
		}
	}
	return 0;
}