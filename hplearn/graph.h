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
    void addNameOpMap(string opName, Op* op);
    map<string, Op*> getTrainableNameOpMap();
    void addTrainableNameOpMap(string opName, Op* variableOp);
    string getUniqueName(string inputName);
    void addToGraph(Op* op);

    // TODO: Add toString method
};



} // namespace hplearn

#endif //HPLEARN_GRAPH_H