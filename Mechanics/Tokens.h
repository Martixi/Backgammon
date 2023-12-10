//
// Created by admin on 29.11.2023.
//

#ifndef BACKGAMMON_TOKENS_H
#define BACKGAMMON_TOKENS_H

struct token{
	int id;
	int player;
	char *symbol;
	int index;

};

void CreateTokens(token *Tokens);



#endif //BACKGAMMON_TOKENS_H
