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
#include <map>
#include <vector>

#include "../src/op.h"
#include "../src/graph.h"
#include "../src/session.h"
#include "../src/optimizer.h"

using namespace std;
using namespace hplearn;


void benchmarkLinearRegression() {
    // Define train data
    double learningRate = 0.01;
    int epochNumber = 1000000;
    vector<double> trainFeatureList = {1.0, 2.0, 3.0, 4.0, 5.0};
    vector<double> trainLabelList = {10.0, 20.0, 30.0, 40.0, 50.0};
    int instanceNumber = trainFeatureList.size();

    // Create graph
    Graph* graph = new Graph();

    VariableOp* weights = new VariableOp(0.0);
    VariableOp* bias = new VariableOp(0.0);
    PlaceholderOp* x = new PlaceholderOp();
    PlaceholderOp* y = new PlaceholderOp();

    Op* multipleOp = *weights * *x;
    Op* predictOp = *multipleOp + *bias;
    Op* minusOp = *y - *predictOp;
    SquareOp* lossOp = new SquareOp(minusOp);
    GradientDescentOptimizer* optimizer = new GradientDescentOptimizer(graph, learningRate);
    OptimizerMinimizeOp* trainOp = (OptimizerMinimizeOp*) optimizer->minimize(lossOp);

    graph->addToGraph(weights);
    graph->addToGraph(bias);
    graph->addToGraph(x);
    graph->addToGraph(y);
    graph->addToGraph(multipleOp);
    graph->addToGraph(predictOp);
    graph->addToGraph(minusOp);
    graph->addToGraph(lossOp);
    graph->addToGraph(trainOp);

    // Create session
    Session* sess = new Session(graph);
    map<string, double> feedDict;

    for (int i=0; i<epochNumber; ++i) {
        // Get training data
        double feature = trainFeatureList[i % instanceNumber];
        double label = trainLabelList[i % instanceNumber];

        // Start training
        feedDict[x->getName()] = feature;
        feedDict[y->getName()] = label;
        sess->run(trainOp->getName(), feedDict);
    }

}


int main(int argc,char* argv[]) {
    cout << "Benchmark scenario: linear regression, epoch: 1000000" << endl;
    benchmarkLinearRegression();
    return 0;
}