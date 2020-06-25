# CustomerServiceSimulator

This is my Customer Service Traffic-Flow Simulator! 

A minute-by-minute simulation based on 6 inputs (within the attached simulation.txt file) is performed through C++ programming. The simulation should pause after each minute's summary is outputted onto the console, enabling the user to press ENTER to continue to the view the next minute's visualizations.

Please make sure to download the entire folder, consisting of BetterSimulation.cpp, PriorityQueue.h, DynamicArray.h, Queue.h, and a text file called simulation.txt. Also, make sure all five files are within the same directory.

In this program, I made use of the Priority Queue and Queue header files that I made so I could manage this program's concept.

------------------------------------------------------------------------------------------------------------------------------
NOTE: It is essential that the values written in the simulation.txt file meet these following requirements.

The BetterSimulation.cpp program will perform a minute-by-minute customer service simulation based on 6 inputs written prior by the user (from a text file, simulation.txt, as numbers only, one per line, in this order):
                
                 1. The number of servers/employees (1 or more, whole number)
                 2. The average arrival rate of customers, per minute (> 0.0, floating point)
                 3. The maximum length of the wait queue; the waiting line (>1, whole number)
                 4. The minimum service time interval, in minutes, (>1, whole number), meaning the minimum amount of time an employee will spend with helping a customer.
                 5. The maximum service time interval, in minutes (>=minimum service time interval, whole number), meaning the maximum amount of time an employee will spend with helping a customer.
                 6. The clock time at which new arrivals stop, in min (>0, whole number)

When the BetterSimulation.cpp program compiles and begins, each minute's output will include the following:
     
     - The clock time -- that is, the amount of time since the start of the simulation -- in minutes (whole number)
     - A visual representation of the wait queue

------------------------------------------------------------------------------------------------------------------------------
(For Xcode users): 
If you are on Xcode, you may need to go to Product > Scheme > Edit Scheme > Run test (on the right) > Options (middle top). Down under Options check “Use custom working directory” and set it to the directory where your .txt file is located. Sometimes Xcode has trouble locating the .txt file even though it is correctly in the same directory as the .cpp file.


