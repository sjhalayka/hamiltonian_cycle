/*

* C++ Program to Find Hamiltonian Cycle

*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;


#include "string_utilities.h"
using namespace string_utilities;





/*
* check if the vertex v can be added at index 'pos' in the Hamiltonian Cycle
*/

bool isSafe(int v, vector<vector<bool> > graph, int path[], int pos)
{
	if (graph[path[pos - 1]][v] == 0)
		return false;

	for (int i = 0; i < pos; i++)
		if (path[i] == v)
			return false;

	return true;
}



/* solve hamiltonian cycle problem */
bool hamCycleUtil(vector<vector<bool> > graph, int path[], int pos)
{
	const size_t V = graph[0].size();

	if (pos == V)
	{
		if (graph[path[pos - 1]][path[0]] == 1)
			return true;
		else
			return false;
	}

	for (int v = 1; v < V; v++)
	{
		if (isSafe(v, graph, path, pos))
		{
			path[pos] = v;

			if (hamCycleUtil(graph, path, pos + 1) == true)
				return true;

			path[pos] = -1;
		}
	}

	return false;
}

void printSolution(int path[], const size_t V)
{
	cout << "Solution Exists:";
	cout << " Following is one Hamiltonian Cycle \n" << endl;

	for (int i = 0; i < V; i++)
		cout << path[i] << "  ";

	cout << path[0] << endl;
}


/* solves the Hamiltonian Cycle problem using Backtracking.*/
bool hamCycle(vector<vector<bool> > graph)
{
	const size_t V = graph[0].size();

	vector<int> path(V, -1);

	path[0] = 0;

	if (hamCycleUtil(graph, &path[0], 1) == false)
	{
		cout << "\nSolution does not exist" << endl;

		return false;
	}

	printSolution(&path[0], V);

	return true;
}



/* Main */



class city
{
public:
	long unsigned int id;
	float x, y;
};




int main()
{
	long unsigned int num_cities = 0;

	ifstream city_file("cities.csv");
	vector<city> cities;
	string line;

	// Skip first line
	getline(city_file, line);

	size_t line_count = 0;

	while (getline(city_file, line))
	{
		line_count++;

		if ("" == line)
			continue;

		vector<string> tokens = stl_str_tok(",", line);

		if (tokens.size() != 3)
			continue;

		istringstream iss;
		city c;

		iss.str(tokens[0]);
		iss >> c.id;

		iss.clear();
		iss.str(tokens[1]);
		iss >> c.x;

		iss.clear();
		iss.str(tokens[2]);
		iss >> c.y;

		cities.push_back(c);
	}


	vector<bool> g(cities.size(), true);
	vector< vector<bool> > graph(cities.size(), g);

	hamCycle(graph);

	return 0;
}

