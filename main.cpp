#include "GameBoard/Board.h"
#include "GameBoard/Visuals.h"
#include "Mechanics/Tokens.h"
#include "Defines.h"
#include "Controls/User_Input.h"
#include "Mechanics/players.h"
#include "Other/Other.h"
#include "conio2.h"





int main() {
	token tokens[TOKEN_AMOUNT];
	pole poles[INDEXES_AMOUNT];
	player players[PLAYERS];
	int zn = 0, leading = 1;
	if(!Begining(tokens, players, poles, &leading)){
		return 0;
	}
    do {
	    currentBoard(tokens, players, poles, leading);
		zn = inputCheck(zn);
		control(zn, tokens, players, poles, leading);
		if(zn == 'r') leading = RoundControl(leading);
    } while (zn != 'q');
    return 0;
}
