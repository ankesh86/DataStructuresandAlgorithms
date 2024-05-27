//Name - Ankesh Kumar
//NU ID - 002208893

//Declaring standard library
#include <iostream>
#include <fstream>  
#include <stdexcept>
#include <climits> // for INT_MAX (places where we need to set infinity to the values)
#include <algorithm> //using it for Sort method required on Kruskal's

#define maxints 100
using namespace std;

//Function declaration
void DFS(int startVertex, int numVertices, bool visited[], int** adjMatrix); //Function for Depth First Search
void primMST(int** graph, int V); //Function for Minimum Spanning Tree using Prim's algorithm
void KruskalMST(int** graph, int V); //Function for Minimum Spanning Tree using Kruskal's algorithm
void Dijkstra(int** graph, int V, int src); //Function for Shortest Path using Dijkstra's algorithm
bool BellmanFord(int** graph, int src, int V); //Function for Shortest Path using Bellman-Ford algorithm

//Main function begins
int main() {
	ifstream inf;
	int count = 0;
	int x;
	int list[maxints];
	inf.open("GraphData.txt");
	if (inf.fail())
	{
		cerr << "Error: Could not open input file\n";
		exit(1);
	}
	//activate the exception handling of inf stream
	inf.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	while (count < maxints) { //keep reading until reading maxints or
				 //until a reading failure is caught.
		try { inf >> x; }
		//Check for reading failure due to end of file or
		// due to reading a non‐integer value from the file.
		catch (std::ifstream::failure e) {
			break;
		}
		list[count++] = x;
	}

	const int numVertices = list[0];

	// Step 1: Allocating memory for the array of pointers (rows).
	int** AdjMatrix = new int*[numVertices];

	// Step 2: Allocating memory for each row and initialize with zeros.
	for (int i = 0; i < numVertices; ++i) {
		AdjMatrix[i] = new int[numVertices](); // The () at the end initializes the array to 0.
	}

	// Step 3: Fill in the adjacency matrix with the weights.
	// Note that we start at index 1 because index 0 contains the number of vertices.
	for (int i = 1; i < count; i += 3) {
		int u = list[i] ;     // Convert to 0-based index.
		int v = list[i + 1] ; // Convert to 0-based index.
		int w = list[i + 2];     // Weight of the edge.
		AdjMatrix[u][v] = w;     // For a undirected graph.
		AdjMatrix[v][u] = w;
	}

	// Use the AdjMatrix for whatever operations you need here...
	bool* visited = new bool[numVertices]();
	for (int i = 0; i < numVertices; ++i) {
		visited[i] = false;
	}

	// Start DFS from vertex 0
	DFS(0, numVertices, visited, AdjMatrix);

	// Check if all vertices are visited
	bool isConnected = true;
	for (int i = 0; i < numVertices; ++i) {
		if (!visited[i]) {
			isConnected = false;
			break;
		}
	}

	// If the graph is not connected, printing message and exit
	if (!isConnected) {
		cout << "The graph is not connected." << endl;
		return 1;
	}
	else {
		cout << "The graph is connected." << endl;
		// Printing the AdjMatrix
		for (int i = 0; i < numVertices; ++i) {
			for (int j = 0; j < numVertices; ++j) {
				cout << AdjMatrix[i][j] << " ";
			}
			cout << endl;
		}
	}

	//Minimum Spanning Tree
	cout << "-------------------------------Minimum Spanning Tree-------------------------------------------------" << endl;

	//Kruskal Algorithm
	cout << "Using Kruskal Algorithm" << endl;
	KruskalMST(AdjMatrix, numVertices);

	//Prims Algorithm
	cout << "Using Prims Algorithm" << endl;
	primMST(AdjMatrix, numVertices);

	//Single-Source Shortest Path
	cout << endl <<"----------------------------------------Single-Source Shortest Path---------------------------------------------" << endl;
	
	//Dijkstra Algorithm
	cout << "Using Dijkstra Algorithm" << endl;
	Dijkstra(AdjMatrix, numVertices, 0);

	//Bellman-Ford's algorithm
	cout << "Using Bellman-Ford's Algorithm" << endl;
	if (!BellmanFord(AdjMatrix, 0, numVertices)) {
		cout << "Graph contains a negative-weight cycle" << endl;
	}
	else {
		cout << "No negative-weight cycle detected" << endl;
	}

	// Deallocating memory for visited array
	delete[] visited;

	// Deallocating memory for AdjMatrix
	for (int i = 0; i < numVertices; ++i) {
		delete[] AdjMatrix[i];
	}
	delete[] AdjMatrix;

	// ... (Any additional code if needed)

	return 0; // Successful execution
}

class Stack {
private:
	int *arr;
	int capacity;
	int topIndex;

public:
	Stack(int size) : capacity(size), topIndex(-1) {
		arr = new int[capacity];
	}

	~Stack() {
		delete[] arr;
	}

	void push(int element) {
		if (topIndex >= capacity - 1) {
			throw std::out_of_range("Stack Overflow");
		}
		arr[++topIndex] = element;
	}

