//
// Created by admin on 21.11.2023.
//
#include "../conio2.h"
#include "Board.h"
#include "../Defines.h"
#include "Visuals.h"
#include "../Controls/User_Input.h"
#include "cstdlib"
#include "ctime"
#include "../Other/Other.h"

//Sets basic visual rules
void SetVisuals(){
	settitle("Backgammon");
    textbackground(BLACK);
    clrscr();
    textcolor(BLUE);
	_setcursortype(0);
	Options(-1);
}

void Name(){
	gotoxy(BOARD_X, BOARD_Y-4);
	cputs("BACKGAMMON");
	gotoxy(BOARD_X, BOARD_Y-3);
	cputs("Martyna Ignaczak - s197905");
}

void Board_data(){
	gotoxy(BOARD_X + (BOARD_WIDTH / 2) - 1, BOARD_Y + (BOARD_LENGTH / 2));
	cputs("[BAR]");
	Numbers();
	Name();
	gotoxy(BOARD_X + BOARD_WIDTH + 4, BOARD_Y + (BOARD_LENGTH / 2));
	cputs("HOME");
}


void printWithColor(int before, int color, char *str) {
	textcolor(color);
	cputs(str);
	textcolor(before);
}

//Display main options for player
void Options(int selected){
	gotoxy(BOARD_X, BOARD_Y + BOARD_LENGTH + 4);
	cputs("SELECT:");
	const char *elements[4] = {"R. Roll )", "S. Save )","N. New )", "Q. Quit )"};
	int elementCount = 4;
	for (int i = 0; i < elementCount; ++i) {
		cputs("   ");
		cputs(elements[i]);
	}
}

//Display options connected with dice roll for player
void optionsDice(){
	gotoxy(BOARD_X, BOARD_Y + BOARD_LENGTH + 4);
	cputs("SELECT:");
	const char *elements[3] = {"1. First dice One )", "2. First dice two )", "3. End round )"};
	int elementCount = 3;
	for (int i = 0; i < elementCount; ++i) {
		cputs("   ");
		cputs(elements[i]);
	}
}

void OpeningMenuTitle(){
	gotoxy(BACKGAMMON_X, BACKGAMMON_Y);
	cputs(" ____             _     ___");
	gotoxy(BACKGAMMON_X, BACKGAMMON_Y+1);
	cputs("| __ )  __ _  ___| | __/ __|  __ _ _ __ ___  _ __ ___   ____  _ ___");
	gotoxy(BACKGAMMON_X, BACKGAMMON_Y+2);
	cputs("|  _ \\ / _` |/ __| |/ / / __ / _` | '_ ` _ \\| '_ ` _ \\ /  _ \\| '_  \\");
	gotoxy(BACKGAMMON_X, BACKGAMMON_Y+3);
	cputs("| |_) | (_| | (__|   \\\\ \\_| | (_| | | | | | | | | | | |  (_) | | | |");
	gotoxy(BACKGAMMON_X, BACKGAMMON_Y+4);
	cputs("|____/ \\__,_|\\___|_|\\_\\\\___/ \\__,_|_| |_| |_|_| |_| |_|\\____/|_| |_|");
}
void OpeningMenu(){
	textcolor(BLUE);
	_setcursortype(0);
	OpeningMenuTitle();
	gotoxy(OPTIONS_X-7, OPTIONS_Y-2);
	cputs("+");
	for (int i = 0; i < BOARD_WIDTH/2-2; ++i) {
		cputs("-");}
	cputs("+");
	gotoxy(OPTIONS_X, OPTIONS_Y);
	cputs("PRESS SPACE TO START");
	gotoxy(OPTIONS_X, OPTIONS_Y+3);
	cputs("PRESS R TO READ SAVE");
	gotoxy(OPTIONS_X, OPTIONS_Y+6);
	cputs("PRESS Q TO QUIT GAME");

}

void BasicInstructionsPrint(){
	int positionX = OPTIONS_X-1;
	int Y = OPTIONS_Y;
	clrscr();
	colorChange(BLUE, BLACK);
	gotoxy(positionX, ++Y);
	cputs("Basic Instructions:");
	gotoxy(positionX, ++Y);
	cputs("-Player1 moves from 1 to 24");
	++Y;
	gotoxy(positionX, ++Y);
	cputs("-Player2 moves from 24 to 1");
	++Y;
	gotoxy(positionX, ++Y);
	cputs("-If possible strike exists,");
	gotoxy(positionX, ++Y);
	cputs(" program does it by itself");
	++Y;
	gotoxy(positionX, ++Y);
	cputs("-No valid type of movement");
	gotoxy(positionX, ++Y);
	cputs(" makes player end round");
	getch();
}

bool Begining(token *tokens, player *players, pole *poles, int *leading) {
	OpeningMenu();
	int zn;
	srand(time(nullptr));
	do {
		zn = getch();
		if (zn == ' '){
			BasicInstructionsPrint();
			BasicSetUp(poles, tokens, players);
			TokensSetUp(poles, tokens);
			*leading = rand()%2+1;
		}

		if(zn == 'r'){
			SetVisuals();
			Board_generation();
			IndexGeneration(poles);
			PlayerSetUp(players);
			ReadSave(tokens, players, leading);
			TokensSetUp(poles, tokens);

			zn = ' ';
		}
		if (zn == 'q'){
			return false;
		}
	} while (zn != ' ');
	return true;
}

