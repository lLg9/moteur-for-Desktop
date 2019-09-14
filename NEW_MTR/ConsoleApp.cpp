#include <iostream>
#include <string>


#include "Moteur.h"
#include "iMoteur.h"
#include "WordStruct.h"

const int pack_limit = 1;

std::string PATH;
int PACKAGENUM;
int NUMTOLOAD;
char MODE;

int remaining = 8; 
WordStruct currWord; 
char answer;

void setUp();
void wait();
void play(Moteur& mtr);
void finish(Moteur& mtr);
void recap(Moteur& mtr);

int main(){

	setUp();
	Moteur mtr = Moteur(PATH, NUMTOLOAD);
	wait();
	play(mtr);
	finish(mtr);
	wait();
	recap(mtr);

	return 0;
}

void setUp(){
	PATH = "./files/Deutsch/";
	std::string dummy;

	do{
		std::cout << "package:";
		std::cin >> PACKAGENUM;
	}while(PACKAGENUM < 1 || PACKAGENUM > pack_limit);

	std::string tempLoad;
	do{
		std::cout << "numtoload (60, 20, pm):";
		std::cin >> tempLoad;
	}while(tempLoad != "60" && tempLoad != "20" && tempLoad != "pm");
	if (tempLoad == "pm"){
		NUMTOLOAD = 0;
	}
	else
		NUMTOLOAD = std::stoi(tempLoad);

	do{
		std::cout << "mode (w, t):";
		std::cin >> MODE;
	}while(MODE != 'w' && MODE != 't');

	std::cout << "\n";
	PATH += std::to_string(PACKAGENUM) + "/";
}

void wait(){
	char inp;
	std::cout << "\n" << "(sfyn)>";
	do{
		std::cin >> inp;
	}while(inp != 'y' && inp != 's' && inp != 'n' && inp != 'f');
}

void play(Moteur& mtr){
	while (remaining != 1){
		std::system("clear");
		currWord = mtr.getNext();
		remaining = currWord.remain;
		std::cout << "---------- " << remaining << " words to recall ----------\n\n";

		switch (MODE){
			case 'w':
				std::cout << currWord.word;
				break;
			case 't':
				std::cout << currWord.transl;
				break;
			default:
				std::cout << currWord.word;
				break; 
		}
		std::cout << "\n" << "(sfyn)>";
		do{
			std::cin >> answer;
		}while(answer != 'y' && answer != 's' && answer != 'n' && answer != 'f');

		std::cout << "\n";
		switch (MODE){
			case 'w':
				std::cout << currWord.transl;
				break;
			case 't':
				std::cout << currWord.word;
				break;
			default:
				std::cout << currWord.transl;
				break; 
		}
		std::cout << "\n\n" << currWord.example << "\n\n(y,s/n,f)>";
		do{
			std::cin >> answer;
		}while(answer != 'y' && answer != 's' && answer != 'n' && answer != 'f');

		(answer == 'y' || answer == 's')? mtr.giveFeedback(1) : mtr.giveFeedback(0);
	}
}

void finish(Moteur& mtr){
	std::system("clear");
	currWord = mtr.getNext();
	std::cout << "\n" << currWord.word 
			  << "\n" << currWord.transl
			  << "\n" << currWord.example
			  << "\n\n\n";
}

void recap(Moteur& mtr){
	//to impl;
}