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

#include <iostream>

#include "../src/op.h"
#include "../src/graph.h"
#include "../src/session.h"
#include "../src/optimizer.h"

using namespace std;
using namespace hplearn;


void benchmarkAddOperation() {
    int epochNumber = 1000000;

    // Create graph
    Graph* graph = new Graph();
    ConstantOp* constantOp1 = new ConstantOp(10.0);
    ConstantOp* constantOp2 = new ConstantOp(32.0);
    AddOp* addOp = new AddOp(constantOp1, constantOp2);

    graph->addToGraph(constantOp1);
    graph->addToGraph(constantOp2);
    graph->addToGraph(addOp);

    // Create session
    Session* sess = new Session(graph);

    // Start training
    for (int i=0; i<epochNumber; ++i) {
        sess->run(addOp->getName());
    }
}


int main(int argc,char* argv[]) {
    cout << "Benchmark scenario: add operation, epoch: 1000000" << endl;
    benchmarkAddOperation();
    return 0;
}