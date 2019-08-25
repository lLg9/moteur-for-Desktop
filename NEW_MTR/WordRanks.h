#ifndef WORDRANKS	
#define WORDRANKS

#include <list>
#include <iostream>
#include <sstream>

struct WordRanks {
    std::list<int> good;
    std::list<int> medium;
    std::list<int> poor;
};


std::istream& operator>>(std::istream& is, WordRanks& r){
	std::istringstream isst;
	std::string s;
	int i;
	int counter =0;

	std::getline(is, s);
	isst.str(s);
	while (isst >> i){
		r.good.push_back(i);
		counter++;
	}

	isst.clear();
	std::getline(is, s);
	isst.str(s);
	while (isst >> i){
		r.medium.push_back(i);
		counter ++;
	}

	isst.clear();
	std::getline(is, s);
	isst.str(s);
	while (isst >> i){
		r.poor.push_back(i);
		counter++;
	}
	std::cout << counter << " rank entries imported\n";
	return is;
}


std::ostream& operator<<(std::ostream& os, const WordRanks& r){
	for (std::list<int>::const_iterator it = r.good.begin(); it != r.good.end(); ++it){
		os << *it << " ";
	}
	os << "\n";
	for (std::list<int>::const_iterator it = r.medium.begin(); it != r.medium.end(); ++it){
		os << *it << " ";
	}
	os << "\n";
	for (std::list<int>::const_iterator it = r.poor.begin(); it != r.poor.end(); ++it){
		os << *it << " ";
	}
	os << "\n";

	return os;
}

#endif