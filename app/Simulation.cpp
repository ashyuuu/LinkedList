#include "Simulation.hpp"

Simulation::Simulation()
    :enteredNum{0},exitedLine{0},exitedReg{0},lost{0},totTime{0},cap{0},currT{0},single{true}
{}

void Simulation::runSimulation(){
    setUp();
    readInput();
    std::cout<<finalOut();
}

void Simulation::setUp(){
    int numReg = 0, temp=0;
    std::string c;
    std::cin >> totTime >> numReg >> cap >> c;
    totTime*=60;
    single=(c=="S");
    for (int i = 0; i < numReg; i++){
        std::cin >> temp;
        regTime.push_back(temp);
        //weight.push_back(std::make_tuple(0,0));
        workingReg.push_back(std::make_pair(true,0)); 
        if (!single){
            Queue<int> q;
            waitLine.push_back(q);
        }
    }
    if(single){Queue<int> q; waitLine.push_back(q);}    
}

void Simulation::readInput(){
    std::string next = "",n="dd";
    int entered = 0, arrival = 0;
    std::cin >> next;
    while (true){        
        if(next!=n){
            entered = std::stoi(next);
            std::cin >> arrival;
            enteredNum += entered;
            //currT=arrival;
        }
        while(currT!=arrival)
            currT++;
        for(int j = 0; j < entered; j++){
            writeOutput(arrival,enterLine(arrival));
        } 
             
        n = next;        
        std::cin >> next;
        
        if(cond())
            enterRegister();
        if(next=="END")
            break;
    }
    clearReg();
    
}   

std::string Simulation::enterLine(int time){
    //  if (cond() ){
        //  if (waitLine.at(3).size()>0){
        //         // debug+=1;
        //         Queue<int>::ConstIterator iterator = waitLine.at(3).constIterator();
        //         for ( int k = 0; k < waitLine.at(3).size()-1;k++){
        //             std::cout<<iterator.value()<< " ";
        //             iterator.moveToNext();
        //         }
        //         std::cout<<iterator.value()<<" w"<<std::endl;
        //         }  
        // enterRegister();  
        //   if (waitLine.at(3).size()>0){
        //         // debug+=1;
        //         Queue<int>::ConstIterator iterator = waitLine.at(3).constIterator();
        //         for ( int k = 0; k < waitLine.at(3).size()-1;k++){
        //             std::cout<<iterator.value()<< " ";
        //             iterator.moveToNext();
        //         }
        //         std::cout<<iterator.value()<<" ww"<<std::endl;
        //         }   
        // std::cout<<time<<" "<<std::endl;
    // }
    int ind = 0;
    if (!single){
        for(int i = 1; i < waitLine.size(); i++){
            if (waitLine.at(i).size() < waitLine.at(ind).size())
                ind = i;
        }
    }
    // if(ind!=0&&cond())
    //     enterRegister();
    // if(time == 70 && ind == 2)
    //     std::cout<<"out"<<waitLine.at(3).front()<<" "<<waitLine.at(3).last()<<" "<<std::endl;
    // if(waitLine.at(3).size()>0)
    //     std::cout<<"out"<<waitLine.at(3).front()<<" "<<waitLine.at(3).last()<<" "<<time<<ind<<std::endl;
    //if(time == 70 && ind == 0)
    //     std::cout<<waitLine.at(3).size()<<std::endl;
    // std::cout<<waitLine.at(3).size()<< (ind ==3)<<std::endl;
    if (waitLine.at(ind).size() <= cap-1){
        // if (waitLine.at(ind).size() >0&&ind == 3){
        //     Queue<int>::ConstIterator iterator = waitLine.at(ind).constIterator();
        //     for ( int k = 0; k < waitLine.at(ind).size()-1;k++){
        //         std::cout<<iterator.value()<< "-"<<waitLine.at(ind).size()<<" ";
        //         iterator.moveToNext();
        //     }
        //     std::cout<<waitLine.at(ind).size()<<" "<<iterator.value()<<std::endl;
        // } 
        waitLine.at(ind).enqueue(time);
        // check if any dequeue would happen
        
        // if (ind == 3){
        //     Queue<int>::ConstIterator iterator = waitLine.at(ind).constIterator();
        //     for ( int k = 0; k < waitLine.at(ind).size()-1;k++){
        //         std::cout<<iterator.value()<< "/"<<waitLine.at(ind).size()<<" ";
        //         iterator.moveToNext();
        //     }
        //     std::cout<<iterator.value()<<"oo"<<std::endl;
        // } 
        return std::to_string(time) + " entered line " + std::to_string(ind+1) + " length " + std::to_string(waitLine.at(ind).size()) + "\n";   
    }        
    enteredNum--;
    lost++;
    return std::to_string(time)+" lost\n";
}
    
