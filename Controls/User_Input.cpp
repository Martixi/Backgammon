//
// Created by admin on 01.12.2023.
//
#include "User_Input.h"
#include "../GameBoard/Visuals.h"
#include "stdio.h"

//Function controlling options chosen in menu
void control(int input, token *tokens, player *players,pole *poles, int currentPlayer) {
	if (input == 'r') {
		Options(1);
		Dice(currentPlayer, poles, tokens, players);
	}
	if (input == 's') {
		Options(2);
		save(tokens, players, currentPlayer);
	}
	if (input == 'q'){
	}
	if (input == 'n'){
		BasicSetUp(poles, tokens, players);
	}

}

//Save option execution
char save(token *tokens, player *players, int activePlayer) {
	FILE *f = fopen("../Save.txt", "w");
	for (int i = 0; i < TOKEN_AMOUNT; i++) {
		fprintf( f, "%d %d %s %d\n" , tokens[i].id, tokens[i].player, tokens[i].symbol,  tokens[i].index);
	}
	fprintf(f, "%d %d %d\n", players[0].score, players[1].score, activePlayer);

	fclose(f);
	return 'q';
}

//reloading saved game
void ReadSave(token *tokens, player *players, int *leading) {
	FILE *f = fopen("../Save.txt", "r");
	int id_save, player_save, index_save, score_one, score_two, currentPlayer;
	char inputSymbol[3];
	for (int j = 0; j < TOKEN_AMOUNT+1; ++j) {
		if (j == TOKEN_AMOUNT) {
			fscanf(f, "%d %d %d", &score_one, &score_two, &currentPlayer);
			players[0].score = score_one;
			players[1].score = score_two;
			*leading = currentPlayer;
		} else {
			fscanf(f, "%d %d %2s %d", &id_save, &player_save, inputSymbol, &index_save);
			ScanTokens(tokens, j, id_save, player_save, inputSymbol, index_save);
		}
	}
	fclose(f);
}

//rewriting tokens info prior to the save
void ScanTokens(token *tokens, int j, int id, int player, const char symbol[3], int index){
	char *memSymbol = new char [3];
	tokens[j] = {.id = id, .player = player, .symbol=memSymbol, .index = index};
	for ( int i = 0; i < 3; i ++) {
		memSymbol[i] = symbol[i];
	}
}