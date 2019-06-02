# CustomerServiceSimulator

Hi,

This is my Customer Service Runtime Simulator! 
Please make sure to download the entire folder, consisting of BetterSimulation.cpp, PriorityQueue.h, DynamicArray.h, Queue.h, and a text file called simulation.txt.

In this program, I made use of the Priority Queue and Queue header files that I made so I could manage this program's concept.

------------------------------------------------------------------------------------------------------------------------------

The BetterSimulation.cpp program will perform a minute-by-minute customer service simulation based on 6 inputs written prior by the user (from a text file, simulation.txt, as numbers only, one per line, in this order):
                 1. The number of servers/employees (1 or more, whole number)
                 2. The average arrival rate of customers, per minute (> 0.0, floating point)
                 3. The maximum length of the wait queue; the waiting line (>1, whole number)
                 4. The minimum service time interval, in minutes, (>1, whole number), meaning the minimum amount of time an                       employee will spend with helping a customer.
                 5. The maximum service time interval, in minutes (>=minimum service time interval, whole number), meaning the                     maximum amount of time an employee will spend with helping a customer.
                 6. The clock time at which new arrivals stop, in min (>0, whole number)
         
Each minute's output will include the following:
- The clock time -- that is, the amount of time since the start of the simulation -- in minutes (whole number)
- A visual representation of the wait queue

ALSO NOTE:


