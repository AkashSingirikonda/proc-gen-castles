#include "graph.h"

template <class T>
void Graph<T>::addNode(int nodeId, T *val) {
    if (m_nodes.find(nodeId) == m_nodes.end()) {
        m_nodes[nodeId] = std::set<int>();
        m_vals[nodeId] = val;
    }
}

// Add an undirected edge between two nodes
template <class T>
void Graph<T>::addEdge(int node1, int node2) {
    addNode(node1);
    addNode(node2);

    m_nodes[node1].insert(node2);
    m_nodes[node2].insert(node1);
}

// Get neighbors of a node
template <class T>
const std::set<int>& Graph<T>::getNeighbors(int nodeId) const {
    static const std::set<int> emptySet;
    auto it = m_nodes.find(nodeId);
    return (it != m_nodes.end()) ? it->second : emptySet;
}

// Get value of a node
template <class T>
const T& Graph<T>::getVal(int nodeId) const {
    return m_vals[nodeId];
}

// Print the graph
template <class T>
void Graph<T>::printGraph() const {
    for (const auto& entry : m_nodes) {
        std::cout << "Node " << entry.first << " is connected to: ";
        for (int neighbor : entry.second) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}

