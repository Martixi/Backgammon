//
// Created by admin on 29.11.2023.
//
#include "Tokens.h"
#include "../Defines.h"

void CreateTokens(token *tokens){
	int BeginingIndexes[POLES_IN_BEGINING]= {1, 12, 17, 19, 6,8, 13, 24};
	int TokensForEachPole[POLES_IN_BEGINING/2]= {2, 5, 3, 5};
	int count = 0;
	for (int i = 0; i < POLES_IN_BEGINING/2; ++i) {
		for (int j = 0; j < TokensForEachPole[i]; ++j) {
			tokens[count++] = {.id = count, .player = 1, .symbol = (char*)("()"), .index = BeginingIndexes[i]};
			tokens[count++] = {.id = count, .player = 2, .symbol = (char*)(")("), .index = BeginingIndexes[POLES_IN_BEGINING-1-i]};
		}
	}
}