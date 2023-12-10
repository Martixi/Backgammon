//
// Created by admin on 29.11.2023.
//

#ifndef BACKGAMMON_OTHER_H
#define BACKGAMMON_OTHER_H
#include "../Mechanics/Tokens.h"

int SearchPolesCount(token *pawns, int index);
char *IntToString(int number);
int Digit_length(int number);
void Translate(int NumberINT);
int inputCheck(int zn);
int RollInput(int input);
int PlayerPoleInput();
int min(int a, int b);
void enter();


#endif //BACKGAMMON_OTHER_H
