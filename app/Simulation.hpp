#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <iostream>
#include <vector>
#include "../core/Queue.hpp"
#include <string>
#include <algorithm>

class Simulation 
{
    private:
        unsigned int enteredNum;
        unsigned int exitedLine;
        unsigned int exitedReg;
        unsigned int lost;
        unsigned int totTime;
        unsigned int cap;
        unsigned int currT;
        // int debug=0;
        bool single;

        //std::vector<std::tuple<int,int>>weight; //vector of tuple of queue num and weight     
        std::vector<Queue<int>> waitLine; //vector of queue of arrival time 
        std::vector<std::pair<bool, int>> workingReg; //vector of register each with free? and exitTime
        std::vector<int> regTime;
        std::vector<int> waitT;
        std::vector<std::pair<int, std::string>> out;

        
        void setUp();
        void readInput();
        std::string enterLine(int time);
        void enterRegister();
        // void updateReg();
        bool cond();
        bool move();
        void clearReg();
        double avgTime();
        void writeOutput(int time, std::string event);
        std::string getLog();
        std::string getStats();
        std::string finalOut();
        
        
    public:
        Simulation();
        void runSimulation();        

};

#endif