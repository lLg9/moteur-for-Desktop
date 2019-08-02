#ifndef MOTEUR_ENGLISH
#define MOTEUR_ENGLISH

#include "moteur_rank_base.h"
#include "moteur_content_base.h"
#include <vector>
#include <fstream>

struct english_data{
	english_data() : key(), week(), hits(), word(), transl(), context() {}
	english_data(int k, int wk, std::vector<int> hits, std::string wd, std::string t, std::string c) 
	: key(k), week(wk), hits(hits), word(wd), transl(t), context(c) {}
	int key, week;
	std::vector<int> hits;
	std::string word, transl, context;

	void modrank(int i);
	int sumrank() const;
	bool last_q() const;
	bool last3_q() const; 
	bool last5_q() const;
};

class moteur_english : public moteur_rank_base, moteur_content_base{
public: 
	void import_data();
	void q_n_a();
	void export_data();

private: 
	std::vector<english_data> data;
	void print_tilde_string(std::string) const; 
};

//---------------------CPP------------------------------------

//vector >> and << operators
std::ostream& operator<< (std::ostream& os, std::vector<int>& v){
	if (v.size()==0) return os;
	os << "[";
	std::vector<int>::iterator it = v.begin();
	for (std::vector<int>::iterator& i = it; i < v.end()-1; ++i) 
		os << *it << ", ";
	os << *it  << "]";
	return os;
}

std::istream& operator>> (std::istream& is, std::vector<int>& v){
	int ti;
	char tc;
	while (is >> tc && tc!= ']'){
		is >> ti;
		v.push_back(ti);
	}
	return is; 
}


//english_data methods & operators

std::istream& operator>>(std::istream& is, english_data& ed){
	char curr;
	int key, week; 
	std::vector<int> hits;
	std::string word, transl, context;

	is >> key >> curr >> week >> curr >> hits >> curr;
	while (is.get(curr) && curr != ';') word+=curr;
	while (is.get(curr) && curr != ';') transl+=curr;
	while (is.get(curr) && curr != '\n') context+=curr;

	ed = english_data(key, week, hits, word, transl, context);

	return is;
}

std::ostream& operator<< (std::ostream& os, english_data& dt){
	os << dt.key << " ; " << dt.week << " ; " << dt.hits  << " ;"  << dt.word << ";" << dt.transl << ";" << dt.context << "\n"; 
	return os;
}


void english_data::modrank(int i){
	for (int i=0; i<9; ++i)
		std::swap(hits[i], hits[i+1]);
	hits[9]=i;
}

int english_data::sumrank() const{
	int res=0; 
	for (int i=0; i<10;++i)
		res+=hits[i];
	return res; 
}

bool english_data::last_q() const{
	return hits[9];
}

bool english_data::last3_q() const{
	for (int i=7; i<10; ++i){
		if (hits[i]==0) return false; 
	}
	return true;
}

bool english_data::last5_q() const{
	for (int i=5; i<10; ++i){
		if (hits[i]==0) return false; 
	}
	return true;
}
//------------------------------------------------------------------

//moteur_english methods

void moteur_english::import_data(){
	std::string s = get_path();
	s.append("#data.fgnt");
	std::cout << "importing_words_from: " << s << "\n";
	std::ifstream inf{s};
	english_data ed;
	int counter = 0; 
	while (inf >> ed){
		data.push_back(ed);
		counter ++;
	}
	std::cout << counter << " data entries imported\n";
}

void moteur_english::q_n_a(){
	char ans, mode;
	int curr_rank;
	int counter = prt.size();
	std::cout << "(_w_ord->translation? _t_ranslation->word? _r_andom?)>";
	do{
		std::cin >> mode;
	}while(mode != 'w' && mode != 't' && mode != 'r');

	for (auto i : prt){
		std::cout << "---------- " << counter << " words to recall ----------\n\n";

		std::cout << "\n---";

		(mode == 'w')? print_tilde_string(data[i].word) : (mode == 't')? print_tilde_string(data[i].transl) : (counter%6 < 3)? print_tilde_string(data[i].word) : print_tilde_string(data[i].transl);
		
		std::cout << "\n" << "(any char)>";

		std::cin >> ans;

		std::cout << "\n";

		(mode == 'w')? print_tilde_string(data[i].transl) : (mode == 't')? print_tilde_string(data[i].word) : (counter%6 < 3)? print_tilde_string(data[i].transl) : print_tilde_string(data[i].word);
		
		std::cout << "\n\n" << data[i].context << "\n\n(y,s/n,f)>";

		do{
			std::cin >> ans;
		}while(ans != 'y' && ans != 's' && ans != 'n' && ans != 'f');

		(ans == 'y' || ans == 's')? data[i].modrank(1) : data[i].modrank(0);

		//append word at the end of poor/medium/good
		curr_rank = data[i].sumrank();
		if ( (curr_rank<=6 && !data[i].last3_q() && !data[i].last5_q() ) || !data[i].last_q() )
			word_ranks.poor.push_back(i);
		else if ( (curr_rank>6 && curr_rank <=8 && !data[i].last5_q() ) || ( curr_rank<=6 && data[i].last3_q() && !data[i].last5_q() ) )
			word_ranks.medium.push_back(i);
		else if (curr_rank>=9 || data[i].last5_q())
			word_ranks.good.push_back(i);

		std::system("clear");
		counter--;
	}
}

void moteur_english::export_data(){
	std::string s = get_path();
	s.append("#data.fgnt");
	std::ofstream ofs{s};
	for (auto e : data) ofs << e;
	std::cout << "DATA_EXPORTED\n";
}

void moteur_english::print_tilde_string(std::string s) const{
	for (auto c : s){
		if ( c == '~'){
			std::cout << '\n';
		}
		else{
			std::cout << c;
		}
	}
}
#endif