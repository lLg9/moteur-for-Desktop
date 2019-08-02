/*

_g9
***moteur***
2019.01.13. -- week 2
version 2.1.0


TODO:
[]	-python script for formatting conjugation 
[]	-display word ranks should also display a package's average score 
[]	-facility to display nicely a package
[]	-on startup, all package's ranks should be displayed

CONCEPT

    Word practice program with monitoring. 

FEATURES
    usage: 
	    Monitoring answers in order to query words effectively.
	    Flashcard-like system, with a y,s/n,f user input feedback.
	    Practice either (up to) 20 words or a full package (revise mode).  
	    Packages of size 60 are stored related to a language. (User input is needed to decide which package to practice.)
	    Display of g/m/p rank numbers after choosing package. (Ranking system:  poor: 0-6  ||  last_q==0  --  medium: 7-8 ||  last3_q==1 --  good  9-10 ||  last_5==1)
	tehnical: 
		Runs in a console window.
		Mass import words is facilitated from <word> ; <translation> format (using python script).
		Data and ranks are stored separetely text file. (Modification or appending manually is possible.)
		Possible to store strings of multiple lines in data ('~' should be used instead of new line)

DESIGN
    CLASSES:

		moteur_english : public moteur_rank_base, moteur_content_base   ---   CONCRETE CLASS
			contains:
				english_data
			methods:
				import_data()
				q_n_a()
				export_data()

		moteur_rank_base   ---   PROTECTED CONSTRUCTOR
			contains:
				word_ranks
				path
				no_pack
				prt vector
			methods:
				choose_package()
				import_word_ranks()
				display_word_ranks()
				load_prt()
				export_word_ranks()
				set_no_pack(int i)
				get_no_pack() const 
				set_path(std::string s)
				get_path() const 

		moteur_content_base   ---   PURE VIRTUAL METHODS
			methods: 
				virtual import_data() = 0
				virtual q_n_a() = 0
				virtual export_data() = 0





	STORING DATA: 

		separate containers for words and ranks: 

			1 container for up to 60 data entries (append only):
				data: (key) (week) (rank table) (word) (translation) (context)
		                stored:    - in a vector in memory,
		                           - ";" separated file 

			3 rank cathegories: good, medium, poor
				rank: (key)
		                stored:    -as a list in memory (3 separate lists for g-m-p)
		                           -single space separated file, newline separates the rank cathegories (g-m-p)


    RANKING: 

        *3 cathegories: poor: 0-6  ||  last_q==0  --  medium: 7-8 ||  last3_q==1 --  good  9-10 ||  last_5==1
        *last 10 query results are stored in an int array
 
  
    SORTING:
        
        *updating rank after query, and appending at the end of the proper rank list


-----------------------------------------------------------------------------------------------------------------    */



#include "moteur_english.h"

const int no_pack = 99;

int main(){

	moteur_english moteur;

	moteur.set_path("./files/Deutsch");
	moteur.set_no_pack(no_pack);
	moteur.choose_package(); //user interaction: package_no
	moteur.import_word_ranks();
	moteur.import_data();

	moteur.display_word_ranks();
	moteur.load_prt(); //user interaction: 20 or revise
	moteur.q_n_a(); //user interaction: wt, tw, random

	moteur.export_word_ranks();
	moteur.export_data();

	return 0;
}