#include <iostream>
#include <list>
#include <limits>

using namespace std;

class Node
{
public:
    int vertex;
    int range;
    bool visited = false;

    Node(int vertex, int range);
};

Node::Node(int vertex, int range)
{
    this->vertex = vertex;
    this->range = range;
    this->visited = false;
}

class Graph
{
    list<Node> *graph;

    int V;

public:
    Graph(int V); //construtor

    void addCity(int city1, int city2, int range);
    int findTheLessRange(list<int> ranges);
    bool canTravel(int src, int range, int gas);
    bool verityTheTravel();
    void seeVisited();

    void print();
};

Graph::Graph(int V)
{
    this->V = V;
    graph = new list<Node>[V];
}

void Graph::addCity(int city1, int city2, int range)
{
    this->graph[city1].push_back(Node(city2, range));
}

int Graph::findTheLessRange(list<int> ranges)
{
    int lessRange = INT_MAX;

    bool travelIsPossible;

    list<int>::iterator it;

    for (it = ranges.begin(); it != ranges.end(); it++)
    {
        for (int src = 0; src < V; src++)
        {
            canTravel(src, *it, 0);
            seeVisited();
            travelIsPossible = this->verityTheTravel();
            seeVisited();

            cout << "range: " << *it << "travel is possible ? : " << travelIsPossible << endl;

            if (travelIsPossible && *it < lessRange)
            {
                lessRange = *it;
            }
        }
    }

    return lessRange;
}

bool Graph::verityTheTravel()
{
    bool travelIsPossible = true;

    list<Node>::iterator it;

    for (int i = 0; i < V; i++)
    {
        for (it = graph[i].begin(); it != graph[i].end(); it++)
        {
            if (it->visited == false)
                travelIsPossible = false;

            it->visited = false;
        }
    }

    return travelIsPossible;
}

void Graph::seeVisited()
{
    cout << "SEE VISITED: " << endl;

    list<Node>::iterator it;

    for (int i = 0; i < V; i++)
    {
        cout << "i: " << i << "-> ";

        for (it = graph[i].begin(); it != graph[i].end(); it++)
        {
            cout << it->visited << " ";
        }

        cout << endl;
    }
}

bool Graph::canTravel(int src, int range, int gas)
{
    cout << "src: " << src << endl;
    cout << "range: " << range << endl;

    list<Node>::iterator it;

    for (it = graph[src].begin(); it != graph[src].end(); it++)
    {
        cout << "Node: " << endl
             << "vertex: " << it->vertex << endl
             << "range: " << it->range << endl
             << "visited: " << it->visited << endl
             << endl;
        gas += range; //abastece
        if (!it->visited && gas >= it->range)
        {
            gas -= it->range;
            it->visited = true;

            canTravel(it->vertex, range, gas);
        }
    }
    cout << endl;
    /*for (int i = 0; canTravel && i < V; i++)
    {
        for (it = graph[i].begin(); it != graph[i].end(); it++)
        {
            if (it->range < range)
                canTravel = false;

            range += range;
        }
    }
    cout << "range: " << range << " canTravel? " << canTravel;*/

    return true;
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
            cout << "|" << it->vertex << "|" << it->range << "|"
                 << "->";
        }

        cout << endl;
    }
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

            graph.addCity(city1, city2, range);
            ranges.push_back(range);
        }

        graph.print();
        cout << "lessRange: " << graph.findTheLessRange(ranges) << endl;

        cin >> cities;
        cin >> roads;
    } while (cities != 0 && roads != 0);
}