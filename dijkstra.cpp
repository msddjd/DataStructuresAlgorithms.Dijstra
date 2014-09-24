#include "queue.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "graph.h"
#include <stdlib.h>
#include <boost/algorithm/string.hpp>
#include "SeparateChaining.h"
using namespace boost;
using namespace std;

struct VertexType
{
	string name;
	bool marked;
	int distance;
	string previous;	
};

void sort(VertexType a[], int numVertices);
void insertionSort(string cities[], int numVertices);
void checkInFile(int argc);
void buildDGraph(Graph<string> &dGraph, string filename, string cities[], int &numVertices, int &numEdges, VertexType myVertices[]);
void printCities(Graph<string> dGraph, int numVertices, VertexType myVertices[], string cities[]);
string setStart(string start, Graph<string> &dGraph, int numVertices, VertexType myVertices[]);
void printRow(int location, VertexType myVertices[]);
int findMin(VertexType myVertices[], int numVertices);
void dijkstra(Graph<string> &dGraph, int numVertices, VertexType myVertices[],string cities[]);
bool allMarked(int numVertices, VertexType myVertices[]);
void print(vector <string> & v);

int main(int argc, char* argv[])
{
	checkInFile(argc);	// Checks to see if Filename is given

	// Creation of Input File:
	string filename = argv[1];

	Graph<string> dGraph;// a Graph of strings 
	int numVertices = 0;
	int numEdges= 0;
	VertexType myVertices [50];
	string cities [50];
	Queue<string> adjvertexQ;
	buildDGraph(dGraph, filename, cities, numVertices, numEdges, myVertices);	// Builds the Graph using the data from the external file.
	printCities(dGraph, numVertices, myVertices, cities);	// Prints Cities found in file
//	dijkstra(dGraph, numEdges, myVertices);	// Computes Dijkstra's Algorithm:


}
	
void print(vector <string> & v)
{
	for(int i = 0; i < v.size(); i++)
	cout << "\"" << v[i] << "\"\n";
	cout << endl;
}


// Checks to see if Filename is given:
void checkInFile(int argc)
{
	if(argc < 2)
	{cout << "Incorrect Entry, please enter the name of the file containing the Graph Data" << endl;
	exit(1);}
	
}

// Computes Dijkstra's Algorithm:
void dijkstra(Graph<string> &dGraph, int numVertices, VertexType myVertices[],string cities[])
{
	Queue<string> adjvertexQ;
	cout << "\tPlease input your starting vertex:";
	string start;
	cin >> start;

	bool found = false;
	for(int i = 0; i < numVertices; i++)
	if( start == cities[i] )
	found = true; 

		if(found)
		dGraph.GetToVertices( (setStart(start,dGraph,numVertices,myVertices)), adjvertexQ ); //Find start and also find its adjacents
		else
		{	cout << start << " Is an Incorrect Entry...Press Enter to try again" << endl;
			cin.get();	
			cin.get();
			printCities(dGraph,numVertices,myVertices,cities);
		}




	//For each adjvertex determine the weight value that exists between each one and your current vertx
	//if adjacent vertex is unmarked and distance value of that adjacent vertes is greater than sum of the weight value plus the distance of the last marked vertex
//	while(!adjvertexQ.isEmpty())
//	{cout << adjvertexQ.dequeue() << endl; }

	string adjvertex;
	string current = start;
	int adjindex,currindex;
			
	for(int i = 0; i < numVertices; i++)
	if(current == myVertices[i].name)
	currindex = i;

	while(	!allMarked(numVertices,myVertices) )
	{

	
		while(!adjvertexQ.isEmpty())	//if queue is not empty get top
          {	adjvertex = adjvertexQ.dequeue();

		if(!dGraph.IsMarked(adjvertex)) //if adjacent is not marked
		{
		//	cout << adjvertex << " was not marked" << endl;	
	
			//Find adjvertex in my Vertices 
			for(int i = 0; i < numVertices; i++)
			if(adjvertex == myVertices[i].name)
			adjindex = i;

		
	
			//if its distance value in the table is greater than the sum of the weight value plus the distance of the last marked vertex
			//
		//	cout << myVertices[index].distance << endl;
		//	cout <<	 (dGraph.WeightIs(current,adjvertex) + myVertices[currindex].distance) << endl;
			if( myVertices[adjindex].distance > (dGraph.WeightIs(current,adjvertex) + myVertices[currindex].distance) )
			myVertices[adjindex].distance = (dGraph.WeightIs(current,adjvertex) + myVertices[currindex].distance );
		//	cout << myVertices[index].distance << endl;
				
			//set previous of all adjacents to current
			myVertices[adjindex].previous = current;
		//	cout << myVertices[index].name << endl;
		//	cout << myVertices[index].previous << endl;
		}		
	}   
		
			//Find min distance, set it to new current index
			if( (findMin(myVertices, numVertices)) >= 0) 
			currindex = findMin(myVertices, numVertices); 
			current = myVertices[currindex].name;
			cout << myVertices[currindex].name << "\t\t\t" << myVertices[currindex].distance << "\t\t\t" << myVertices[currindex].previous << endl;
			
			//Mark that vertex
			myVertices[currindex].marked = true;
			dGraph.MarkVertex(myVertices[currindex].name);
		

			     		

	
			dGraph.GetToVertices( current, adjvertexQ ); //Find adjacents
		
	}

	
//	sort(myVertices,numVertices);

//	cout << "Vertex\t\tDistance\t\tPrevious" << endl << endl;

//	for(int i = 0; i < numVertices; i++)
//	cout << myVertices[i].name << "\t\t" << myVertices[i].distance << "\t\t" << myVertices[i].previous << endl;

}

