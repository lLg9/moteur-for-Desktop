#include <iostream>

#include "../Parser.h"
#include "../WordRanks.h"
#include "../WordData.h"
#include "../Moteur.h"
#include "../WordStruct.h"

#include <vector>
#include <string>

void testParser();
void testMoteur();

const std::string PATH = "../files/Deutsch/1/";

int main(){

	// testing the parser

	// testParser();

	// testint Moteur

	testMoteur();


	return 0;
}



void testMoteur(){

	Moteur moteur = Moteur(PATH, 1, 20);

	WordStruct ws;
	for (int i=0; i<21; ++i){
		ws = moteur.getNext();
		std::cout << ws;
		moteur.giveFeedback(1);

	}

}



void testParser(){


	Parser p = Parser(PATH);

	//import - export ranks
	WordRanks ranks = p.parseRanks();

	for (auto e : ranks.good)
		std::cout << e << " ";
	std::cout << "\n";

	for (auto e : ranks.medium)
		std::cout << e << " ";
	std::cout << "\n";

	for (auto e : ranks.poor)
		std::cout << e << " ";
	std::cout << "\n";

	p.exportRanks(ranks);

	//import-export data
	std::vector<WordData> data = p.parseData();

	for (auto e : data){
		std::cout << e << std::endl;
	}

	p.exportData(data);

}
