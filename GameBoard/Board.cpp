//
// Created by admin on 18.11.2023.
//
#include "../conio2.h"
#include "../Defines.h"
#include "Board.h"
#include "Visuals.h"
#include "../Other/Other.h"

//Basic setup for begining game
void BasicSetUp(pole *poles, token *pawns, player *players){
	SetVisuals();
	Board_generation();
	IndexGeneration(poles);
	CreateTokens(pawns);
	PlayerSetUp(players);
}

//Sole generation of borders and poles(with indexes)
void Board_generation(){
	Borders();
	Poles();
	Board_data();
}

//Building borders of board
void Borders() {
	for(int i = BOARD_Y; i <= BOARD_LENGTH + BOARD_Y; i++){
		gotoxy(BOARD_X, i);
		cputs(":");
		gotoxy(BOARD_X + BOARD_WIDTH + 2, i);
		cputs(":");
	}
	for(int i = BOARD_Y+1;i<= BOARD_Y + BOARD_LENGTH - 1; i++){
		gotoxy(BOARD_X+1, i);
		cputs(":");
		gotoxy(BOARD_X + BOARD_WIDTH + 1, i);
		cputs(":");
	}
	for(int i = BOARD_X+1; i <= BOARD_X + BOARD_WIDTH + 1; i++) {
		gotoxy(i, BOARD_Y);
		cputs("=");
		gotoxy(i, BOARD_Y + BOARD_LENGTH);
		cputs("=");
	}
	for (int i = BOARD_Y+1; i <= BOARD_Y + BOARD_LENGTH - 1 ; ++i) {
		gotoxy(BOARD_X+(BOARD_WIDTH / 2), i);
		cputs("|||");
	}
}

//Placing poles on board
void PoleGenerator(int X_location, int Y_location){
	int w = 0;
	for(int i = 0; i < POLES_IN_QUARTER / 2; i++){
		gotoxy(X_location+w, Y_location);
		for(int j = 0; j < POLES_LENGTH; j++){
			gotoxy(X_location+w, Y_location+j);
			cputs("..");
			gotoxy(X_location+w, BOARD_Y + BOARD_LENGTH - POLES_LENGTH + j);
			cputs("..");
		}
		w+=WIDTH_BETWEEN_POLES;
		gotoxy(X_location+w, Y_location);
		for(int j = 0; j < POLES_LENGTH; j++){
			gotoxy(X_location+w, Y_location+j);
			cputs("\\/");
			gotoxy(X_location+w, BOARD_Y + BOARD_LENGTH - POLES_LENGTH + j);
			cputs("/\\");
		}
		w+=WIDTH_BETWEEN_POLES;
	}
}

//creating two rows of poles
void Poles(){
	PoleGenerator(BOARD_X+5, BOARD_Y+1);
	PoleGenerator(BOARD_X + (BOARD_WIDTH / 2) + 6, BOARD_Y + 1);
}

//visual representation of indexes(all of them)
void Numbers(){
	int move = 4;
	int Decimal = 0;
	int First = 1;
	for(int i = 0; i < INDEXES_AMOUNT/2; i++){
		move = MoveBarsNumbersBottom(move);
		First = CountNumbers(Decimal, First);
		if(First==10) {
			First = 0;
			Decimal += 1;
		}
	}
	for(int i = 0; i < INDEXES_AMOUNT/2; i++){
		move = MoveBarsNumbersUpper(move);
		First = CountNumbers(Decimal, First);
		if(First==10) {
			First = 0;
			Decimal += 1;
		}
	}
}

//printing index numbers
int CountNumbers(int Decimal, int First){
	putch(Decimal+'0');
	putch(First+'0');
	return First+1;
}

//Movement required for visual representation of indexes from 1 to 12
int MoveBarsNumbersBottom(int move){
	if(move == 34){
		move+=6;
	}
	gotoxy(BOARD_X + BOARD_WIDTH - move, BOARD_Y + BOARD_LENGTH + 1);
	move+=WIDTH_BETWEEN_POLES;
	return move;
}

//Movement required for visual representation of indexes from 13 to 24
int MoveBarsNumbersUpper(int move){
	move-=WIDTH_BETWEEN_POLES;
	if(move == 35){
		move-=6;
	}
	gotoxy(BOARD_X + BOARD_WIDTH - move, BOARD_Y - 1);
	return move;
}

//General handling index generation in all four sections of board
void IndexGeneration(pole *poles){
	int move = 4;
	for(int i = 0; i < INDEXES_AMOUNT/4; i++){
		poles[i] = {i + 1,1, BOARD_X + BOARD_WIDTH - move};
		move = Index_Move_Bottom(move);
	}
	move+=6;
	for(int i = 6; i < INDEXES_AMOUNT/2; i++){
		poles[i] = { i+1,2, BOARD_X + BOARD_WIDTH - move};
		move = Index_Move_Bottom(move);
	}
	for(int i = 12; i<(INDEXES_AMOUNT*3)/4; i++){
		move = Index_Move_Upper(move);
		poles[i] = {i+1,3, BOARD_X + BOARD_WIDTH - move};
	}
	move-=6;
	for(int i = 18; i<INDEXES_AMOUNT; i++){
		move = Index_Move_Upper(move);
		poles[i] = {i+1,4, BOARD_X + BOARD_WIDTH - move};
	}
	TokensOnPoles(poles);
}

