#ifndef IMOTEUR
#define IMOTEUR

#include <vector>

#include "WordStruct.h"

class iMoteur{
public: 
	virtual WordStruct getNext() = 0;
	virtual void giveFeedback(bool succ) = 0;
	virtual std::vector<WordStruct> recapMissed() = 0;
};


#endif