// Sorts VertexType Array:
void sort(VertexType a[], int numVertices) //After dijkstra's algorithm is complete sort in order of weights
{

	for(int p =0; p < numVertices; p++)
	{	
		int dist = a[p].distance;
		int j;

		for(j = p; j>0 && dist < a[j-1].distance;j--)
		a[j] = a[j-1];

		a[j].distance = dist;

	}
	
	

}

// Checks to see if all Vertices have been marked:
bool allMarked(int numVertices, VertexType myVertices[])
{
	bool allmarked = true;
	for(int i = 0; i < numVertices; i++)
	if(myVertices[i].marked == false)
	allmarked = false;

	return allmarked; 

}

// Builds the Graph using the data from the External File:
void buildDGraph(Graph<string> &dGraph, string filename, string cities[], int &numVertices, int &numEdges, VertexType myVertices[])
{
	ifstream infile;
	infile.open(filename.c_str());
	string content = "";
	vector <string> fields;
	HashTable<string> CitiesVisited("zzz");

	int slot = 0;
	getline(infile,content);

	VertexType fromVertex,toVertex;
	
	
	while(infile)
	{
		cout << "First Line:\t" << content << endl;	
		split( fields, content, is_any_of(";") );
		print(fields);


		if( CitiesVisited.find(fields[0]) != fields[0] ) //If city not in hash
		{	
//			fromVertex.name = fields[0];
			
			VertexType fromVertex = { fields[0], false, INT_MAX, "-"};	//Create a Vertex for it
			myVertices[slot]=fromVertex;
			dGraph.AddVertex(fromVertex.name);
			CitiesVisited.insert(fields[0]);
			cities[slot]=fields[0];
			numVertices++;
			slot++;
		}

		if( CitiesVisited.find(fields[1]) != fields[1] ) //If city not in hash
		{

			toVertex.name = fields[1];
			VertexType toVertex = { fields[1], false, INT_MAX, "-"};
			myVertices[slot]=toVertex;
			dGraph.AddVertex(toVertex.name);
			numVertices++;
			cities[slot]=fields[1];
			CitiesVisited.insert(fields[1]);
			slot++;
		}

		dGraph.AddEdge( fields[0],fields[1],atoi(fields[2].c_str()) );
		numEdges++;
	
		getline(infile,content);

	}
	infile.close();

	cout << "numVertices = " << numVertices << endl;
	cout << "numEdges = " << numEdges << endl;

	insertionSort(cities,numVertices);


//	cout << "sizeof = " << sizeof(cities);
//	for(int j = 0; j < numVertices; j++)
//	cout << "City#" << j << " :" << cities[j] << endl;


}

// Prints Cities found in External File:
void printCities(Graph<string> dGraph, int numVertices, VertexType myVertices[], string cities[])
{

	system("clear");
	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^\tDIJKSTRA'S ALGORITHM\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
	cout << "\n\tA Weighted Graph Has Been Built For These " << numVertices << " Cities :\n" << endl;

	for(int i = 0; i < numVertices; i++)
	{	cout << "\t\t" << cities[i];
		if((i+1)%3==0)
		cout << endl;
	}

	cout << endl;

	dijkstra(dGraph,numVertices,myVertices,cities);



}
// Sorts the Cities Alphabetically:
void insertionSort(string cities[], int numVertices)
{

	for(int p =0; p < numVertices; p++)
	{	
		string tmp = cities[p];
		int j;

		for(j = p; j>0 && tmp < cities[j-1];j--)
		cities[j] = cities[j-1];

		cities[j] = tmp;

	}

}

//Sets the Starting Value in Dijsktra's Algorithm:
string setStart(string start, Graph<string> &dGraph, int numVertices, VertexType myVertices[])
{
	//Find start in myVertices
	int location;
	for(int i = 0; i < numVertices; i++)	
	{
		cout << myVertices[i].name << endl;
		if(start == myVertices[i].name)
		location = i;
	}

//	cout << "Found in slot " << location << " Word is:" << myVertices[location].name << endl;

	myVertices[location].marked = true;
	myVertices[location].distance = 0;
	myVertices[location].previous = "N/A";

	dGraph.MarkVertex(start);
	
	cout << endl << endl;
	cout << "Vertex\t\t\tDistance\t\t\tPrevious" << endl << endl;
	cout << myVertices[location].name << "\t\t\t" << myVertices[location].distance << "\t\t\t" << myVertices[location].previous << endl;

	return start;

}

// Finds the minimum non-marked values in VertexType Array:
int findMin(VertexType myVertices[], int numVertices)
{

	int mindist = INT_MAX;
	for(int i = 0; i < numVertices; i++)
	{
		if(myVertices[i].marked==false)
		{if(myVertices[i].distance < mindist)
			mindist = myVertices[i].distance;
		}
	
	}

	for(int i = 0; i < numVertices; i++)
	{
		if(myVertices[i].distance == mindist)
		return i;	

	}
	return -1;

}

// Prints a given row in a Summary Table:
void printRow(int location, VertexType myVertices[])
{


}
