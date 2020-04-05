#include <iostream>
#include <stdlib.h>

#define INFINITY INT_MAX

using namespace std;

class Graph
{
public:
    int V;

    int **graph;

    int *dist;

    int *parent;

    Graph(int V);

    void initializeGraph();

    void createLigation(int a, int b, int c);

    // Functions for the Floyd's algorithm
    int floydWarshall();

    int **makeInputMatrix();

    int **makeOutputMatrix(int **inputMatrix);
};

Graph::Graph(int V)
{
    this->V = V;

    initializeGraph();
}

void Graph::initializeGraph()
{
    graph = new int *[V];

    for (int i = 0; i < V; i++)
    {
        graph[i] = new int[V];

        for (int j = 0; j < V; j++)
        {
            graph[i][j] = INFINITY;
        }
    }
}

void Graph::createLigation(int a, int b, int c)
{
    graph[a][b] = c;
}

void print(int **matrix, int V)
{
    cout << "GRAFO \n";

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

int **Graph::makeInputMatrix()
{
    //int **inputMatrix = new int[this->V][this->V];
    int **inputMatrix = new int *[V];

    for (int i = 0; i < V; i++)
    {
        inputMatrix[i] = new int[V];

        for (int j = 0; j < V; j++)
        {
            if (i == j)
                inputMatrix[i][j] = 0;
            else if (i != j && graph[i][j] != INFINITY)
                inputMatrix[i][j] = graph[i][j];
        }
    }

    return inputMatrix;
}

int **Graph::makeOutputMatrix(int **inputMatrix)
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            for (int k = 0; k < V; k++)
            {
                inputMatrix[j][k] = min(inputMatrix[j][k], (inputMatrix[j][i] + inputMatrix[i][k]));
            }
        }
    }

    return inputMatrix;
}

int **Graph::floydWarshall()
{
    cout << "inputMatrix" << endl;
    int **inputMatrix = makeInputMatrix();
    print(inputMatrix, V);

    int **outputMatrix = makeOutputMatrix(inputMatrix);

    cout << "outputMatrix" << endl;
    print(outputMatrix, V);

    return -1;
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

        for (int i = 0; i < roads; i++)
        {
            cin >> city1;
            cin >> city2;
            cin >> range;

            graph.createLigation(city1, city2, range);
        }

        print(graph.graph, graph.V);

        graph.floydWarshall();

        cin >> cities;
        cin >> roads;
    } while (cities != 0 && roads != 0);
}