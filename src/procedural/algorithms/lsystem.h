#pragma once

#include<vector>

template <class T>
class LSystemRule
{
public:
    LSystemRule(T predecessorData, std::vector<T> successorData);
    T predecessor;
    std::vector<T> successor;
};

template <class T>
class LSystem
{
public:
    LSystem(){};
    ~LSystem();

    void addRule(T predecessorData, std::vector<T> successorData){ rules.push_back(new LSystemRule<T>(predecessorData, successorData)); };

    void generate(int seed, T start, int steps, std::vector<T>& out);

    std::vector<LSystemRule<T>*> rules;
};
