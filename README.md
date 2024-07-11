## Balls and Bins

This project provides tools to simulate and analyze several balls-and-bins algorithms. 
The model considers uniform, one-dimensional balls and bins. The balls arrive one at a time. Each ball picks a bin independently.
The algorithms consider vary the number of sampled bins. Specifically the number of sampled bins may be either 1 (picking a bin u.a.r.), 2 (using the power of 2 choices), or $n$ (selecting the bin with the minimal current load). 

For further details, please refer to the paper:

Mitzenmacher, Michael., [The power of two choices in randomized load balancing](https://citeseerx.ist.psu.edu/document?repid=rep1&type=pdf&doi=2b5c5a64a4403f3f22ed7f7170e3a559e0687443), IEEE Transactions on Parallel and Distributed Systems 12.10 (2001): 1094-1104.

The source files are described below. More detailed documentation is found within the source files.

##### BallsNBins.cpp, BallsNBins.h #
The main source and header files, containing the balls-and-bins simulator and a main function that runs it.
The simulator can write to either results (.res) files or log (.log) files, as chosen by the "verbose" level. 

##### settings.cpp, settings.h # 
Some accessory functions, parameters, and types.

##### ResFileParser.py
A python script that parses the result (.res) files and generates plots.