void Simulation::enterRegister(){
    int wait_time=0;
    for (int j = 0; j < workingReg.size(); j++){
        int i=(single)?0:j;
        if (waitLine.at(i).size() > 0 && (workingReg.at(j).first || waitLine.at(i).front()>=workingReg.at(j).second || currT >= workingReg.at(j).second) ){   
            if (currT==workingReg.at(j).second&&workingReg.at(j).second!=0){
                if (currT >= workingReg.at(j).second){
                    exitedReg++;
                    writeOutput(workingReg.at(j).second, std::to_string(workingReg.at(j).second)+" exited register "+std::to_string(i+1)+"\n");
                }   
                wait_time = workingReg.at(j).second - waitLine.at(i).front();
                waitT.push_back(wait_time);
                waitLine.at(i).dequeue();
                exitedLine++;
                
                writeOutput(currT, std::to_string(currT)+" exited line "+std::to_string(i+1)+" length "+std::to_string(waitLine.at(i).size())+" wait time "+std::to_string(wait_time)+"\n");
                writeOutput(currT, std::to_string(currT)+" entered register "+std::to_string(i+1)+"\n");        
            
            // workingReg.at(j).second = currT + regTime.at(i);
            // workingReg.at(j).first = false;
                // currT = workingReg.at(j).second;
            } else if(currT==waitLine.at(i).front()) {
                // currT = waitLine.at(i).front();
                waitT.push_back(wait_time);
                workingReg.at(j).second = currT + regTime.at(i);
                workingReg.at(j).first = false;
                waitLine.at(i).dequeue();
                exitedLine++;
                
                writeOutput(currT, std::to_string(currT)+" exited line "+std::to_string(i+1)+" length "+std::to_string(waitLine.at(i).size())+" wait time "+std::to_string(wait_time)+"\n");
                writeOutput(currT, std::to_string(currT)+" entered register "+std::to_string(i+1)+"\n");        
            
            }

            
            // if(i==3 && waitLine.at(i).size() > 0 && waitLine.at(i).last()==60)
            //     std::cout<<waitLine.at(i).front();            
            // if (waitLine.at(i).size()>1&&j == 3){
            //     // debug+=1;
            //     Queue<int>::ConstIterator iterator = waitLine.at(i).constIterator();
            //     for ( int k = 0; k < waitLine.at(i).size()-1;k++){
            //         std::cout<<iterator.value()<< " ";
            //         iterator.moveToNext();
            //     }
            //     std::cout<<iterator.value()<<" i"<<currT<<std::endl;
            //     }    
            // if(i==3 && waitLine.at(i).size() > 0 && waitLine.at(i).last()==60)
            //     std::cout<<waitLine.at(i).front();            
            // if (waitLine.at(i).size()>0&&j == 3){
            //     // debug+=1;
            //     Queue<int>::ConstIterator iterator = waitLine.at(i).constIterator();
            //     for ( int k = 0; k < waitLine.at(i).size()-1;k++){
            //         std::cout<<iterator.value()<< " ";
            //         iterator.moveToNext();
            //     }
            //     std::cout<<iterator.value()<<" ii"<<std::endl;
            //     }         
                       
        }    
    }
}

// void Simulation::updateReg(){
//     while(cond()){
//         enterRegister();
//     }
// }

bool Simulation::cond(){
    for (int i = 0; i < waitLine.size(); i++){
        if (waitLine.at(i).size() > 0 && (waitLine.at(i).front()>=workingReg.at(i).second || currT >= workingReg.at(i).second)){
            return true;
        }
    }
    return false;
}

bool Simulation::move(){
    for (int i = 0; i < waitLine.size(); i++){
        if (workingReg.at(i).second<=totTime){
            return true;
        }
    }
    return false;
}

void Simulation::clearReg(){
    // while there are still moves 
    while(move()&&currT < totTime){
        enterRegister();
        currT++;
    }
    for (int i = 0; i < workingReg.size(); i++){
        if (!workingReg.at(i).first && workingReg.at(i).second<=totTime){
            exitedReg++;
            writeOutput(workingReg.at(i).second, std::to_string(workingReg.at(i).second)+" exited register "+std::to_string(i+1)+"\n");
            workingReg.at(i).second = 0;
            workingReg.at(i).first = true;           
        }
    }
}

double Simulation::avgTime(){
    double sum=0.0;
    for (auto i : waitT)
        sum+=i;
    return sum/double(waitT.size());
}

std::string Simulation::getLog(){
    std::string s = "LOG\n0 start\n";
    for (auto i : out)
        s+=i.second;
    s+=std::to_string(totTime)+" end\n";
    return s;
}

std::string Simulation::getStats(){
    std::string a = std::to_string(avgTime());
    std::string s = "STATS\n";
    s+="Entered Line    : " + std::to_string(enteredNum) + "\n";
    s+="Exited Line     : " + std::to_string(exitedLine) + "\n";
    s+="Exited Register : " + std::to_string(exitedReg) + "\n";
    s+="Avg Wait Time   : " + a.substr(0,a.find(".")+3) + "\n";
    s+="Left In Line    : " + std::to_string(enteredNum-exitedLine) + "\n";
    s+="Left In Register: " + std::to_string(exitedLine-exitedReg) + "\n";
    s+="Lost            : " + std::to_string(lost) + "\n";
    return s;
}

void Simulation::writeOutput(int time, std::string event){ 
    out.push_back(std::make_pair(time,event));
    std::sort(out.begin(), out.end(), [](const std::pair<int,std::string> &left, const std::pair<int,std::string> &right) {return left.first < right.first;});
}

std::string Simulation::finalOut(){
    return getLog()+"\n"+getStats();
}