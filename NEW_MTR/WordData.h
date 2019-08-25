#ifndef WORDDATA
#define WORDDATA

#include <string>
#include <vector>
#include <iostream>

#include "VectorInOut.h"

struct WordData {
    //fields
    int key;
    int week;
    std::vector<int> hits;
    std::string word;
    std::string transl;
    std::string example;
    //constructors
    WordData(){}
    WordData(int k, int we, std::vector<int> h, std::string wo, std::string t, std::string e);
    //methods
    int sumRank();
    int updateRank(bool hit);
    bool lastQ();
    bool last3Q();
    bool last5Q();
};


std::istream& operator>>(std::istream& is, WordData& ed){
    char curr;
    int key, week; 
    std::vector<int> hits;
    std::string word, transl, example;

    is >> key >> curr >> week >> curr >> hits >> curr;
    while (is.get(curr) && curr != ';') word+=curr;
    while (is.get(curr) && curr != ';') transl+=curr;
    while (is.get(curr) && curr != '\n') example+=curr;

    ed = WordData(key, week, hits, word, transl, example);

    return is;
}

std::ostream& operator<< (std::ostream& os, WordData& dt){
    os << dt.key << " ; " << dt.week << " ; " << dt.hits  << " ;"  << dt.word << ";" << dt.transl << ";" << dt.example << "\n"; 
    return os;
}

//---------------------CPP------------------------------------

    WordData::WordData(int k, int we, std::vector<int> h, std::string wo, std::string t, std::string e) : 
        key(k) ,
        week(we) ,
        hits(h),
        word(wo),
        transl(t) ,
        example(e)
        {}

    //methods
    int WordData::sumRank(){
        int result = 0;
        for (int e : hits){
            result += e;
        }
        return result;
    }

    int WordData::updateRank(bool hit){
        for (int i = 0; i < 9; i++){
            hits[i] = hits[i+1];
        }
        if (hit)
            hits[9] = 1;
        else
            hits[9] = 0;

        return sumRank();
    }

    bool WordData::lastQ(){
        if (hits[9] == 1)
            return true;
        else
            return false;
    }

    bool WordData::last3Q(){
        for (int i = 7; i<10; i++) {
            if (hits[i] == 0)
                return false;
        }
        return true;
    }

    bool WordData::last5Q(){
        for (int i = 5; i<10; i++) {
            if (hits[i] == 0)
                return false;
        }
        return true;
    }

#endif