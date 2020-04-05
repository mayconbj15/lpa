#include <iostream>
#include <list>
#include <limits>

using namespace std;

class Graph
{
public:
    int V;

    int **graph;

    int *dist;

    int *parent;

    list<int> ranges;

    Graph(int V);

    void print();

    void inicializaGrafo();

    void createLigation(int a, int b, int c);

    /** Diijskra **/
    int minDistance(int dist[], bool sptSet[]);

    int printSolution(int dist[]);

    int printParent(int parent[]);

    int dijkstra(int src);
};

Graph::Graph(int V)
{
    this->V = V;

    inicializaGrafo();
}

void Graph::inicializaGrafo()
{
    graph = new int *[V];

    for (int i = 0; i < this->V; i++)
    {
        graph[i] = new int[V];
        for (int j = 0; j < this->V; j++)
        {
            this->graph[i][j] = 0;
        }
    }
}

void Graph::print()
{
    cout << "GRAPH " << endl;

    for (int i = 0; i < this->V; i++)
    {
        for (int j = 0; j < this->V; j++)
        {
            cout << this->graph[i][j] << " ";
        }
        cout << "\n";
    }
}

void Graph::createLigation(int a, int b, int c)
{
    this->graph[a][b] = c;
}

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int Graph::minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// A utility function to print the constructed distance array
int Graph::printSolution(int dist[])
{
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < V; i++)
    {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

int Graph::printParent(int parent[])
{
    for (int i = 0; i < V; i++)
    {
        printf("Parent: %d \t\t %d\n", i, parent[i]);
    }
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
int Graph::dijkstra(int src)
{
    int *parent = new int[V];

    int *dist = new int[V];

    bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX, parent[i] = -1, sptSet[i] = false;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)

            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
    }

    this->dist = dist;
    this->parent = parent;

    printSolution(dist);
    printParent(parent);
}

int main()
{
    int cities, roads;
    int city1, city2, range;

    cin >> cities;
    cin >> roads;

    do
    {
        Graph graph(cities);
        list<int> ranges;

        for (int i = 0; i < roads; i++)
        {
            cin >> city1;
            cin >> city2;
            cin >> range;

            graph.createLigation(city1, city2, range);
            ranges.push_back(range);
        }

        graph.ranges = ranges;

        for (int i = 0; i < graph.V; i++)
        {
            cout << "V = " << i << endl;
            graph.dijkstra(i);
        }

        cin >> cities;
        cin >> roads;
    } while (cities != 0 && roads != 0);
}