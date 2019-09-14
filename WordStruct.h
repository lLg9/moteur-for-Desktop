#ifndef WORDSTRUCT
#define WORDSTRUCT

#include <string>
#include <iostream>

struct WordStruct {

    int remain;
    std::string word;
 	std::string transl;
  	std::string example;

};


std::ostream& operator<<(std::ostream& os, const WordStruct& ws){

	std::cout 
	<< "remaining : " << ws.remain << "\n"
	<< "word : " << ws.word << "\n"
	<< "transl : " << ws.transl << "\n"
	<< "example : " << ws.example << "\n"
	<< "----------------------------------------------------------------------------\n";

	return os;
}

#endif
