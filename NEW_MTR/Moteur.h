#ifndef MOTEUR
#define MOTEUR

#include "iMoteur.h"
#include "WordData.h"
#include "WordRanks.h"
#include "Parser.h"

#include <bits/stdc++.h> 


class Moteur : public iMoteur {
public: 
    //constructor
    Moteur(std::string folderPath, int numToLoad);
    //public methods
    WordStruct getNext();
    void giveFeedback(bool succ);
    std::vector<WordStruct> recapMissed();
private:
    //private methods
    void loadPracticeList();
    void load20();
    void loadAll();

    //private fields
    int remaining;
    bool waitingForAnswer;
    bool contentExported;
    const std::string FOLDER_PATH;
    const int NUM_LOAD;
    std::vector<WordData> wDataVector;
    WordRanks wRanks;
    std::list<int> wPracticeList;
};


//---------------------CPP------------------------------------


    Moteur::Moteur(std::string folderPath, int numToLoad) :
        FOLDER_PATH(folderPath) ,
        NUM_LOAD(numToLoad) ,
        waitingForAnswer(false),
        contentExported(false)
    {
        Parser pars = Parser(FOLDER_PATH);
        wDataVector = pars.parseData();
        wRanks = pars.parseRanks();
        loadPracticeList();
        remaining = wPracticeList.size();
    }

    WordStruct Moteur::getNext() {
        WordStruct ws;
        if (remaining > 0 && !waitingForAnswer){
            ws.remain = remaining;
            ws.word = wDataVector[wPracticeList.front()].word;
            ws.transl = wDataVector[wPracticeList.front()].transl;
            ws.example = wDataVector[wPracticeList.front()].example;
            remaining--;
            waitingForAnswer = true;
            return ws;
        }

        else if (remaining == 0 && !contentExported){
            ws.remain = 888;
            ws.word = "good: " + std::to_string(wRanks.good.size());
            ws.transl = "medium: " + std::to_string(wRanks.medium.size());
            ws.example = "poor: " + std::to_string(wRanks.poor.size());
            Parser pars = Parser(FOLDER_PATH);
            pars.exportData(wDataVector);
            pars.exportRanks(wRanks);
            contentExported = true;
            return ws;
        }
        else if (remaining == 0 && contentExported){
            ws.remain = 888;
            ws.word = "good: " + std::to_string(wRanks.good.size());
            ws.transl = "medium: " + std::to_string(wRanks.medium.size());
            ws.example = "poor: " + std::to_string(wRanks.poor.size());
            return ws;
        }

    }

    void Moteur::giveFeedback(bool succ) {
        //TBD: add missed ones to wMmissedList
        if (remaining >= 0 && waitingForAnswer) {
            int current = wPracticeList.front();
            wPracticeList.pop_front();
            int newrank = wDataVector[current].updateRank(succ);
            if ((newrank <= 6 && !wDataVector[current].last3Q() && !wDataVector[current].last5Q()) || !wDataVector[current].lastQ()) {
                wRanks.poor.push_back(current);
            } else if ((newrank > 6 && newrank <= 8 && !wDataVector[current].last5Q()) || (newrank <= 6 && wDataVector[current].last3Q() && !wDataVector[current].last5Q())) {
                wRanks.medium.push_back(current);
            } else if (newrank >= 9 || wDataVector[current].last5Q()) {
                wRanks.good.push_back(current);
            }
            waitingForAnswer = false;
        }
    }

    std::vector<WordStruct> Moteur::recapMissed() {
        return std::vector<WordStruct>();
    }

    void Moteur::loadPracticeList(){
        if (NUM_LOAD==20){
            load20();
        }
        else{
            loadAll();
        }
    }

    void Moteur::load20(){
        int counter = 20;
        for (int i = 0; i < 12; i++){
            if (wRanks.poor.size() != 0){
                wPracticeList.push_back(wRanks.poor.front());
                wRanks.poor.pop_front();
                counter--;
            }
            else break;
        }
        for (int i = 0; i < 6; i++){
            if (wRanks.medium.size() != 0){
                wPracticeList.push_back(wRanks.medium.front());
                wRanks.medium.pop_front();
                counter--;
            }
            else break;
        }
        while (counter != 0 && wRanks.good.size() != 0){
            wPracticeList.push_back(wRanks.good.front());
            wRanks.good.pop_front();
            counter--;
        }
        std::vector<int> tempvec = std::vector<int>(wPracticeList.begin(), wPracticeList.end());
        std::shuffle (tempvec.begin(), tempvec.end(), std::default_random_engine(0));
        wPracticeList = std::list<int>(tempvec.begin(), tempvec.end());
    }

    void Moteur::loadAll(){
        for (int i : wRanks.poor)
            wPracticeList.push_back(i);
        for (int i : wRanks.medium)
            wPracticeList.push_back(i);
        for (int i : wRanks.good)
            wPracticeList.push_back(i);
        wRanks.good.clear();
        wRanks.medium.clear();
        wRanks.poor.clear();
        std::vector<int> tempvec = std::vector<int>(wPracticeList.begin(), wPracticeList.end());
        std::shuffle (tempvec.begin(), tempvec.end(), std::default_random_engine(0));
        wPracticeList = std::list<int>(tempvec.begin(), tempvec.end());
    }

#endif