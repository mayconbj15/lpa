// C++ program to print connected components in 
// an undirected graph 
#include<iostream> 
#include <list> 
using namespace std; 
  
// Graph class represents a undirected graph 
// using adjacency list representation 
class Graph 
{ 
    int V;    // No. of vertices 
  
    // Pointer to an array containing adjacency lists 
    list<int> *adj; 
  
    // A function used by DFS 
    void DFSUtil(int v, bool visited[]); 

public: 
    Graph(int V);   // Constructor 
    
    void addEdge(int v, int w); 
    int connectedComponents(); 

    void createLigation(string ligation);
    void showTheConnectedComponents(Graph g, int numberCase);
    void printGraph();
}; 
  
// Method to print connected components in an 
// undirected graph and return the numbers of 
// components connecteds
int Graph::connectedComponents() 
{ 
    // Mark all the vertices as not visited 
    bool *visited = new bool[V]; 
    for(int v = 0; v < V; v++) 
        visited[v] = false; 
    
    int connectedComponents = 0;

    for (int v=0; v<V; v++) 
    { 
        if (visited[v] == false) 
        { 
            // print all reachable vertices 
            // from v 
            DFSUtil(v, visited); 
  
            cout << "\n"; 
            connectedComponents++;
        } 
    } 

    return connectedComponents;
} 
  
void Graph::DFSUtil(int v, bool visited[]) 
{ 
    // Mark the current node as visited and print it 
    visited[v] = true; 
    cout << v << ","; 
  
    // Recur for all the vertices 
    // adjacent to this vertex 
    list<int>::iterator i;

    for(i = adj[v].begin(); i != adj[v].end(); i++) 
        if(!visited[*i]) 
            DFSUtil(*i, visited); 
} 
  
Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new list<int>(V); 
} 
  

//method to add an undirected edge
void Graph::addEdge(int v, int w) 
{ 
    adj[v-1].push_back(w-1); // Add w to v’s list. 
    adj[w-1].push_back(v-1); // Add w to v’s list. 
} 

void Graph::showTheConnectedComponents(Graph g, int numberCase){
    cout << "Case #" << numberCase << ":\n";

    int connectedCompents = g.connectedComponents();

    cout << connectedCompents << " connected components\n\n";
}

void Graph::printGraph(){
    list<int>::iterator iti;
    
    for(int i=0; i < this->V; i++){
        for(iti = adj[i].begin(); iti != adj[i].end(); iti++){
            cout << "TA PORRA: ";
            cout << *iti << " ";
        }
    }
    
    cout << endl;
} 

    

  
// Drive program to test above 
int main() 
{ 
    int quantTest;
    int vertex;
    int edges;

    int friend1;
    int friend2;
    
    cin >> quantTest; //receive the cases of test
    

    for(int i=0; i < quantTest; i++){
        cin >> edges; 
        cin >> vertex; 

        //buffer to clear the '\n' character of the input above
        string buffer;
        getline(cin, buffer);
        
        Graph g(vertex);
        
        for(int j=0; j<edges; j++){
            cin >> friend1;
            cin >> friend2;

            cout << "friend1 " << friend1;
            cout << "friend2 " << friend2;
        
            g.addEdge(friend1, friend2);
        }
        g.printGraph();
        // g.showTheConnectedComponents(g, i+1);
        

    }

    return 0; 
}