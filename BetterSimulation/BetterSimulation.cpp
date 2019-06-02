/*Programmer: Benedict Tannady*/

#include <iostream>
#include <iomanip> /*setw()*/
#include <fstream>
#include <string>
using namespace std;

#include <cstring> /*strtok(), strcpy()*/
#include <cmath> /*poisson process*/
#include <cstdlib> /*poisson process, atoi(), atof(), rand(), exit()*/
#include <ctime> /*srand()*/

#include "Queue.h"
#include "DynamicArray.h"
#include "PriorityQueue.h"

struct Customer
{
    char idTag; //alphabetical letter (65-90)
    int arrivalTime;
};

struct serverInfo
{
    Customer customer;
    bool busyStatus = false;
};

struct serviceEvent
{
    int serverNum;
    int endTime;
};

int getRandomNumberOfArrivals(double);

/*for PriorityQueue*/
bool operator<(const serviceEvent& a, const serviceEvent& b)
{
    return a.endTime < b.endTime ? false : true;
}

int main(){
    
    /*Programmer's Identification*/
    cout << "Programmer: Benedict Tannady"<< endl;
    cout << "File: " << __FILE__ << endl;
    
    /*-----------------------------------------------------------------------*/
    /*Parsing the textfile*/
    
    int lineNum = 0;
    int numOfServers;
    double averageArrivalRate;
    int maxQueueLength;
    int maxServiceTime;
    int minServiceTime;
    int arrivalStopTime;
    
    // for parsing the inputfile
    char* token;
    char buf[1000];
    const char* const tab = "\t";
    
    // open the input file
    ifstream fin;
    fin.open("simulation.txt");
    if (!fin.good()) throw "I/O error";
    
    // read the input file
    while (fin.good())
    {
        // read the line
        string line;
        getline(fin, line);
        strcpy(buf, line.c_str());
        
        if (buf[0] == 0) continue; // skip blank lines
        
        //parse the line
        
        const string stringRead(token = strtok(buf, tab));
        
        if(lineNum == 0){
            numOfServers = atoi(stringRead.c_str());
        }
        if(lineNum == 1){
            averageArrivalRate = atof(stringRead.c_str());
        }
        if(lineNum == 2){
            maxQueueLength = atoi(stringRead.c_str());
        }
        if(lineNum == 3){
            minServiceTime = atoi(stringRead.c_str());
        }
        if(lineNum == 4){
            maxServiceTime = atoi(stringRead.c_str());
        }
        if(lineNum == 5){
            arrivalStopTime = atoi(stringRead.c_str());
        }
        
        ++lineNum;
    }
    if(lineNum){
        if(lineNum == 6){
            cout << "\n---------------------------------------" << endl;
            cout << "Number of Servers: " << numOfServers << endl;
            cout << "Average Arrival Rate: " << averageArrivalRate << " per minute, for " << arrivalStopTime << " minutes" << endl;
            cout << "Max Queue Length: " << maxQueueLength << endl;
            cout << "Min Service Time: " << minServiceTime << " minutes" << endl;
            cout << "Max Service Time: " << maxServiceTime << " minutes" << endl;
            
        }
    }
    
    fin.close();
    
    /*File read successful. Continue the program.*/
    
    
    /*-----------------------------------------------------------------------*/
    /*declare and create and assign arrays and queues to be used in the solution*/
    
    Queue<Customer> waitLine;
    Queue<Customer> waitLineCopy;
    DynamicArray<serverInfo> servers;
    PriorityQueue<serviceEvent> eventList;
    
    //    for(int i = 0; i < numOfServers; i++)
    //    {
    //        cout << "halo: " << servers[i].busyStatus << endl;
    //        servers[i].busyStatus = false;
    //    }
    
    int static letterGenerator = 65; /*set to ascii of 'A'*/
    int numOfArrivals;
    srand(time(0));
    
    /*-----------------------------------------------------------------------*/
    // the clock time loop
    for (int time = 0;; time++) // the clock time
    {
        
        /*handle all services scheduled to complete at this clock time*/
        
        //event queue is not empty and its top's end-of-service time equals the clock time
        while(eventList.empty() == false && eventList.top().endTime == time)
        {
            //set the top service event's server to idle
            servers[eventList.top().serverNum].busyStatus = false;
            
            //pop the just-used service event off of the event queue
            eventList.pop();
            
        }
        
        /*-----------------------------------------------------------------------*/
        /*handle new arrivals -- can be turned away if wait queue is at maximum length*/
        
        if(time < arrivalStopTime)
        {
            /*clock time is less than the time at which new arrivals stop*/
            numOfArrivals = getRandomNumberOfArrivals(averageArrivalRate);
            numOfArrivals = getRandomNumberOfArrivals(averageArrivalRate);
            
            //            cout<< "\nFIGHTER: " <<  numOfArrivals << endl;
            for(int i = 0; i < numOfArrivals; i++)
            {
                /*for each new arrival*/
                
                if(maxQueueLength != waitLine.size())
                {
                    /*if the wait queue is NOT full*/
                    
                    /*create a new customer object*/
                    Customer *tempDude;
                    tempDude = new Customer;
                    /*assign it an ID tag (A-Z)*/
                    if(letterGenerator >= 91){
                        letterGenerator = 65;
                    }
                    tempDude->idTag = letterGenerator++;
                    /*set its arrival time equal to the current clock time*/
                    tempDude->arrivalTime = time;
                    
                    /*push the new customer onto the wait queue*/
                    waitLine.push(*tempDude);
                    
                    
                }
            }
        }
        
        /*-----------------------------------------------------------------------*/
        // for idle servers, move customer from wait queue and begin service for each server
        for(int i = 1; i <= numOfServers; i++)
        {
            //            if( servers[i-1].busyStatus == true || waitLine.empty() )
            //            {
            //                if(servers[i-1].busyStatus == true)
            //                {
            //                    cout << "activistion: hyperD!" << endl;
            //                }
            //                if((waitLine.empty())){
            //                    cout << "activistion: hyperZ!" << endl;
            //                }
            //                cout << "activistioN!: " << i << endl;
            //            }
            if( (servers[i-1].busyStatus == false) && (!waitLine.empty()) )
            {
                //                cout << "dunkirk: " << i << endl;
                /*server is idle AND the wait queue is not empty*/
                
                // copy it to the now serving list at that server's index (gives id and arrivalTime info)
                servers[i-1].customer = waitLine.front();
                
                // remove top customer from wait queue
                waitLine.pop();
                
                // set service end time to current clock time PLUS "random service interval", mark that server as busy
                int randoNum = minServiceTime + rand() % (maxServiceTime - minServiceTime + 1);
                serviceEvent tempEvent;
                tempEvent.serverNum = (i-1);
                tempEvent.endTime = (time + randoNum);
                eventList.push(tempEvent);
                servers[i-1].busyStatus = true;
                //                cout << "POOPYTOOO: " << tempEvent.endTime << "    " << tempEvent.serverNum << endl;
                
            }
        }
        
        PriorityQueue<serviceEvent> testerThing = eventList;
        //        cout << "SIZE OF PRIORITY QUEUE 1: " << eventList.size()<< endl;
        //        cout << "SIZE OF PRIORITY QUEUE 2: " << testerThing.size()<< endl;
        ////        for(int i = 0; i < eventList.size();i++)
        ////        {
        ////            cout << i << " : " << testerThing.top().serverNum << "  " << testerThing.top().endTime << endl;
        ////            testerThing.pop();
        ////        }
        //        cout << "SIZE OF PRIORITY QUEUE 3: " << eventList.size()<< endl;
        //        cout << "SIZE OF PRIORITY QUEUE 4: " << testerThing.size()<< endl;
        
        /*-----------------------------------------------------------------------*/
        /*output the summary*/
        
        cout << "\n---------------------------------------" << endl;
        cout << "   " << "Server" << "   " << "Time for end-of-service" << endl;
        cout << "   " << "------" << "   " << "-----------------------" << endl;
        
        for(int i = 0; i < eventList.size();i++)
        {
            cout << setw(7) << testerThing.top().serverNum << setw(16) << testerThing.top().endTime << endl;
            testerThing.pop();
        }
        
        //cout << "\n---------------------------------------" << endl;
        cout << endl;
        cout << "   " << "Server" << "   " << "Now Serving" << "   " << "Wait Queue" << endl;
        cout << "   " << "------" << "   " << "-----------" << "   " << "----------" << endl;
        
        for(int i = 0; i < numOfServers; i++)
        {
            
            /*display servers*/
            cout << setw(7) << i;
            
            /*display now serving*/
            if(servers[i].busyStatus){
                //                cout << "#";
                cout << setw(11) << servers[i].customer.idTag;
            }else{
                cout << setw(11) << " ";
            }
            
            /*display wait queue line*/
            cout << setw(10);
            if(i == 0)
            {
                /*for server 0 only, show the IDs of customers in the wait queue*/
                waitLineCopy = waitLine;
                for(int i = 0; i < waitLine.size()-1; i++)
                {
                    cout << waitLine.front().idTag;
                    waitLine.pop();
                }
                
            }
            
            cout << endl;
        }
        
        /*display time*/
        cout << "\nCurrent Time: " << time << endl;
        
        cout << "\n---------------------------------------" << endl;
        
        /*check for end condition, if continuing then wait for ENTER key to be pressed by user*/
        
        // if the end of the simulation has been reached, break
        if(time >= arrivalStopTime)
        {
            if(waitLine.empty())
            {
                //                    cout << "IM EMPTY FOOOOL!!!" << endl;
                int numOfIdleServers = 0;
                for(int i = 1; i <= numOfServers; i++)
                {
                    if(servers[i-1].busyStatus == false)
                    {
                        ++numOfIdleServers;
                    }
                    //                        cout << "NUMOFIDLESERVERS: " << numOfIdleServers << "   NUMOFSERVERS: " << numOfServers << endl;
                    if(numOfIdleServers == numOfServers)
                    {
                        /*End condition is met. Program will now end.*/
                        cout << "\n [End condition is met. Program will now end.]\n";
                        exit(EXIT_SUCCESS);
                    }
                }
            }
        }
        
        // pause for the user to press ENTER
        char continueButton = ' ';
        cout << "Press enter to continue..." << endl;
        while(continueButton != '\n')
        {
            cin.get(continueButton);
            break;
        }
        
        waitLine = waitLineCopy;
        
    }
    
    return 0;
}

/*Poisson Process*/
// requires cmath and cstdlib
int getRandomNumberOfArrivals(double averageArrivalRate)
{
    int arrivals = 0;
    double probOfnArrivals = exp(-averageArrivalRate);
    for (double randomValue = (double)rand( ) / RAND_MAX;
         (randomValue -= probOfnArrivals) > 0.0;
         probOfnArrivals *= averageArrivalRate / static_cast<double>(++arrivals));
    return arrivals;
}
