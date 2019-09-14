#include <iostream>
#include <string>


#include "Moteur.h"
#include "iMoteur.h"
#include "WordStruct.h"

const int pack_limit = 1;

std::string PATH = "./files/Deutsch/";
int PACKAGENUM;
int NUMTOLOAD;
char MODE;

int remaining = 8; 
WordStruct currWord; 
char answer;

void paramSetup(bool& checker, char* params[]);
void setUp();
void wait();
void play(Moteur& mtr);
void finish(Moteur& mtr);
void recap(Moteur& mtr);


int main(int argc, char* argv[]){
	bool correctParamSetup = false;

	if (argc == 4)
		paramSetup(correctParamSetup, argv);
	if (!correctParamSetup)
		setUp();
	Moteur mtr = Moteur(PATH, NUMTOLOAD);
	wait();
	play(mtr);
	finish(mtr);
	wait();
	recap(mtr);

	return 0;
}

/////////////////////////////////////////////////////////////////////////
/////////////////FUNCTION_IMPLEMENTATIONS////////////////////////////////

void paramSetup(bool& checker, char* params[]){
	try{
		int pack = std::stoi(params[1]);
		if (pack < 1 || pack > pack_limit)
			return;
		PACKAGENUM = pack;

		std::string num = params[2];
		if (num != "60" && num != "20" && num != "pm" )
			return;
		if (num == "pm"){
			NUMTOLOAD = 0;
		}
		else
			NUMTOLOAD = std::stoi(num);

		std::string mod = params[3];
		if (mod.length() != 1 || (mod[0] != 'w' && mod[0] != 't') )
			return;
		MODE = mod[0];

	}catch(std::invalid_argument){
		return;
	}

	PATH += std::to_string(PACKAGENUM) + "/";
	checker = true;
	return;
}

void setUp(){
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
	std::vector<WordStruct> msd = mtr.recapMissed();
	for (WordStruct ws : msd){
		std::cout
		<< "word : " << ws.word << "\n"
		<< "transl : " << ws.transl << "\n"
		<< "example : " << ws.example << "\n"
		<< "----------------------------------------------------------------------------\n\n\n";
	}
}