/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 Hashtable_Hard_Version.cpp
* @version:
* @Time: 		 2015-12-17 17:25:57
* @Description:  Project3 Hashing - Hard Version   (40分)
*
+----------------------------------------------------------
*/
#include <iostream>
#include <functional>
#include <vector>
#include <list>
#include <queue>

using namespace std;

struct Node {
	int elem;
	int in_degree;
	list<int> adjacents;

	Node(int e = -1, int d = 0): elem{e}, in_degree{d} , adjacents() {}
	//reload < operator because we need to use it when we use the priority queue in the STL
	bool operator>(const Node & rhs) const {
		return in_degree > rhs.in_degree || (in_degree == rhs.in_degree && elem > rhs.elem);
	}
};

//because the default pop only remove the item, but won't return the value , so I override it
class priorityQueue : public priority_queue<Node, vector<Node>, greater<Node>>
{
public:
	Node pop() {
		Node temp = priority_queue<Node, vector<Node>, greater<Node>>::top();
		priority_queue<Node, vector<Node>, greater<Node>>::pop();
		return temp;
	}

};

class Graph
{
private:
	vector<Node> array;
	int tableSize;
public:
	Graph(int ts): array(ts), tableSize{ts} {
		//get vertex
		for (int i = 0; i < tableSize; ++i) {
			cin >> array[i].elem;
			array[i].in_degree = 0;
		}
		//make edges
		for (int i = 0; i < tableSize; ++i)
			//if the i th position of the hashTable has a item, and it is not on where it shold be(let's call this P)
			if (array[i].elem != -1 && array[i].elem % tableSize != i) {
				//then we calculate the in_degree as it's offset to P
				array[i].in_degree = (i + tableSize - array[i].elem % tableSize) % tableSize;
				//and for each node that is between this node and P, we add an edge form that node to this node
				for (int count = 0; count < array[i].in_degree; ++count) {
					int j = (i - count - 1 + tableSize) % tableSize;
					array[j].adjacents.push_back(i);
				}
			}
	}
	~Graph() {}
	void topOutput();
};
//output the vertexes in topsort with the help of min priority queue
void Graph::topOutput() {
	priorityQueue vertexsWithZeroIndegree;
	int currentSize = 0;
	//calculate the number of valid item in the hashtable for the convenice of output
	for (int i = 0; i < tableSize; ++i)
		if (array[i].elem != -1)
			++currentSize;
	//add the zero in-degree node into the priority queue
	for (int i = 0; i < tableSize; ++i)
		if (array[i].in_degree == 0 && array[i].elem != -1)
			vertexsWithZeroIndegree.push(array[i]);
	//remove one item from the priority queue, decress it's adjecents' in-degree by one, and add that adjecent into the queue if that adjacent's in-degree turn zero
	while (!vertexsWithZeroIndegree.empty()) {
		Node temp = vertexsWithZeroIndegree.pop();
		//don't print blank space at the end
		cout << temp.elem << (--currentSize > 0 ? " " : "");
		for (int k : temp.adjacents)
			if (--array[k].in_degree == 0)
				vertexsWithZeroIndegree.push(array[k]);
	}
}

int main() {
	//get the number of the input
	int tableSize;
	cin >> tableSize;
	//initialize the graph
	Graph graph(tableSize);
	//output with topsort
	graph.topOutput();

	return 0;
}
