
#include <string>
#include <iostream>

#include <glog/logging.h>

#include "graph.h"

namespace hplearn {


Graph::Graph() {
    this->name = "";
}

Graph::Graph(string name) : name(name) {

}

map<string, Op*> Graph::getNameOpMap() {
    return this->nameOpMap;
}

map<string, Op*> Graph::getTrainableNameOpMap() {
    return this->trainableNameOpMap;
}


string Graph::getUniqueName(string inputName) {
    string outputName = inputName;
    int index = 0;

    while (this->nameOpMap.count(outputName) > 0 ) {
        outputName = outputName + "_" + to_string(index);
        index += 1;
    }

    // cout << "Unique op name is " << outputName << endl;
    return outputName;
}

void Graph::addNameOpMap(string name, Op *op) {
    this->nameOpMap[name] = op;
}

void Graph::addToGraph(Op *op) {
    // Get unique name and set in the op
    string opName = this->getUniqueName(op->getName());
    if (opName != op->getName()) {
        op->setName(opName);
    }

    this->addNameOpMap(opName, op);


}



} // namespace hplearn
