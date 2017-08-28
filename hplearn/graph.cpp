/* =====================================================================
Copyright 2017 The Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
========================================================================*/

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

void Graph::addNameOpMap(string opName, Op* op) {
    this->nameOpMap[opName] = op;
}

void Graph::addTrainableNameOpMap(string opName, Op* variableOp) {
    this->trainableNameOpMap[opName] = variableOp;
}

void Graph::addToGraph(Op *op) {
    // Get unique name and set in the op
    string opName = this->getUniqueName(op->getName());
    if (opName != op->getName()) {
        op->setName(opName);
    }

    // Add to the map
    this->addNameOpMap(opName, op);

    // Add to the trainable map
    if(VariableOp* variableOp = dynamic_cast<VariableOp*>(op)) {
        if (variableOp->getIsTrainable()) {
            this->addTrainableNameOpMap(opName, variableOp);
        }
    }
}



} // namespace hplearn
