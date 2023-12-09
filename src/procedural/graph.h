#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <set>

class Graph {
public:
    // Constructor
    Graph() {}

    // Add a node to the graph
    void addNode(int nodeId) {
        if (nodes.find(nodeId) == nodes.end()) {
            nodes[nodeId] = std::set<int>();
        }
    }

    // Add an undirected edge between two nodes
    void addEdge(int node1, int node2) {
        addNode(node1);
        addNode(node2);

        nodes[node1].insert(node2);
        nodes[node2].insert(node1);
    }

    // Get neighbors of a node
    const std::set<int>& getNeighbors(int nodeId) const {
        static const std::set<int> emptySet;
        auto it = nodes.find(nodeId);
        return (it != nodes.end()) ? it->second : emptySet;
    }

    // Print the graph
    void printGraph() const {
        for (const auto& entry : nodes) {
            std::cout << "Node " << entry.first << " is connected to: ";
            for (int neighbor : entry.second) {
                std::cout << neighbor << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    std::unordered_map<int, std::set<int>> nodes;
};


#endif // GRAPH_H
