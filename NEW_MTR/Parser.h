#ifndef PARSER
#define PARSER

#include <string>
#include <vector>
#include <fstream>

#include "WordData.h"
#include "WordRanks.h"

class Parser {
public: 
    //constructor
    Parser(std::string dirPath);
    //public methods
    std::vector<WordData> parseData();
    WordRanks parseRanks();
    bool exportData(std::vector<WordData> data);
    bool exportRanks(WordRanks ranks);
private:
    //private fields
    const std::string PATH;
};


//---------------------CPP------------------------------------


    Parser::Parser(std::string dirPath) :
        PATH(dirPath)
        {}

    std::vector<WordData> Parser::parseData(){
        // try{
            std::vector<WordData> data;
            std::string s = PATH;
            s.append("#data.fgnt");
            std::cout << "importing_words_from: " << s << "\n";
            std::ifstream inf{s};
            WordData ed;
            int counter = 0; 
            while (inf >> ed){
                data.push_back(ed);
                counter ++;
            }
            std::cout << counter << " data entries imported\n";
            return data;
        // }catch(int i){
            //TODO...
        // }
    }

    WordRanks Parser::parseRanks(){
        WordRanks ranks;
        // try{
            std::string s = PATH;
            s.append("#ranks.fgnt");
            std::cout << "importing_ranks_from: " << s << "\n";
            std::ifstream ifs{s};
            ifs >> ranks;
            return ranks;
        // }catch(int i){
            //TODO...
        // }
    }


    bool Parser::exportData(std::vector<WordData> data){
        // try{
            std::string s = PATH;
            s.append("#data.fgnt");
            std::ofstream ofs{s};
            for (auto e : data) ofs << e;
            std::cout << "DATA_EXPORTED\n";
        // }catch(int i){
            //TODO
        // }
        return true;
    }

    bool Parser::exportRanks(WordRanks ranks){
        // try{
            std::string s = PATH;
            s.append("#ranks.fgnt");
            std::ofstream ofs{s};
            ofs << ranks;
            std::cout << "RANKS_EXPORTED\n";
        // }catch(int i){
            //TODO
        // }
        return true;
    }

#endif