//handling the generation of indexes in section 1 and 2
int Index_Move_Bottom(int move){
	gotoxy(BOARD_X + BOARD_WIDTH - move, BOARD_Y + BOARD_LENGTH + 1);
	move+=WIDTH_BETWEEN_POLES;
	return move;
}

//handling the generation of indexes in section 3 and 4
int Index_Move_Upper(int move){
	move-=WIDTH_BETWEEN_POLES;
	gotoxy(BOARD_X + BOARD_WIDTH - move, BOARD_Y - 1);
	return move;
}


//reset of token count on poles
void TokensOnPoles(pole *poles){
	for (int i = 0; i < INDEXES_AMOUNT; i++) {
		poles[i].TokensOn=0;
	}
}

//Visualisation of tokens in players home's
void Player_home(token *tokens){
	gotoxy(BOARD_X+BOARD_WIDTH+5, BOARD_Y);
	cputs("Home, P1: ");
	int count = 0;
	for (int i = 0; i < TOKEN_AMOUNT; ++i) {
		if (tokens[i].index == 25 and tokens[i].player == 1) count++;
	}
	cputs(IntToString(count));
	gotoxy(BOARD_X+BOARD_WIDTH+5, BOARD_Y+BOARD_LENGTH);
	cputs("Home, P2: ");
	count = 0;
	for (int i = 0; i < TOKEN_AMOUNT; ++i) {
		if (tokens[i].index == 25 and tokens[i].player == 2) count++;
	}
	cputs(IntToString(count));
}

//Placing tokens on specified poles
void TokensSetUp(pole *poles, token *tokens){
	textbackground(LIGHTBLUE);
	textcolor(BLACK);

	for (int i = 0; i < INDEXES_AMOUNT/2; i++) {
		int count = SearchPolesCount(tokens, i+1);
		if(count>0){
			heightControlBottom(poles, tokens, i, count);
		}
		int i2 = i+INDEXES_AMOUNT/2;
		count = SearchPolesCount(tokens, i2+1);
		if(count>0) {
			heightControlUpper(poles, tokens, i2, count);
		}
	}
	textbackground(BLACK);
	textcolor(BLUE);
	TokensOnBar(tokens);
}

//control amount of tokens on specified index from 1 to 12
void TokenSetUpMoveBottom(pole *poles, int index){
	gotoxy(poles[index-1].positionX, BOARD_Y + BOARD_LENGTH - 1 - poles[index - 1].TokensOn);
	++poles[index-1].TokensOn;

}

//control amount of tokens on specified index from 13 to 24
void TokenSetUpMoveUpper(pole *poles, int index){
	gotoxy(poles[index-1].positionX, BOARD_Y+1+poles[index-1].TokensOn);
	++poles[index-1].TokensOn;
}

//controlling height of full poles for indexes 1 to 12
void heightControlBottom(pole *poles, token *tokens, int i, int count){
	for (int j = 0; j < count; j++) {
		if (j<6) {
			TokenSetUpMoveBottom(poles, i + 1);
			cputs(SearchPoles(tokens, i + 1));
		} else if(j == 6){
			gotoxy(poles[i].positionX, BOARD_Y + BOARD_LENGTH - POLES_LENGTH - 2);
			poles[i].TokensOn = count;
			textbackground(BLACK);
			textcolor(LIGHTBLUE);
			cputs("+");
			Translate(poles[i].TokensOn - POLES_LENGTH);
			textcolor(BLACK);
			textbackground(LIGHTBLUE);
			break;
		}
	}
}

//controlling height of full poles for indexes 13 to 24
void heightControlUpper(pole *poles, token *tokens, int i, int count){
	for (int j = 0; j < count; j++) {
		if (j<6) {
			TokenSetUpMoveUpper(poles, i + 1);
			cputs(SearchPoles(tokens, i + 1));
		} else if(j == 6){
			gotoxy(poles[i].positionX, BOARD_Y + POLES_LENGTH + 2);
			poles[i].TokensOn = count;
			textbackground(BLACK);
			textcolor(LIGHTBLUE);
			cputs("+");
			Translate(poles[i].TokensOn - POLES_LENGTH);
			textcolor(BLACK);
			textbackground(LIGHTBLUE);
			break;
		}
	}
}

//Give the type of pawn that belongs to the pole
const char *SearchPoles(token *pawns, int index){
	for (int i = 0; i < TOKEN_AMOUNT; ++i) {
		if(pawns[i].index == index){
			return pawns[i].symbol;
		}
	}
	return "";
}

