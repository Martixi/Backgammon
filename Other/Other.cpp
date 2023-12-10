//
// Created by admin on 29.11.2023.
//
#include "../conio2.h"
#include "../Mechanics/Tokens.h"
#include "../Defines.h"

//count amount of tokens on pole
int SearchPolesCount(token *pawns, int index){
	int count = 0;
	for (int i = 0; i < TOKEN_AMOUNT; ++i) {
		if(pawns[i].index == index){
			count++;
		}
	}
	return count;
}

//Counting digit length
int Digit_length(int number){
	if (!number) return 1;
	int count =0;
	while(number){
	number/=10;
	++count;
	}
	return count;
}

//Transforming integer to string for cputs()
char *IntToString(int number){
	int length = Digit_length(number);
	char *str = new char[length+1];
	str[length] = '\0';

	for (int i = length-1; i>=0; --i){
		str[i] = (char)('0' + (number % 10));
		number/=10;
	}
	return str;
}

//turning integer to char and printing to the screen
void Translate(int NumberINT){
	putch(NumberINT+48);
}

//Options for main menu available
int inputCheck(int zn){
	while(zn!= 'q'){
		zn = getch();
		if (zn == 'r') break;
		if (zn == 'n') break;
		if (zn == 's') break;
	}
	return zn;
}


//Options for roll available
int RollInput(int input){
	while(true){
		input = getch();
		if(input == '1') break;
		if(input == '2') break;
		if(input == '3') break;
	}
	return input;
}

//Choosing pole
int PlayerPoleInput(){
	int input = '\0';
	int IndexOfPole = 0;
	while (input != '\r'){
		input = getch();
		if ((input >= '0') and (input <= '9')){
			IndexOfPole*=10;
			IndexOfPole+= input - '0';
			textcolor(LIGHTBLUE);
			putch(input);
			textcolor(BLUE);
		}
	}
	return IndexOfPole;
}

//Finding minimal value
int min(int a, int b){
	if(a> b) return b;
	return a;
}

//click enter to continue
void enter(){
	int input = '\0';
	while (input != '\r') {
		input = getch();
	}
}