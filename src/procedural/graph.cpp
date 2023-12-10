#include "graph.h"
#include "scene/sceneobject.h"
template <typename T>
void Graph<T>::addNode(int nodeId, T *val) {
    if (m_nodes.find(nodeId) == m_nodes.end()) {
        m_nodes[nodeId] = std::set<int>();
        m_vals[nodeId] = val;
    }
}

// Add an undirected edge between two nodes with a weight/type
template <typename T>
void Graph<T>::addEdge(int node1, int node2, int edgeVal) {
    if (m_nodes.contains(node1) && m_nodes.contains(node2)) {
        m_nodes[node1].insert(node2);
        m_nodes[node2].insert(node1);

        m_edgeV[std::pair(node1, node2)] = edgeVal;
        m_edgeV[std::pair(node2, node1)] = edgeVal;
        m_Vedge[edgeVal].insert(std::pair(node1, node2));
        m_Vedge[edgeVal].insert(std::pair(node1, node2));
    } else {
        std::cerr << "Graph does not contain edge" << node1 << " " << node2 << std::endl;
    }
}

// Add an undirected edge between two nodes
template <typename T>
void Graph<T>::addEdge(int node1, int node2) {
    if (m_nodes.contains(node1) && m_nodes.contains(node2)) {
        m_nodes[node1].insert(node2);
        m_nodes[node2].insert(node1);

        m_edgeV[std::pair(node1, node2)] = -1;
        m_edgeV[std::pair(node2, node1)] = -1;
        m_Vedge[-1].insert(std::pair(node1, node2));
        m_Vedge[-1].insert(std::pair(node1, node2));
    } else {
        std::cerr << "Graph does not contain edge" << node1 << " " << node2 << std::endl;
    }
}

// Get neighbors of a node
template <typename T>
const std::set<int>& Graph<T>::getNeighbors(int nodeId) const {
    static const std::set<int> emptySet;
    auto it = m_nodes.find(nodeId);
    return (it != m_nodes.end()) ? it->second : emptySet;
}

// Get value of a node
template <typename T>
T* Graph<T>::getVal(int nodeId) {
    return m_vals[nodeId];
}

// Print the graph
template <typename T>
void Graph<T>::printGraph() const {
    for (const auto& entry : m_nodes) {
        std::cout << "Node " << entry.first << " is connected to: ";
        for (int neighbor : entry.second) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}

template class Graph<SceneNode>;
