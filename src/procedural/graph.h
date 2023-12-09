#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <set>
#include <unordered_map>

template <class T>
class Graph {
public:
    // Constructor
    Graph() {}

    // Add a node to the graph
    void addNode(int nodeId, T* val);

    // Add an edge to the graph
    void addEdge(int node1, int node2);

    // Gets the neighbor Ids of a node in the graph.
    const std::set<int>& getNeighbors(int nodeId) const;
    const T& getVal(int nodeId) const;

    // Prints the connections in a graph.
    void printGraph() const;
private:
    std::unordered_map<int, std::set<int>> m_nodes;
    std::unordered_map<int, T*> m_vals;
};


#endif // GRAPH_H
