#include <iostream>
#include <list>
#include <limits>

using namespace std;

class Node
{
public:
    int vertex, weight;

    Node(int vertex, int weight);
};

Node::Node(int vertex, int weight)
{
    this->vertex = vertex;
    this->weight = weight;
}

class Cycle
{
public:
    list<Node> vertexs;

    Cycle();

    void addVertex(Node vertex);
    int getCycleSize();
};

Cycle::Cycle()
{
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

void printCycle(list<Node> cycle)
{
    cout << "PRINT CYCLE";

    list<Node>::iterator it;

    for (it = cycle.begin(); it != cycle.end(); it++)
    {
        cout << it->weight;
    }
    cout << endl;
}

class Graph
{
public:
    list<Node> *graph;
    list<Cycle *> cycles;

    int V;
    int smallestCycle;

    Graph(int numberOfVertex);

    void createLigation(int x, int y, int weight);
    int findShortestCycle(int src);
    void addCycle(Cycle *cycle);

    void print();

private:
    int findCycle(int src, bool *visited, int parent, Cycle *cycle);
};

Graph::Graph(int numberOfVertex)
{
    this->V = numberOfVertex;
    this->graph = new list<Node>[numberOfVertex];
    this->smallestCycle = INT_MAX;
}

void Graph::addCycle(Cycle *cycle)
{
    cycles.push_back(cycle);
}

void Graph::print()
{
    cout << "GRAPH: " << endl;

    list<Node>::iterator it;

    for (int i = 0; i < V; i++)
    {
        cout << "i: " << i << "-> ";

        for (it = graph[i].begin(); it != graph[i].end(); it++)
        {
            cout << "|" << it->vertex << "|" << it->weight << "|"
                 << "->";
        }

        cout << endl;
    }
}

void Graph::createLigation(int x, int y, int weight)
{
    //x -= 1;
    //y -= 1;
    this->graph[x].push_back(Node(y, weight));
    this->graph[y].push_back(Node(x, weight));
}

int Graph::findShortestCycle(int src)
{
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
    {
        visited[i] = false;
    }
    Cycle *cycle = new Cycle();
    return findCycle(src, visited, -1, cycle);
}

int Graph::findCycle(int src, bool *visited, int parent, Cycle *cycle)
{
    visited[src] = true;

    list<Node>::iterator it;
    for (it = graph[src].begin(); it != graph[src].end(); it++)
    {
        //0 -> 1, 2, 3
        if (!visited[it->vertex])
        {
            cout << "weight: " << it->weight;
            //sizeOfCycle += it->weight;
            cycle->addVertex(*it);
            int foundCycle = findCycle(it->vertex, visited, src, cycle);

            if (foundCycle == 0)
            {
                printCycle(cycle->vertexs);
                //sizeOfCycle = 0;
                cout << "ops " << endl;
                cout << "TAMANHO DESSA DISGRETA " << cycle->getCycleSize();
                //cout << "sizeOfCycle: " << sizeOfCycle << endl;
            }
            cycle = new Cycle();
        }
        else if (it->vertex != parent)
        {
            //cycle found
            //verify if this cicle is bigger
            //sizeOfCycle += it->weight;
            cycle->addVertex(*it);
            printCycle(cycle->vertexs);
            cout << "WEIGHT: " << it->weight;
            cout << "cycle found: " << it->vertex << endl;
            //cout << "size: " << sizeOfCycle << endl;
            this->cycles.push_back(cycle);

            return 0;
        }
    }

    return -1;
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
        graph.print();
        graph.findShortestCycle(0);
    }
}