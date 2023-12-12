#include "lsystem.h"
#include "lsystemstructuretypes.h"

template <class T>
LSystemRule<T>::LSystemRule(T predecessorData, std::vector<T> successorData)
{
    predecessor = predecessorData;
    successor = successorData;
}

template <class T>
LSystem<T>::~LSystem()
{
    for(LSystemRule<T>* rule : rules)
    {
        delete rule;
    }
}

template <class T>
void LSystem<T>::generate(int seed, T start, int steps, std::vector<T>& out)
{
    srand(seed);

    out.clear();
    out.push_back(start);

    for(int step = 0; step < steps; step++)
    {
        LSystemRule<T>* rule = rules[rand() % rules.size()];
        for (typename std::vector<T>::iterator it = out.begin() ; it != out.end(); ++it)
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

template class LSystem<StructureType>;
