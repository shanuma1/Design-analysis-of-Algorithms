all:
	g++ Knapsack.cc -o createkn01
	g++ bruteforce.cc -o bruteforce
	g++ refine.cc -o dynpro
	g++ backtrack.cc -o backtrack
