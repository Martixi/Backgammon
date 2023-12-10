#include "GameBoard/Board.h"
#include "GameBoard/Visuals.h"
#include "Mechanics/Tokens.h"
#include "Defines.h"
#include "Controls/User_Input.h"
#include "Mechanics/players.h"
#include "Other/Other.h"


int main() {
	token tokens[TOKEN_AMOUNT];
	pole poles[INDEXES_AMOUNT];
	player players[PLAYERS];
	int zn = 0, leading = 1;
	//starting with the main menu
	if(!Begining(tokens, players, poles, &leading)){
		//quit
		return 0;
	}
	//working game until player decides to quit
    do {
	    currentBoard(tokens, players, poles, leading);
		zn = inputCheck(zn);
		//picking options
		control(zn, tokens, players, poles, leading);
		//switching players
	    WinnerCase(players, tokens, poles, leading);
		if(zn == 'r') leading = RoundControl(leading);

    } while (zn != 'q');
    return 0;
}