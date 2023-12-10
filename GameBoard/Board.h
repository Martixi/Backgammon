//
// Created by admin on 18.11.2023.
//

#ifndef BACKGAMMON_BOARD_H
#define BACKGAMMON_BOARD_H
#include "../Mechanics/Mechanics.h"
#include "../Mechanics/Tokens.h"

struct pole{
	int index;
	int section;
	int positionX;
	int TokensOn;
};

void Board_generation();
void Borders();
void Poles();
void PoleGenerator(int X_location, int Y_location);
void Numbers();
int CountNumbers(int Decimals, int First);
int MoveBarsNumbersBottom(int move);
int MoveBarsNumbersUpper(int move);
void IndexGeneration(pole *poles);
int Index_Move_Upper(int move);
int Index_Move_Bottom(int move);
void TokensOnPoles(pole *poles);
void BasicSetUp(pole *poles, token *pawns, player *players);
void Player_home(token *tokens);
void BasicInstructionsPrint();
void TokensSetUp(pole *poles, token *tokens);
void TokenSetUpMoveBottom(pole *poles, int index);
void TokenSetUpMoveUpper(pole *poles, int index);


#endif //BACKGAMMON_BOARD_H

/*
 *   13   14   15   16   17   18         19   20   21   22   23   24
:=======================================================================:
::   ][   \/   ..   \/   []   \/   |||   []   \/   ..   \/   ..   ][   ::
::   ][   \/   ..   \/   []   \/   |||   []   \/   ..   \/   ..   ][   ::
::   ][   \/   ..   \/   []   \/   |||   []   \/   ..   \/   ..   \/   ::
::   ][   \/   ..   \/   ..   \/   |||   []   \/   ..   \/   ..   \/   ::
::   ][   \/   ..   \/   ..   \/   |||   []   \/   ..   \/   ..   \/   :: +===+ R
::   ..   \/   ..   \/   ..   \/   |||   ..   \/   ..   \/   ..   \/   :: | X | 2
::                                 |||                                 :: +===+ R
::                                [BAR]                                :: +===+ O
::                                 |||                                 :: | X | L
::   ..   /\   ..   /\   ..   /\   |||   ..   /\   ..   /\   ..   /\   :: +===+ L
::   []   /\   ..   /\   ..   /\   |||   ][   /\   ..   /\   ..   /\   ::
::   []   /\   ..   /\   ..   /\   |||   ][   /\   ..   /\   ..   /\   ::
::   []   /\   ..   /\   ][   /\   |||   ][   /\   ..   /\   ..   /\   ::
::   []   /\   ..   /\   ][   /\   |||   ][   /\   ..   /\   ..   []   ::
::   []   /\   ..   /\   ][   /\   |||   ][   /\   ..   /\   ..   []   ::
:=======================================================================:
	 12   11   10    9    8    7          6    5    4    3    2    1
 *
 */