//Updating board after executing picked option from menu
void currentBoard(token *tokens, player *players, pole *poles, int leading){
	SetVisuals();
	Board_generation();
	IndexGeneration(poles);
	TokensSetUp(poles, tokens);
	Score(players, leading);
	Player_home(tokens);
}

//Updating board after token movement
void  TokenUpdate(token *tokens, player *players, pole *poles, int leading){
	Borders();
	Poles();
	Board_data();
	IndexGeneration(poles);
	TokensSetUp(poles, tokens);
	Score(players, leading);
	Player_home(tokens);
}

//Visual representation of tokens on bar
void TokensOnBar(token *tokens){
	gotoxy(BOARD_X+(BOARD_WIDTH / 2)+1, BOARD_Y +BOARD_LENGTH/4-1);
	textcolor(LIGHTBLUE);
	cputs("P");
	gotoxy(BOARD_X+(BOARD_WIDTH / 2)+1, BOARD_Y +BOARD_LENGTH/4);
	cputs("1");
	gotoxy(BOARD_X+(BOARD_WIDTH / 2)+1, BOARD_Y +BOARD_LENGTH*3/4-1);
	cputs("P");
	gotoxy(BOARD_X+(BOARD_WIDTH / 2)+1, BOARD_Y +BOARD_LENGTH*3/4);
	cputs("2");
	textcolor(BLUE);
	gotoxy(BOARD_X+(BOARD_WIDTH / 2)+1, BOARD_Y +BOARD_LENGTH/4+1);
	cputs(":");
	gotoxy(BOARD_X+(BOARD_WIDTH / 2)+1, BOARD_Y +BOARD_LENGTH*3/4+1);
	cputs(":");
	CountBeatenTokens(tokens);
}

//Inform about the amount of tokens on each players bar
void CountBeatenTokens(token *tokens){
	int playerOne = 0;
	int playerTwo = 0;
	for (int i = 0; i < TOKEN_AMOUNT; ++i) {
		if (tokens[i].player == 1 and tokens[i].index == 0) playerOne++;
		if (tokens[i].player == 2 and tokens[i].index == 0) playerTwo++;
	}
	textcolor(LIGHTBLUE);
	gotoxy(BOARD_X+(BOARD_WIDTH / 2)+1, BOARD_Y +BOARD_LENGTH/4+2);
	cputs(IntToString(playerOne));
	gotoxy(BOARD_X+(BOARD_WIDTH / 2)+1, BOARD_Y +BOARD_LENGTH*3/4+2);
	cputs(IntToString(playerTwo));
	textcolor(BLUE);
}

//Visual representation of player's score
void Score(player *players, int currentPlayer) {
	gotoxy(BOARD_X + BOARD_WIDTH/2, BOARD_Y - 3);
	if (currentPlayer == 1) {
		textcolor(9);
		cputs("() Player One: ");
		cputs(IntToString(players[0].score));
		textcolor(1);
		cputs("   Player Two: ");
		cputs(IntToString(players[1].score));
	} else {
		cputs(" Player One: ");
		cputs(IntToString(players[0].score));
		textcolor(9);
		cputs("    )( Player Two: ");
		cputs(IntToString(players[1].score));
		textcolor(1);
	}
}

//repeat if input is invalid
void wrongInput(){
	gotoxy(BOARD_X, BOARD_Y + BOARD_LENGTH + 5);
	clreol();
	cputs("Token from pole: ");
}

//instruction for moving tokens to home
void MovingToHomeInformation(int movingValue){
	gotoxy(BOARD_X, BOARD_Y + BOARD_LENGTH + 4);
	clreol();
	cputs("Move token to home, dice: ");
	Translate(movingValue);
	gotoxy(BOARD_X, BOARD_Y + BOARD_LENGTH + 5);
	clreol();
	cputs("Token from pole: ");
}

void DisplayInformation(){
	textbackground(LIGHTBLUE);
	textcolor(BLACK);
	gotoxy(BOARD_X, BOARD_Y + BOARD_LENGTH + 5);
	cputs("No move available, press enter for next action");
	textbackground(BLACK);
	textcolor(BLUE);
	enter();
	gotoxy(BOARD_X, BOARD_Y + BOARD_LENGTH + 4);
	clreol();
	gotoxy(BOARD_X, BOARD_Y + BOARD_LENGTH + 5);
	clreol();
}

//different color uses
void colorChange(int text, int background){
	textcolor(text);
	textbackground(background);
}

//Information about players victory displayed to the screen
void VictoryCommunicate(int currentPlayer, int points){
	gotoxy(BOARD_X+10, BOARD_Y + (BOARD_LENGTH / 2));
	colorChange(CYAN, BLACK);
	cputs("Player ");
	Translate(currentPlayer);
	cputs(" has won");
	gotoxy(BOARD_X + (BOARD_WIDTH / 2) + 9, BOARD_Y + (BOARD_LENGTH / 2));
	cputs("He/She gains ");
	Translate(points);
	cputs(" point(s)");
	gotoxy(BOARD_X, BOARD_Y + BOARD_LENGTH + 4);
	clreol();
	gotoxy(BOARD_X+26, BOARD_Y + BOARD_LENGTH + 4);
	cputs("press ENTER to renew");
	gotoxy(BOARD_X, BOARD_Y + BOARD_LENGTH + 5);
	clreol();

}
