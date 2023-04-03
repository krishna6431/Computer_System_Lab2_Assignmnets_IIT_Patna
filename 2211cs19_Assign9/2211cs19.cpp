/**
 * @file 2211cs19.cpp
 * @author Krishna Kant Verma
 * @brief Assignmnet 9 IIT Patna System Lab 2
 * @rollNo 2211cs11
 * @version 0.1
 * @date 27-03-2023
 */

/// @brief  important header file
#include <iostream>
using namespace std;

/// @brief created linked list data structure contains nodeVal and Pointer to next
class LinkedList
{
public:
	int nodeVal;
	LinkedList *nextPtr;

	/// @brief LinkedList Constructor to create object
	/// @param nodeVal
	LinkedList(int nodeVal)
	{
		this->nodeVal = nodeVal;
		this->nextPtr = nullptr;
	}
};

/**
 * @brief created queue data structure contains frontPtr and rearPtr
 * @details frontPtr = points to front of the queue and rearPtr = points to rear of the queue where push operation takes place
 */
class queue
{
public:
	LinkedList *frontPtr;
	LinkedList *rearPtr;

	/// @brief queue constructor to init pointers
	queue()
	{
		this->frontPtr = nullptr;
		this->rearPtr = nullptr;
	}
	/// @brief checks if queue is empty or not
	/// @return true if queue is empty otherwise false
	bool isEmpty()
	{
		if (frontPtr == nullptr)
		{
			return true;
		}
		return false;
	}

	/// @brief to find front of the queue
	/// @return front Node of the queue
	LinkedList *queueFront()
	{
		if (isEmpty())
		{
			return nullptr;
		}
		return frontPtr;
	}

	/// @brief for pushing the element into queue
	/// @param nodeVal
	void queuePush(int nodeVal)
	{
		if (isEmpty())
		{
			rearPtr = new LinkedList(nodeVal);
			frontPtr = rearPtr;
		}
		else
		{
			LinkedList *newNode = new LinkedList(nodeVal);
			rearPtr->nextPtr = newNode;
		}
	}
	/// @brief function to pop out element from the queue
	void queuePop()
	{
		/// checking empty condn
		if (isEmpty())
		{
			cout << "Queue is Already Empty" << endl;
			return;
		}
		/// incrementing frontPtr
		frontPtr = frontPtr->nextPtr;
	}
};

/// @brief creating adjacency list data structre
class adjacencyList
{
public:
	/// head ptr(contains adjacency of each node) and rearptr(for tracking last element)
	LinkedList *adjacentHeadPtr;
	LinkedList *rearPtr;
	// adjacency list constructor
	adjacencyList()
	{
		this->adjacentHeadPtr = nullptr;
		this->rearPtr = nullptr;
	}
};

/// @brief function to compute the shortest path for any pair of node
/// @param sourceNode
/// @param graph
/// @param visited
/// @param pathLen
void shortestPath(int sourceNode, adjacencyList graph[], bool visited[], int pathLen[])
{
	// initinalizing queue data structure
	queue qds;
	// pushing source node to queue
	qds.queuePush(sourceNode);
	// marking it visited
	visited[sourceNode] = true;
	pathLen[sourceNode] = 0;
	// do bfs till q data structure become empty
	while (!qds.isEmpty())
	{
		// storing current node
		LinkedList *itr = qds.queueFront();
		// storing distance of current node
		int dist = pathLen[itr->nodeVal];
		// popping out it from queue
		qds.queuePop();
		LinkedList *adj = graph[itr->nodeVal].adjacentHeadPtr;
		// iterating over adjcent node of current node
		while (adj != nullptr)
		{
			// if not visited adjacent node
			if (!visited[adj->nodeVal])
			{
				// update path and put it into queue
				pathLen[adj->nodeVal] = dist + 1;
				visited[adj->nodeVal] = true;
				qds.queuePush(adj->nodeVal);
				adj = adj->nextPtr;
			}
			else
			{
				// increment
				adj = adj->nextPtr;
			}
		}
	}
	return;
}

