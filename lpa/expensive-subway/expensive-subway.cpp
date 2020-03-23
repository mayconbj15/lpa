#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

using namespace std;

class Edge
{
public:
    int initial, end, weight;
    Edge(int initial, int end, int weight);
};

Edge::Edge(int initial, int end, int weight)
{
    this->initial = initial;
    this->end = end;
    this->weight = weight;
}

class Graph
{
public:
    int V;

    int **graph;

    vector<Edge> egdes;

    Graph(int V);

    void print();

    void initializeGraph();

    void createLigation(vector<string> cities, string input);

    void kruskal();
};

// Definition of classes
Graph::Graph(int V)
{
    this->V = V;

    initializeGraph();
}

// A set of utility functions
int indexOf(string name, vector<string> listOfCities);
string toLowerCase(string input);
void flush();
vector<string> trim(string input);
bool lessWeight(Edge edge1, Edge edge2);

/**
 * Function to find the index of a name city in a vector of string
 * 
 * @param name the name of city to search
 * @param listOfCities a list with the name of the cities
 * 
 * @return the index of the given name of city or -1 if the name not exists in vector
 */
int indexOf(string name, vector<string> listOfCities)
{
    bool find = false;
    int indexOf = -1;

    string city;

    if (!listOfCities.empty())
    {
        for (int i = 0; i < listOfCities.size() && find == false; i++)
        {
            city = toLowerCase(listOfCities.at(i));
            //cout << "CITY: " << city << endl;
            if (city.compare(toLowerCase(name)) == 0)
            {
                find = true;
                indexOf = i;
            }
        }
    }

    return indexOf;
}

/**
 * Function to parse a string in lower case
 * 
 * @param input the string to be parsed
 * 
 * @return a parsed string
 */
string toLowerCase(string input)
{
    string newString = "";

    for (int i = 0; i < input.size(); i++)
    {
        newString += tolower(input.at(i));
    }

    return newString;
}

/**
 * A functin to flush the input buffer
 */
void flush()
{
    int ch;
    while ((ch = fgetc(stdin)) != EOF && ch != '\n')
    {
    }
}

/**
 * A function to find the less weight between two edges
 * 
 * @param edge1 the edge to be compared
 * @param edge2 the edge to be compared
 * 
 * @return true if the edge1 is less than edge2
 */
bool lessWeight(Edge edge1, Edge edge2)
{
    return edge1.weight < edge2.weight;
}

/**
 * A function to trim a input with space as separators
 * 
 * @param input the string to be trimmed
 * 
 * @return a vector with the strings trimmed
 */
vector<string> trim(string input)
{
    vector<string> values;

    string value = "";

    for (int i = 0; i < input.size(); i++)
    {
        if (input.at(i) != ' ')
            value += input.at(i);
        else
        {
            values.push_back(value);

            value = "";
        }
    }

    values.push_back(value);

    return values;
}

void Graph::initializeGraph()
{
    this->graph = (int **)malloc(this->V * sizeof(int *));

    for (int i = 0; i < this->V; i++)
    {
        this->graph[i] = (int *)malloc(this->V * sizeof(int));
        for (int j = 0; j < this->V; j++)
        {
            this->graph[i][j] = 0;
        }
    }
}

int find(int *arvore, int x)
{
    while (x != arvore[x])
        x = arvore[x];

    return x;
}

void Graph::kruskal()
{
    sort(this->egdes.begin(), this->egdes.end(), lessWeight);

    int sumOfWeights = 0;
    int vertices[this->V];
    int contadorDeArestas = this->V - 1;

    for (size_t x = 0; x < this->V; x++)
    {
        vertices[x] = x;
    }

    for (size_t x = 0; x < this->egdes.size(); x++)
    {
        int v1 = find(vertices, this->egdes[x].initial);
        int v2 = find(vertices, this->egdes[x].end);

        if (v1 != v2)
        {
            sumOfWeights += this->egdes[x].weight;
            vertices[v1] = v2;
            contadorDeArestas--;
        }
    }

    if (contadorDeArestas > 0)
        cout << "Impossible" << endl;
    else
        cout << sumOfWeights << endl;
}

void Graph::createLigation(vector<string> cities, string input)
{

    vector<string> values = trim(input);

    if (!values.empty())
    {
        int indexOfCity1 = indexOf(values.at(0), cities);

        int indexOfCity2 = indexOf(values.at(1), cities);

        int weight = stoi(values.at(2));

        this->graph[indexOfCity1][indexOfCity2] = weight;
        this->graph[indexOfCity2][indexOfCity1] = weight;

        Edge edge(indexOfCity1, indexOfCity2, weight);
        this->egdes.push_back(edge);
    }
}

void Graph::print()
{
    cout << "GRAFO \n";

    for (int i = 0; i < this->V; i++)
    {
        for (int j = 0; j < this->V; j++)
        {
            cout << this->graph[i][j] << " ";
        }
        cout << "\n";
    }
}

void printCities(vector<string> cities)
{
    for (int i = 0; i < cities.size(); i++)
    {
        cout << "city: " << cities.at(i) << endl;
    }
}

int main()
{
    int cities, connections, i;
    string cityName, input, initialCity;

    cin >> cities;
    cin >> connections;

    flush();

    do
    {
        Graph g(cities);

        vector<string> listOfCities;

        for (i = 0; i < cities; i++)
        {
            getline(cin, cityName);

            listOfCities.push_back(cityName);
        }

        for (int i = 0; i < connections; i++)
        {
            getline(cin, input);

            g.createLigation(listOfCities, input);
        }

        getline(cin, initialCity);

        g.kruskal();
        cin >> cities;
        cin >> connections;

        flush();

    } while (cities != 0 && connections != 0);
}