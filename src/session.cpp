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

#include "session.h"

namespace hplearn {

Session::Session() {

}

Session::Session(Graph* graph) : graph(graph) {

}

string Session::getName() {
    return this->name;
}

void Session::setName(string name) {
    this->name = name;
}

Graph * Session::getGraph() {
    return this->graph;
}

void Session::setGraph(Graph *graph) {
    this->graph = graph;
}

double Session::run(string opName) {
    map<string, Op*> nameOpMap = this->graph->getNameOpMap();
    Op* op = nameOpMap[opName];
    double result = op->forward();

    return result;
}

double Session::run(string opName, map<string, double> feedDict) {

    map<string, Op*> nameOpMap = this->graph->getNameOpMap();

    map<string, double>::iterator item;
    for(item=feedDict.begin(); item!=feedDict.end(); ++item) {
        string feedOpName = item->first;
        double value = item->second;
        Op* feedOp = nameOpMap[feedOpName];
        if (PlaceholderOp* placeholderOp = dynamic_cast<PlaceholderOp*>(feedOp)) {
            placeholderOp->setValue(value);
        }
    }

    Op* op = nameOpMap[opName];
    double result = op->forward();

    return result;
}


} // namespace hplearn
