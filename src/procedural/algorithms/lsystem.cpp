#include "lsystem.h"

LSystemRule::LSystemRule(int predecessorData, std::vector<int> successorData)
{
    predecessor = predecessorData;
    successor = successorData;
}


LSystem::~LSystem()
{
    for(LSystemRule* rule : rules)
    {
        delete rule;
    }
}

void LSystem::generate(int seed, int start, int steps, std::vector<int>& out)
{
    srand(seed);

    out.clear();
    out.push_back(start);

    for(int step = 0; step < steps; step++)
    {
        LSystemRule* rule = rules[rand() % rules.size()];
        for (std::vector<int>::iterator it = out.begin() ; it != out.end(); ++it)
        {
            if(*it == rule->predecessor)
            {
                out.erase(it);
                out.insert(it, rule->successor.begin(), rule->successor.end());
                break;
            }
        }
    }

}
