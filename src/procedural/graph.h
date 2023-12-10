#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <set>
#include <unordered_map>
#include <map>
#include <utility>

#include "scene/sceneobject.h"

template <typename T>
class Graph {
public:
    // Constructor
    Graph() {}

    // Add a node to the graph
    void addNode(int nodeId, T* val);

    // Add an edge to the graph. edgeVal represents a type.
    void addEdge(int node1, int node2, int edgeVal);

    // Add an edge to the graph without a value. Value defaults to -1
    void addEdge(int node1, int node2);

    // Gets the neighbor Ids of a node in the graph.
    const std::set<int>& getNeighbors(int nodeId) const;
    T* getVal(int nodeId);

    // Prints the connections in a graph.
    void printGraph();

    // Gets the value of an edge.
    int getValFromEdge(int edge1, int edge2);

    // Gets all edges with a value.
    std::set<std::pair<int, int>>* getEdgesFromVal(int val);
private:
    std::unordered_map<int, std::set<int>> m_nodes;
    // Stores a map from edge to edgeVal
    std::map<std::pair<int, int>, int> m_edgeV;

    // Stores a map from edgeVal to edge (Used when edgeVal represents a type)
    std::unordered_map<int, std::set<std::pair<int, int>>> m_Vedge;

    std::unordered_map<int, T*> m_vals;
};

#endif // GRAPH_H
