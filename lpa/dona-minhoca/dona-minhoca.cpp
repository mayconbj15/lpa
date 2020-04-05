#include <iostream>
#include <list>
#include <limits>

using namespace std;

void printMatrix(int **matrix, int V);

#define INFINITY 1000000

class Node
{
public:
    int initial, end, weight;

    Node(int intial, int end, int weight);
};

Node::Node(int initial, int end, int weight)
{
    this->initial = initial;
    this->end = end;
    this->weight = weight;
}

class Cycle
{
public:
    list<Node> vertexs;
    int startOfCycle;
    int weightOfCycle;

    Cycle();

    void addVertex(Node vertex);
    int getCycleSize();
};

Cycle::Cycle()
{
    this->startOfCycle = -1;
    this->weightOfCycle = -1;
}

void Cycle::addVertex(Node vertex)
{
    vertexs.push_back(vertex);
}

int Cycle::getCycleSize()
{
    int size = 0;
    list<Node>::iterator it;

    for (it = vertexs.begin(); it != vertexs.end(); it++)
    {
        size += it->weight;
    }

    return size;
}

bool hasInCycle(Cycle cycle, int vertex);

void printCycle(list<Node> cycle)
{
    cout << "PRINT CYCLE " << endl;

    list<Node>::iterator it;

    for (it = cycle.begin(); it != cycle.end(); it++)
    {
        cout << it->initial << "|" << it->weight << "|" << it->end << "->";
    }
    cout << endl;
}

class Graph
{
public:
    int **graph;
    list<Cycle> cycles;
    bool *hasIsCycle;
    bool hasCycle;

    int V;
    int smallestCycle;

    Graph(int numberOfVertex);
    void initializeGraph();

    void createLigation(int x, int y, int weight);
    int findShortestCycle(int beginOfJourney, int weightOfWorm);
    void addCycle(Cycle cycle);
    Cycle findShortestCycle(int weightOfWorm);

    int **floydWarshall();
    int **makeInputMatrix();
    int **makeOutputMatrix(int **inputMatrix);
    void addInCycle(list<Node> vertexs);

    void print();

private:
    int findCycle(int src, bool *visited, int parent, Cycle cycle, int initialVertex);
};

Graph::Graph(int numberOfVertex)
{
    this->V = numberOfVertex;
    this->hasIsCycle = new bool[numberOfVertex];
    initializeGraph();
    this->smallestCycle = INFINITY;
    this->hasCycle = false;
}

void Graph::initializeGraph()
{
    graph = new int *[V];

    for (int i = 0; i < V; i++)
    {
        graph[i] = new int[V];

        for (int j = 0; j < V; j++)
        {
            graph[i][j] = 1500000;
        }
    }
}

void Graph::addCycle(Cycle cycle)
{
    cycles.push_back(cycle);
}

void Graph::print()
{
    cout << "GRAPH: " << endl;

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::createLigation(int x, int y, int weight)
{
    x -= 1;
    y -= 1;
    graph[x][y] = weight;
    graph[y][x] = weight;
}

void Graph::addInCycle(list<Node> vertexs)
{
    list<Node>::iterator it;
    for (it = vertexs.begin(); it != vertexs.end(); it++)
    {
        hasIsCycle[it->end] = true;
    }
}

bool *cleanVisited(bool *visited, int V)
{
    for (int i = 0; i < V; i++)
    {
        visited[i] = false;
    }

    return visited;
}

Cycle Graph::findShortestCycle(int weightOfWorm)
{
    int shortestWeight = 1500000;
    list<Cycle>::iterator it;
    Cycle cycle;

    int weight = 0;
    for (it = cycles.begin(); it != cycles.end(); it++)
    {
        weight = it->weightOfCycle;

        if (weight < shortestWeight && weight >= weightOfWorm)
        {
            cycle = *it;
            shortestWeight = weight;

            cycle.weightOfCycle = shortestWeight;
            cycle.startOfCycle = it->startOfCycle;
        }
    }

    return cycle;
}

int Graph::findShortestCycle(int beginOfJourney, int weightOfWorm)
{
    bool *visited = new bool[V];

    for (int i = 0; i < V; i++)
    {
        visited = cleanVisited(visited, V);
        findCycle(i, visited, -1, Cycle(), i);
    }

    if (!this->hasCycle)
        cout << "-1" << endl;
    else
    {
        Cycle shortestCycle = findShortestCycle(weightOfWorm);
        if (shortestCycle.weightOfCycle != -1)
        {
            int **outputMatrix = floydWarshall();

            int startOfCycle = shortestCycle.startOfCycle;

            int distance = shortestCycle.weightOfCycle;
            if (!hasInCycle(shortestCycle, beginOfJourney))
            {

                distance += outputMatrix[beginOfJourney][startOfCycle] + outputMatrix[startOfCycle][beginOfJourney];
            }

            cout << "" << distance << endl;
        }
        else
        {
            cout << "-1" << endl;
        }
    }
}

bool hasInCycle(Cycle cycle, int vertex)
{
    bool exists = false;

    list<Node>::iterator it;
    for (it = cycle.vertexs.begin(); it != cycle.vertexs.end() && !exists; it++)
    {
        if (it->initial == vertex)
            exists = true;
    }
    return exists;
}

void printMatrix(int **matrix, int V)
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int Graph::findCycle(int src, bool *visited, int parent, Cycle cycle, int initialVertex)
{
    visited[src] = true;

    for (int j = 0; j < V; j++)
    {
        if (graph[src][j] != 1500000) //have edge
        {
            if (!visited[j] && !hasIsCycle[j])
            {

                cycle.addVertex(Node(src, j, graph[src][j]));

                int foundCycle = findCycle(j, visited, src, cycle, initialVertex);
                cycle = Cycle();
            }
            else if (j != parent && j == initialVertex)
            {
                this->hasCycle = true;

                cycle.addVertex(Node(src, j, graph[src][j]));

                cycle.weightOfCycle = cycle.getCycleSize();

                addInCycle(cycle.vertexs);

                cycle.startOfCycle = j;
                this->cycles.push_back(cycle);

                return 0;
            }
        }
    }

    return -1;
}

int **Graph::makeInputMatrix()
{
    int **inputMatrix = new int *[V];

    for (int i = 0; i < V; i++)
    {
        inputMatrix[i] = new int[V];

        for (int j = 0; j < V; j++)
        {
            if (i == j)
                inputMatrix[i][j] = 0;
            else if (graph[i][j] != 1500000)
                inputMatrix[i][j] = graph[i][j];
            else
            {
                inputMatrix[i][j] = INFINITY;
            }
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
    int **inputMatrix = makeInputMatrix();

    int **outputMatrix = makeOutputMatrix(inputMatrix);

    return outputMatrix;
}

int main()
{
    int sallons, tunnels;
    int initialSallon, finalSallon, weightOfTunnel;
    int attempts;
    int beginOfJourney, weightOfWorm;

    while (scanf("%d%d", &sallons, &tunnels) != EOF)
    {
        Graph graph(sallons);
        for (int i = 0; i < tunnels; i++)
        {
            cin >> initialSallon;
            cin >> finalSallon;
            cin >> weightOfTunnel;

            graph.createLigation(initialSallon, finalSallon, weightOfTunnel);
        }

        cin >> attempts;

        for (int j = 0; j < attempts; j++)
        {
            cin >> beginOfJourney;
            cin >> weightOfWorm;

            graph.findShortestCycle(beginOfJourney - 1, weightOfWorm);
        }
    }
}