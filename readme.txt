Name - Sushma Hanumanthu
Programming Assignment 5

The program is written in C++ Language.
tar file contains

1)Knapsack.cc - program which creates a file knapsack01.txt whose first line contains the number items and the weight capacity of the knapsack and the following lines contains the name of the item (you can just use item1 to item8), the profit of the item, and the weight of the item.
2)bruteforce.cc - program which uses brute force to solve 0/1 knapsack
3)refine.cc - program for solving 0/1 knapsack using dynamic programming
4)backtrack.cc - to solve 0/1 knapsack using backtracking algorithm
5)makefile
6)readme.txt

Steps to run program:-

Commands on Command prompt

1) make - it will compile all 4 c programs and also execute object files
 ./createkn01 -k knapsack01.txt - creates a file called knapsack01.txt which contains value of n and profit,weight
 ./bruteforce -k knapsack01.txt - it will get the inputs from knapsack01.txt and creates a file called output1.txt which contains output
 ./dynpro -k knapsack01.txt - it will get the inputs from knapsack01.txt and creates a file called output2.txt which contains output and enteries2.txt
 ./backtrack -k knapsack01.txt - it will get the inputs from knapsack01.txt and creates a file called output3.txt which contains output and 			enteries3.txt

 it will produce all output files and enteries file