	int pop() {
		if (topIndex < 0) {
			throw std::out_of_range("Stack Underflow");
		}
		return arr[topIndex--]; // Change the order to return before decrement
	}

	int top() {
		if (topIndex < 0) {
			throw std::out_of_range("Stack Underflow");
		}
		return arr[topIndex]; // Just return the top element
	}

	bool isEmpty() {
		return topIndex < 0;
	}
};

//Implemetation of Depth First Search using the Stack Data structure
void DFS(int startVertex, int numVertices, bool visited[], int** adjMatrix) {
	Stack s(numVertices);

	s.push(startVertex);
	visited[startVertex] = true;

	while (!s.isEmpty()) {
		int v = s.top();
		bool foundUnvisited = false;

		for (int i = 0; i < numVertices; i++) {
			if (adjMatrix[v][i] != 0 && !visited[i]) {
				s.push(i);
				visited[i] = true;
				foundUnvisited = true;
				break; // Found an unvisited adjacent vertex, so break
			}
		}

		if (!foundUnvisited) {
			s.pop(); // If no unvisited adjacent vertices, pop the stack
		}
	}
}


//Implementation of Kruskal's algorithm for MST
struct Edge {
	int u, v, weight;
};

struct subset {
	int parent;
	int rank;
};

// Function to compare two edges according to their weights.
bool compareEdge(const Edge& a, const Edge& b) {
	return a.weight < b.weight;
}

// Function to find set of an element i (uses path compression)
int find(subset subsets[], int i) {
	if (subsets[i].parent != i)
		subsets[i].parent = find(subsets, subsets[i].parent);
	return subsets[i].parent;
}

// Function that does union of two sets of x and y (uses union by rank)
void Union(subset subsets[], int x, int y) {
	int xroot = find(subsets, x);
	int yroot = find(subsets, y);

	if (subsets[xroot].rank < subsets[yroot].rank)
		subsets[xroot].parent = yroot;
	else if (subsets[xroot].rank > subsets[yroot].rank)
		subsets[yroot].parent = xroot;
	else {
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
	}
}

void createEdgeList(int** graph, Edge edges[], int V, int &numEdges) {
	numEdges = 0; // Reset the number of edges
	for (int i = 0; i < V; ++i) {
		for (int j = i + 1; j < V; ++j) {
			if (graph[i][j] != 0 && graph[i][j] != INT_MAX) {
				edges[numEdges].u = i;
				edges[numEdges].v = j;
				edges[numEdges].weight = graph[i][j];
				++numEdges;
			}
		}
	}
}

//Printing the Kruskals MST from edges
void printMST(Edge mst[], int V) {
	int mst_weight = 0;
	cout << "Edge \tWeight\n";
	for (int i = 0; i < V - 1; ++i) {
		cout << mst[i].u << " -- " << mst[i].v << " == " << mst[i].weight << endl;
		mst_weight += mst[i].weight;
	}
	cout << "Weight of Minimum Spanning Tree is " << mst_weight << endl;
}

void KruskalMSTEdges(Edge edges[], int numEdges, subset subsets[], Edge mst[], int V) {
	sort(edges, edges + numEdges, compareEdge);

	int e = 0;
	for (int i = 0; e < V - 1 && i < numEdges; ++i) {
		Edge next_edge = edges[i];
		int x = find(subsets, next_edge.u);
		int y = find(subsets, next_edge.v);

		if (x != y) {
			mst[e++] = next_edge;
			Union(subsets, x, y);
		}
	}
}

void KruskalMST(int** graph, int V) {
	int MAX_EDGES = V * (V - 1) / 2;
	Edge* edges = new Edge[MAX_EDGES];
	int numEdges;

	subset* subsets = new subset[V];
	for (int v = 0; v < V; ++v) {
		subsets[v].parent = v;
		subsets[v].rank = 0;
	}

	Edge* mst = new Edge[V - 1];

	//Calling the function to perforn respection operation
	createEdgeList(graph, edges, V, numEdges);
	KruskalMSTEdges(edges, numEdges, subsets, mst, V);
	printMST(mst, V);

	//cleanup
	delete[] edges;
	delete[] subsets;
	delete[] mst;
}

