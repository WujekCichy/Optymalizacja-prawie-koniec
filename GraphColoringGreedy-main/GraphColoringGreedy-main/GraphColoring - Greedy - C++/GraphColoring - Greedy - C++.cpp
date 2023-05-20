// A C++ program to implement greedy algorithm for graph coloring
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
using namespace std;

// A class that represents an undirected graph
class Graph
{
    int V;    // No. of vertices
    list<int>* adj;    // A dynamic array of adjacency lists
public:
    // Constructor and destructor
    Graph(int V) { this->V = V; adj = new list<int>[V]; }
    ~Graph() { delete[] adj; }

    // function to add an edge to graph
    void addEdge(int v, int w);

    // Prints greedy coloring of the vertices
    void greedyColoring();

    int calculateCost(vector<int>& result);
};

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);  // Note: the graph is undirected
}

// Assigns colors (starting from 0) to all vertices and prints
// the assignment of colors
void Graph::greedyColoring()
{
    vector <int> result;
    // Assign the first color to first vertex
    result.push_back(0);

    // Initialize remaining V-1 vertices as unassigned
    for (int u = 1; u < V; u++)
        result.push_back(-1);  // no color is assigned to u

    // A temporary array to store the available colors. 1
    // value of available[cr] would mean that the color cr is
    // assigned to one of its adjacent vertices
    vector<int> available;

    for (int cr = 0; cr < V; cr++)
        available.push_back(0);

    // Assign colors to remaining V-1 vertices
    for (int u = 1; u < V; u++)
    {
        // Process all adjacent vertices and flag their colors
        // as unavailable
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (result[*i] != -1)
                available[result[*i]] = 1;

        // Find the first available color
        int cr;
        for (cr = 0; cr < V; cr++)
            if (available[cr] == 0)
                break;

        result[u] = cr; // Assign the found color

        // Reset the values back to 0 for the next iteration
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (result[*i] != -1)
                available[result[*i]] = 0;
    }

    // print the result
    for (int u = 0; u < V; u++)
        cout << "Vertex " << u << " --->  Color "
        << result[u] << endl;
    int cost = calculateCost(result);
    cout << "Total cost of graph coloring: " << cost << endl;
}
int Graph::calculateCost(vector<int>& result)
{
    int maxColor = 0;
    for (int u = 0; u < V; u++)
    {
        if (result[u] > maxColor)
            maxColor = result[u];
    }
    return maxColor + 1; // Zwraca największy kolor + 1 jako koszt
}

// Driver program to test above function
int main()
{
    fstream plik;
    int number,a,b;
    plik.open("gc_1000.txt", ios::in);
    if (!plik.good()) { cout << "cos sie wyjebalo" << endl; }
    plik >> number;
    Graph g(number);
    cout << "Wczytywanie..." << endl;
    while( plik >> a >> b)
    {
        

        
        g.addEdge(a-1, b-1);
    }
    plik.close();
    cout << "koniec wczytywania" << endl;
    g.greedyColoring();
    
    return 0;
}