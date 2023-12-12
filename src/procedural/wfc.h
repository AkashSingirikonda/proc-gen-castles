#ifndef WFC_H
#define WFC_H
#include <queue>
#include "graph.h"

class WFC
{
public:
    // To Implement:

    // PrintGrid Function.

    // Function to check if edge is valid.

    // Rotation space graph, bind new edges.

    // Entropy Function

    // Running the collapse.

    // Choosing the next edge.
    // Takes in a priority queu
    static float calculateEntropy(const std::vector<int>& vec);
//    static float calculateEntropyFromNode(int nodeID);

    struct Tile {
        // Placeholder
        std::string tileLabel;
    };

    std::unordered_map<std::string, std::string> validConnections;

    WFC(Graph<SceneNode>, std::set<Tile>);
private:
//    // Custom comparator for vectors based on their entropy
//    struct VectorEntropyComparator {
//        bool operator()(int v1, int v2) const {
//            double entropy1 = calculateEntropyFromNode(v1);
//            double entropy2 = calculateEntropyFromNode(v2);
//            return entropy1 < entropy2;
//        }
//    };

//    std::priority_queue<std::pair<int, int>, VectorEntropyComparator> pq;
};

#endif // WFC_H
