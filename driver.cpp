#include "TSP.h"
#include <iostream>
#include <string>

int main() {
	std::string fileName;
	std::cout << "Enter filename: ";
	std::cin >> fileName;
	TSP tsp(fileName);
	tsp.solve();

	/*
	TSP firstTest("test17.txt");
	firstTest.solve(); // Answer should be 2085
	TSP secondTest("test15.txt");
	secondTest.solve();
	std::cout << "\n";
	TSP thirdTest("test19.txt");	// Crashes on files larger than 24, possibly runs out of memory
	thirdTest.solve();				// So limit between 20-24 on my machine
	*/
	
	/*
	TSP firstTest("graph1.txt");
	firstTest.solve();
	std::cout << "\n";
	TSP secondTest("graph2.txt");
	secondTest.solve();
	std::cout << "\n";
	TSP thirdTest("graph3.txt");
	thirdTest.solve();
	std::cout << "\n";
	TSP fourthTest("graph4.txt");
	fourthTest.solve();
	std::cout << "\n";
	TSP fifthTest("graph5.txt");
	fifthTest.solve();
	std::cout << "\n";
	TSP sixthTest("test1.txt");
	sixthTest.solve();
	std::cout << "\n";
	TSP seventhTest("test2.txt");
	seventhTest.solve();
	std::cout << "\n";
	*/
	return 0;
}