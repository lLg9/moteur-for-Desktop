#ifndef MOTEUR_RANK_BASE
#define MOTEUR_RANK_BASE

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <fstream>
#include <algorithm>


//--------------------HEADER------------------------------------------

struct ranks{
	std::list<int> good;
	std::list<int> medium;
	std::list<int> poor;
	//methods
	void display() const; 
};


class moteur_rank_base{
public:
	//choose package
	void choose_package();
	//imports
	void import_word_ranks();
	//display ranks 
	void display_word_ranks() const;
	//play
	void load_prt();
	//export
	void export_word_ranks() const;
	//getters&setters
	void set_no_pack(int i) {no_pack = i;}
	int get_no_pack() const {return no_pack;}
	void set_path(std::string s) {path=s;}
	std::string get_path() const {return path;}

protected: 
	ranks word_ranks;
	std::vector<int> prt;
	std::string path;
	int no_pack;

private: 
	//used by load_prt()
	void load_all();
	void load_20();
};


//----------------------CPP--------------------------------------------


//RANKS methods & overloaded operators

void ranks::display() const{
	std::cout << '\n' << "------------------------\n\n"
			  << "good: " << good.size() 	<< "\n"
			  << "medium: " << medium.size()  << "\n"
			  << "poor: "   << poor.size() 	<< "\n\n";
}

std::ostream& operator<<(std::ostream& os, const ranks& r){
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

std::istream& operator>>(std::istream& is, ranks& r){
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

//--------------------------------------------------------------------


//moteur_rank_base methods

void moteur_rank_base::choose_package(){
	int i; 
	do{
		std::cout << "PACKAGE? (1-" << no_pack << ")" << "\n";
		std::cin >> i;
	}while (i<1 || i > no_pack);
	std::cout << std::endl;

	path.append("/").append(std::to_string(i)).append("/");
	std::cout << "path = " << path << "\n";
}

void moteur_rank_base::import_word_ranks(){
	std::string s = path;
	s.append("#ranks.fgnt");
	std::cout << "importing_ranks_from: " << s << "\n";
	std::ifstream ifs{s};
	ifs >> word_ranks;
}

void moteur_rank_base::display_word_ranks() const{
	word_ranks.display();
}


void moteur_rank_base::load_prt(){
	int i;
	std::cout << "0: revise all   ---   1: practice 20";
	do{
		std::cin.clear();
		std::cin >> i;
	}while(i!=0 && i!=1);
	(i == 1)? load_20() : load_all();
}

void moteur_rank_base::export_word_ranks() const{
	std::string s = path;
	std::ofstream ofs{s.append("#ranks.fgnt")};
	ofs << word_ranks;
	std::cout << "RANKS_EXPORTED\n";
}

void moteur_rank_base::load_20(){
	std::list<int>::iterator it = word_ranks.poor.begin();
	int counter = 20;

	while (counter >=9)	{
		if (it == word_ranks.poor.end()) break;
		prt.push_back(*it);
		word_ranks.poor.pop_front();
		it=word_ranks.poor.begin();
		--counter;
	}

	it = word_ranks.medium.begin();
	while (counter >=3) {
		if (it == word_ranks.medium.end()) break;
		prt.push_back(*it);
		word_ranks.medium.pop_front();
		it=word_ranks.medium.begin();
		--counter;
	}

	it = word_ranks.good.begin();
	while (counter >=1)	{
		if (it == word_ranks.good.end()) break;
		prt.push_back(*it);
		word_ranks.good.pop_front();
		it=word_ranks.good.begin();
		--counter;
	}

	random_shuffle(prt.begin(), prt.end());

	std::system("clear");
}

void moteur_rank_base::load_all(){
	for (auto e: word_ranks.good) prt.push_back(e);
	word_ranks.good.clear();
	for (auto e: word_ranks.medium) prt.push_back(e);
	word_ranks.medium.clear();
	for (auto e: word_ranks.poor) prt.push_back(e);
	word_ranks.poor.clear();

	random_shuffle(prt.begin(), prt.end());

	std::system("clear");
}


//--------------------------------------------------------------------------



#endif