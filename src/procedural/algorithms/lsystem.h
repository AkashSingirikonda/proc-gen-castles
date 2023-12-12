#pragma once

#include<vector>

class LSystemRule
{
public:
    LSystemRule(int predecessorData, std::vector<int> successorData);
    int predecessor;
    std::vector<int> successor;
};

class LSystem
{
public:
    LSystem(){};
    ~LSystem();

    void addRule(int predecessorData, std::vector<int> successorData){ rules.push_back(new LSystemRule(predecessorData, successorData)); };

    void generate(int seed, int start, int steps, std::vector<int>& out);

    std::vector<LSystemRule*> rules;
};