/// @brief main function starts here
/// @return
int main()
{
	// taking input no of nodes
	int noOfNodes;
	cout << "Enter Number of Nodes in Graph: ";
	cin >> noOfNodes;
	// taking input node of edges in graph
	cout << "\nEnter Number of Edges in the Graph: ";
	int noOfEdges;
	cin >> noOfEdges;
	// creating adjacency list of the graph
	adjacencyList graph[noOfNodes];
	for (int i = 0; i < noOfEdges; i++)
	{
		// taking input each edges in the graph
		int u, v;
		cout << "\nEnter " << i + 1 << " Edge: ";
		cin >> u >> v;
		// assinging the edges (in both direction)
		// forward connection
		LinkedList *addEdgeForward = new LinkedList(v);
		if (graph[u].adjacentHeadPtr == nullptr)
		{
			graph[u].adjacentHeadPtr = addEdgeForward;
			graph[u].rearPtr = addEdgeForward;
		}
		else
		{
			graph[u].rearPtr->nextPtr = addEdgeForward;
			graph[u].rearPtr = addEdgeForward;
		}
		// backward connection
		LinkedList *addEdgeBackward = new LinkedList(u);
		if (graph[v].adjacentHeadPtr == nullptr)
		{
			graph[v].adjacentHeadPtr = addEdgeBackward;
			graph[v].rearPtr = addEdgeBackward;
		}
		else
		{
			graph[v].rearPtr->nextPtr = addEdgeBackward;
			graph[v].rearPtr = addEdgeBackward;
		}
	}
	// taking input no of prom nodes
	cout << "\nEnter Number of Promiscuous Nodes:" << endl;
	int noOfPromNodes;
	cin >> noOfPromNodes;
	int promArr[noOfPromNodes];
	for (int itr = 0; itr < noOfPromNodes; itr++)
	{
		cin >> promArr[itr];
	}

	for (int i = 0; i < noOfPromNodes; i++)
	{
		cout << promArr[i] << " ";
	}
	cout << endl;

	// grapgh constructed successfully
	cout << "The Constructed Graph" << endl;
	for (int i = 0; i < noOfNodes; i++)
	{
		cout << i << " -> ";
		LinkedList *itr = graph[i].adjacentHeadPtr;
		if (itr == NULL)
		{
			cout << endl;
		}
		while (itr != nullptr)
		{
			if (itr->nextPtr == nullptr)
			{
				cout << itr->nodeVal << endl;
			}
			else
			{
				cout << itr->nodeVal << ", ";
			}
			itr = itr->nextPtr;
		}
	}
	// if edges is 0;
	if (noOfEdges == 0)
	{
		cout << "Nodes Are Not Connected (INF Distance)" << endl;
		return 0;
	}
	int spLen = 1e9, spSrc = -1, spDest = -1;
	// doing bfs and computing the answers
	for (int i = 0; i < noOfPromNodes - 1; i++)
	{
		// visited array
		bool visited[noOfNodes];
		// pathlength array
		int pathLen[noOfNodes];
		for (int k = 0; k < noOfNodes; k++)
		{
			pathLen[k] = 1e9;
		}
		// do bfs once for prom[i]th node
		shortestPath(promArr[i], graph, visited, pathLen);
		// update the rest path which pairs with prom[i]th
		for (int j = i + 1; j < noOfPromNodes; j++)
		{

			if (spLen > pathLen[promArr[j]])
			{
				spLen = pathLen[promArr[j]];
				spSrc = promArr[i];
				spDest = promArr[j];
			}
		}
	}
	// if graph not connect
	if (spLen == 1e9)
	{
		cout << "Promiscuous Nodes are Not Connected(INF Distance)" << endl;
		return 0;
	}
	cout << "Minimum shortest distance between two Promiscuous nodes (" << spSrc << "->" << spDest << ") is " << spLen << "." << endl;
	return 0;
}

/// Time Complexity
// O(P*(V+E))
// (V+E) for BFS
// we are doing bfs no of proms time so over all complexity
// O(p*(V+E))