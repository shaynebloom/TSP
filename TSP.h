#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <iostream>

/*
TSP solution by Shayne Bloom
Visual Studios 2017 used to compile
Dynamic programing solution, O(n^2 * 2^n) time
Prints path if found.
*/

class TSP {
public:
	TSP(const TSP &) = delete;

	// String for file name
	TSP(std::string fileName) {
		// Read file into 2D vector
		getAdjacencyMatrix(fileName);
		memoization = new std::vector<std::vector<int>>((int)pow(2, num_city), std::vector<int>(num_city, -1)); // -1 for not visited
		path = new std::vector<std::vector<int>>((int)pow(2, num_city), std::vector<int>(num_city, -1)); // For keeping track of path
		ALL_BITS = (1 << num_city) - 1; // Bit shift one position past, then -1 to make all previous bits 1
	}
	~TSP() {
		delete adjMatrix, cityNames, memoization, path;
	}

	void solve() {
		// Position 0 is id 1, 1 is bitmask for that;
		std::vector<std::string> tour; // Vector for holding the path
		int solution = solve(0, 1); // 0 is start node id, 1 is the bitmask that says 0 has already been visited
		if (solution >= MAX) {  // If it used a path with MAX value, then the path didn't actually exist, therefore there most likely
								// wasn't Hamiltonian Cycle.
			std::cout << "No Hamiltonian Cycle";
		}
		else {
			int index = 0;
			int mask = 1;
			while (true) { // Use memoization of tour path to print path.
				tour.push_back((*cityNames).at(index));
				int nextIndex = (*path)[mask][index];
				if (nextIndex == -1)
					break;
				int nextState = mask | (1 << nextIndex); // Bit shift, bitwise or operator
				mask = nextState;
				index = nextIndex;
			}
			std::cout << "Optimal Tour Cost = [" << solution << ", <";
			std::string delim = ""; // Clever
			for (std::string i : tour) {
				std::cout << delim << i;
				delim = ","; // Is now a comma
			}
			std::cout << ">]";
		}
	}

private:
	std::vector<std::vector<int>> * adjMatrix;	// Used pointers for these so I could dynamically create with correct size instead of resizing
												// Also less overhead when "copying"
	std::vector<std::string> * cityNames;		// For storing string names, index coorelates to id number - 1
	std::vector<std::vector<int>> * memoization;// For storing previous solutions
	std::vector<std::vector<int>> *path;		// For storing previously visited node
	int num_city;
	int ALL_BITS;								// Bitmask representing all cities visited
	const int MAX = 9999999; // Using INT_MAX causes overflow errors, so I just use a really big number instead

	// Function for getting adjacency matrix from file
	void getAdjacencyMatrix(std::string fileName) {
		int id, id2, weight;
		std::string name, line;
		std::ifstream infile(fileName); // Open file
		std::istringstream strstream;

		while (std::getline(infile, line))
			num_city++; // Determine how many elements based on how many lines, potentially wrong if blank lines are used, but that shouldn't effect results, only size
						// Cound read first number to get more accurate number
		infile.close();
		infile.open(fileName); // Return to start, probably a better way than reopening same file, but this works

		adjMatrix = new std::vector<std::vector<int>>(num_city, std::vector<int>(num_city, MAX)); // Initialize 2D vector, default value INT_MAX for undefined
		cityNames = new std::vector<std::string>(num_city);

		while (std::getline(infile, line)) { // Fill in matrix
			strstream.str(line);
			strstream >> id >> name; // First two values should be id then name
			(*cityNames)[id-1] = name; // Assign name
			while (strstream >> id2 >> weight)
				(*adjMatrix)[id-1][id2-1] = weight; // Any values not assigned were default as INT_MAX already

			strstream.clear(); // Clear for reuse
		}

		for (size_t i = 0; i < (*adjMatrix).size(); i++)
			(*adjMatrix)[i][i] = 0; // Set weight to zero for travelling to same node

	}
	// Private solve function
	// Pos is current city index, mask is a bitmask for determining if there are cities left, depth is for printing path
	int solve(int pos, int mask) { 
		// Using bit masking instead of a bitset.  Capstone research paper was pretty useful.
		// Mask is passed by value, which is extremely important, you can recursively call and it doesn't forget the previous bitmask.
		if (mask == ALL_BITS) {
			return (*adjMatrix)[pos][0];
		}

		// Check memoization table
		if ((*memoization)[mask][pos] != -1) { // -1 if it has not been stored
			return (*memoization)[mask][pos];
		}

		int min = MAX;
		int cityid = -1;
		// Try to go to an unvisited city
		for (int city = 0; city < num_city; city++) {
			if (!(mask&(1 << city))) { // False if already visited.  Bitshift to city position, then bitwise and, will be zero if not visited
				int newMin = (*adjMatrix)[pos][city] + solve(city, mask | (1 << city)); // Bitwise or adds new city to bitmask.
				if (newMin == std::min(min, newMin)) {
					cityid = city; // Keep track of new path for memoization table.
				}
				min = std::min(min, newMin);

			}

		}
		(*path)[mask][pos] = cityid;
		return (*memoization)[mask][pos] = min;
	}
};