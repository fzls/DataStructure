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
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <list>
#include <queue>
#include <HashTable.h>


using namespace std;

struct Node {
	int elem;
	int in_degree;
	list<int> adjacents;

	Node(int e = -1, int d = 0): elem{e}, in_degree{d} , adjacents() {}
	bool operator<(const Node & rhs) const {
		return in_degree > rhs.in_degree || (in_degree == rhs.in_degree && elem > rhs.elem);
	}
};

class priorityQueue : public priority_queue<Node>
{
public:
	Node pop() {
		Node temp = priority_queue<Node>::top();
		priority_queue<Node>::pop();
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
			if (array[i].elem != -1 && array[i].elem % tableSize != i) {
				array[i].in_degree = (i - array[i].elem) % tableSize;
				if (array[i].in_degree < 0)
					array[i].in_degree += tableSize;
				for (int count = 0; count < array[i].in_degree; ++count) {
					int j = i - count - 1;
					if (j < 0)
						j += tableSize;
					array[j].adjacents.push_back(i);
				}
				// for(int j=(i==0?tableSize-1:i-1);j>)
				// int j = i;
				// do {
				// 	j = (j == 0 ? tableSize - 1 : j - 1);
				// 	++array[i].in_degree;
				// 	array[j].adjacents.push_back(i);
				// } while (j>=array[i].elem % tableSize);
			}
	}
	~Graph() {}
	void topOutput();
};

void Graph::topOutput() {
	priorityQueue vertexsWithZeroIndegree;
	int currentSize = 0;
	for (int i = 0; i < tableSize; ++i)
		if (array[i].elem != -1)
			++currentSize;
	for (int i = 0; i < tableSize; ++i)
		if (array[i].in_degree == 0 && array[i].elem != -1)
			vertexsWithZeroIndegree.push(array[i]);
	while (!vertexsWithZeroIndegree.empty()) {
		Node temp = vertexsWithZeroIndegree.pop();
		cout << temp.elem << (--currentSize > 0 ? " " : "");
		for (int k : temp.adjacents)
			if (--array[k].in_degree == 0)
				vertexsWithZeroIndegree.push(array[k]);
	}
}

int main() {
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
	int tableSize;
	cin >> tableSize;
	Graph graph(tableSize);
	graph.topOutput();

	cout << endl;
	// system("pause");
	return 0;
}