//Implementation of Prim's algorithm for MST
int minKey(int key[], bool mstSet[], int V) {
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (mstSet[v] == false && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}

//Printing logic for the MST
void printprimMST(int parent[], int** graph, int V) {
	int mst_weight = 0;
	cout << "Edge \tWeight\n";
	for (int i = 1; i < V; i++) {
		cout << parent[i] << " -- " << i << " == " << graph[i][parent[i]] << "\n";
		mst_weight += graph[i][parent[i]];
	}
	cout << "Weight of Minimum Spanning Tree is " << mst_weight << endl;
}

void primMST(int** graph, int V) {
	int* parent = new int[V]; // Array to store constructed MST
	int* key = new int[V];    // Array for key values
	bool* mstSet = new bool[V]; // Using it as set of vertices not yet included in MST

	// Initializing all keys as INFINITE and mstSet as false
	for (int i = 0; i < V; i++) {
		key[i] = INT_MAX;
		mstSet[i] = false;
	}

	// Always include first 1st vertex in MST.
	key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
	parent[0] = -1; // First node is always root of MST

	// The MST will have V vertices
	for (int count = 0; count < V - 1; count++) {
		// Picking the minimum key vertex from the set of vertices not yet included in MST
		int u = minKey(key, mstSet, V); // Corrected to pass V to minKey

		// Adding the picked vertex to the MST Set
		mstSet[u] = true;

		// Update key value and parent index of the adjacent vertices of
		// the picked vertex. Consider only those vertices which are not yet included in MST
		for (int v = 0; v < V; v++)
			if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v])
				parent[v] = u, key[v] = graph[u][v];
	}

	// printing the constructed MST
	printprimMST(parent, graph, V);

	// Deallocate memory for the dynamic arrays
	delete[] parent;
	delete[] key;
	delete[] mstSet;
}

//Implementation of Single Shortest path algorithms

//Logic for Initializing Single Source
void InitializeSingleSource(int dist[], bool sptSet[], int src, int V) {
	for (int i = 0; i < V; i++) {
		dist[i] = INT_MAX;  // Set distance to INFINITY
		sptSet[i] = false;  // Set all vertices as not included in MST
	}
	dist[src] = 0;  // Distance from source to itself is always 0
}

//Logic for relaxing the 
void Relax(int u, int v, int** graph, int dist[], int pred[], int V) {
	if (graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
		dist[v] = dist[u] + graph[u][v];
		pred[v] = u;
	}
}

int minDistance(int dist[], bool sptSet[], int V) {
	int min = INT_MAX, min_index;
	for (int v = 0; v < V; v++)
		if (!sptSet[v] && dist[v] <= min)
			min = dist[v], min_index = v;
	return min_index;
}

//Method to record the predecossor
void printPath(int pred[], int j) {
	if (pred[j] == -1) // Base case: if j is source
		return;
	printPath(pred, pred[j]); // Recursive call to print the previous vertex
	cout << " -> " << j; // Printing current vertex
}

//Logic to print path
void printShortestPath(int dist[], int pred[], int src, int V) {
	cout << "Vertex\tDistance\tPath\n";
	for (int i = 0; i < V; i++) {
		cout << src << " -> " << i << "\t " << dist[i] << "\t\t" << src;
		printPath(pred, i);
		cout << "\n";
	}
}

//Dijkstra Algorithm
void Dijkstra(int** graph, int V, int src) {
	// Dynamic allocation
	int* dist = new int[V];
	bool* sptSet = new bool[V];
	int* pred = new int[V];

	// Initialization
	for (int i = 0; i < V; i++) {
		dist[i] = INT_MAX;
		sptSet[i] = false;
		pred[i] = -1;
	}

	InitializeSingleSource(dist, sptSet, src, V);
	for (int i = 0; i < V; i++) {
		pred[i] = -1; // Initialize all predecessors as -1
	}

	for (int count = 0; count < V - 1; count++) {
		int u = minDistance(dist, sptSet, V);
		sptSet[u] = true;
		for (int v = 0; v < V; v++) {
			Relax(u, v, graph, dist, pred, V);
		}
	}

	//Printing solution and cleanup
	printShortestPath(dist, pred, src, V); 

	delete[] dist;
	delete[] sptSet;
	delete[] pred;
}

//Bellman-Ford Algorithm
bool BellmanFord(int** graph, int src, int V) {
	int* dist = new int[V];
	bool* changed = new bool[V];
	int* pred = new int[V]; 

	// Step 1: Initialize distances and predecessors
	for (int i = 0; i < V; ++i) {
		dist[i] = INT_MAX;
		changed[i] = false;
		pred[i] = -1; // Initializing predecessors
	}
	dist[src] = 0;
	changed[src] = true;

	// Step 2: Relax all edges |V| - 1 times
	for (int i = 1; i <= V - 1; ++i) {
		bool anyChanged = false;
		for (int u = 0; u < V; ++u) {
			if (!changed[u]) continue;
			for (int v = 0; v < V; ++v) {
				if (graph[u][v] && graph[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
					dist[v] = dist[u] + graph[u][v];
					changed[v] = true;
					pred[v] = u; // Updating predecessor
					anyChanged = true;
				}
			}
		}
		if (!anyChanged) break;
		fill(changed, changed + V, false); // Reset new array for the next iteration
	}

	// Step 3: Checking for negative-weight cycles (optimization part)
	for (int u = 0; u < V; ++u) {
		for (int v = 0; v < V; ++v) {
			if (graph[u][v] && graph[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
				delete[] dist;
				delete[] changed;
				delete[] pred;
				return false; // If an update is possible, a negative cycle exists
			}
		}
	}

	// Printing solution and cleanup
	printShortestPath(dist, pred, src, V);

	delete[] dist;
	delete[] changed;
	delete[] pred;
	return true;
}

