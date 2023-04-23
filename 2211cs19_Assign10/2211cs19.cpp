/// @author Krishna Kant Verma
/// @brief Program to Find Maximum Strongly Connected Component in Directed Graph
// Assignment 10

/// @headerfile 
#include<bits/stdc++.h>
 /// @brief using namespace as standard
using namespace std;

/**
 * @brief Class to Create Linked List Node
 * @details It has 2 member data
 * nodeVal : nodeVal
 * nextPtr : Pointer to next Node
 */

class LinkedList {
    public: int nodeVal;
    LinkedList * nextPtr;

    /// @brief Constructor to Initialize value
    /// @param nodeVal
    LinkedList(int nodeVal) {
        this -> nodeVal = nodeVal;
        this -> nextPtr = nullptr;
    }
};

/**
 * @brief Class to Create adjacnecy List
 * @details It has 2 member data
 * headPtr : tracking headPtr 
 * rearPtr : tracking rearPtr to add node at last in O(1) time
 */
class adjacencyList {
    public: LinkedList * headPtr;
    LinkedList * rearPtr;
    //Constructor to initialize values
    adjacencyList() {
        this -> headPtr = nullptr;
        this -> rearPtr = nullptr;
    }
};

// @brief function to traverse the graph in depth first manner
/**
	@param node : node : current node on which dfs call 
	              graph: adjacency list
	              visited : visited array
	              ans : to Store current ans
	              k : store current ans at index k
	              currSize : total no of nodes in current component
	@return void
*/
void dfs(int node, adjacencyList * graph, bool visited[], adjacencyList * ans, int & k, int & currSize) {
    //marking current node as visited
    visited[node] = true;
    
    //Storing the Current Node
    LinkedList * newNode = new LinkedList(node);
    if (ans[k].headPtr == nullptr) {
        ans[k].headPtr = newNode;
        ans[k].rearPtr = ans[k].headPtr;
    } else {
        ans[k].rearPtr -> nextPtr = newNode;
        ans[k].rearPtr = newNode;
    }
    currSize++;
    LinkedList * itr = graph[node].headPtr;
    
    //iterating over the neighbours of the current node
    while (itr != nullptr) {
        //if neighbour is not visited recur on that node
        if (!visited[itr -> nodeVal]) {
            dfs(itr -> nodeVal, graph, visited, ans, k, currSize);
        }
        //increment the pointer
        itr = itr -> nextPtr;
    }
}
/// @brief function to traverse the graph in depth first manner and store it in order of their finish time
/**
	@param node : node : current node on which dfsStoreFinishOrder call 
	              graph: adjacency list
	              visited : visited array
	              finishArr : array that store nodes in order of their finish time
	              top : topMost index in finish arr
	              n : no of Vertices
	@return void
*/
void dfsStoreFinishOrder(int node, adjacencyList * graph, bool visited[], int * finishArr, int & top, int n) {
    visited[node] = true;
    LinkedList * itr = graph[node].headPtr;
    
     //iterating over the neighbours of the current node
    while (itr != nullptr) {
        if (!visited[itr -> nodeVal]) {
            dfsStoreFinishOrder(itr -> nodeVal, graph, visited, finishArr, top, n);
        }
        itr = itr -> nextPtr;
    }
    
    top = top + 1;
    finishArr[top] = node;
}

/// @brief function to print total number of strongly connected component and maxlen strongly connected components
/**
	@param node : n : no of vertices
	              graph: adjacency list of given graph
	              reverseGraph : adjacency list of reverse graph
	              noOfStrongCmp : number of strongly connected component           
	@return void
*/
void stronglyConnectedComponent(int n, adjacencyList * graph, adjacencyList * reverseGraph, int & noOfStrongCmp) {
    /// finish array to store vertice in order of their finish time
    int finishArr[n];
    //top pointer to track LIFO order
    int top = -1;

    //visited array
    bool * visited = new bool[n + 1];
    for (int i = 1; i <= n; i++)
        visited[i] = false;

    //computing finish order of nodes
    for (int i = 1; i <= n; i++)
        if (visited[i] == false)
            dfsStoreFinishOrder(i, graph, visited, finishArr, top, n);
    //after storing the finish order mark visited array false
    for (int i = 1; i <= n; i++)
        visited[i] = false;

    //crating ans array to store connected components
    adjacencyList ans[n + 1];
    int k = 0;

    //make dfs call on each node of finish array from last to begin in finish array
    while (top >= 0) {
        //getting top of finish array
        int v = finishArr[top];
        top = top - 1;
        if (visited[v] == false) {
            int currSize = 0;
            //dfs call on finish array top element
            dfs(v, reverseGraph, visited, ans, k, currSize);
            noOfStrongCmp = noOfStrongCmp + 1;
            LinkedList * size = new LinkedList(currSize);
            size -> nextPtr = ans[k].headPtr;
            ans[k].headPtr = size;
            k = k + 1;
        }

    }
    cout << "Number of Strongly Connected Component: " << noOfStrongCmp << endl;

    //finding maxlen of connected component
    int maxLen = -1e9;
    for (int i = 0; i < k; i++) {
        maxLen = max(maxLen, ans[i].headPtr -> nodeVal);
    }
    
    //printing all component having length equals to maxLen
    cout << "Printing Maximal Strongly Connected Component" << endl;
    int counter = 1;
    for (int i = 0; i < k; i++) {
        if (ans[i].headPtr -> nodeVal == maxLen) {
            cout << "Component " << counter << " : ";
            LinkedList * itr = ans[i].headPtr;
            if (itr != nullptr) itr = itr -> nextPtr;
            while (itr != nullptr) {
                cout << itr -> nodeVal << " ";
                itr = itr -> nextPtr;
            }
            cout << endl;
            counter++;
        }
    }
    if(counter == 1){
    	cout << "No Strongly Connected Component in Graph" << endl; 
    }
}

/// @brief main function starts here
int main(int argc, char ** argv) {

    //taking input and output from file and to file
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);

    //taking input no of vertice and edges
    int noOfVertices, noOfEdges;
    cin >> noOfVertices >> noOfEdges;

    //creating graph list and reverseGraph list
    adjacencyList graph[noOfVertices + 1];
    adjacencyList reverseGraph[noOfVertices + 1];

    //taking input each edge
    for (int i = 0; i < noOfEdges; i++) {
        int u, v;
        cin >> u >> v;
        LinkedList * edge = new LinkedList(v);
        LinkedList * revEdge = new LinkedList(u);

        //constucting graph
        if (graph[u].headPtr == nullptr) {
            graph[u].headPtr = edge;
            graph[u].rearPtr = graph[u].headPtr;

        } else {
            graph[u].rearPtr -> nextPtr = edge;
            graph[u].rearPtr = edge;
        }

        // constrcuting reverse graph
        if (reverseGraph[v].headPtr == nullptr) {
            reverseGraph[v].headPtr = revEdge;
            reverseGraph[v].rearPtr = reverseGraph[v].headPtr;
        } else {
            reverseGraph[v].rearPtr -> nextPtr = revEdge;
            reverseGraph[v].rearPtr = revEdge;
        }

    }
    
    int noOfStrongCmp = 0;
    // calling stronglyConnectedComponent(..) function to get the answer
    stronglyConnectedComponent(noOfVertices, graph, reverseGraph, noOfStrongCmp);
    return 0;
}

/*
Time Complexity : O(N+M) where N = no of Vertices and M = no of edges
Space Complexity : O(N+M) adjacency list to store graph
*/
