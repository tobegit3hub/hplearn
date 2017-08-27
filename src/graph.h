#ifndef HPLEARN_GRAPH_H
#define HPLEARN_GRAPH_H

#include <string>
#include <map>

#include "op.h"

using namespace std;

namespace hplearn {


class Graph {
private:
    string name;
    map<string, Op*> nameOpMap;
    map<string, Op*> trainableNameOpMap;

public:
    Graph();
    Graph(string name);
    map<string, Op*> getNameOpMap();
    void addNameOpMap(string name, Op* op);
    map<string, Op*> getTrainableNameOpMap();
    void addTrainableNameOpMap(string name, Op* op);
    string getUniqueName(string inputName);
    void addToGraph(Op* op);
};



} // namespace hplearn

#endif //HPLEARN_GRAPH_H