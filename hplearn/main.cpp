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

#include <glog/logging.h>
#include <gflags/gflags.h>

#include "op.h"
#include "graph.h"
#include "session.h"
#include "optimizer.h"

using namespace std;
using namespace hplearn;


void testOp() {
    // Test ConstantOp
    ConstantOp* constantOp = new ConstantOp(10.5);

    cout << "ConstantOp name: " << constantOp->getName() << endl;
    cout << "ConstantOp forward: " << constantOp->forward() << endl;
    cout << "ConstantOp backward: " << constantOp->backward() << endl;

    // Test PlaceholderOp
    PlaceholderOp* placeholderOp = new PlaceholderOp();
    placeholderOp->setValue(10.5);

    cout << "PlaceholderOp name: " << placeholderOp->getName() << endl;
    cout << "PlaceholderOp forward: " << placeholderOp->forward() << endl;
    cout << "PlaceholderOp backward: " << placeholderOp->backward() << endl;

    // Test VariableOp
    VariableOp* variableOp = new VariableOp(10.5);

    cout << "VariableOp name: " << variableOp->getName() << endl;
    cout << "VariableOp forward: " << variableOp->forward() << endl;
    cout << "VariableOp backward: " << variableOp->backward() << endl;

    // Test PowerOp
    PowerOp* powerOp = new PowerOp(variableOp, 3);

    cout << "PowerOp name: " << powerOp->getName() << endl;
    cout << "PowerOp forward: " << powerOp->forward() << endl;
    cout << "PowerOp backward: " << powerOp->backward() << endl;

    powerOp = new PowerOp(10, 3);

    cout << "PowerOp name: " << powerOp->getName() << endl;
    cout << "PowerOp forward: " << powerOp->forward() << endl;
    cout << "PowerOp backward: " << powerOp->backward() << endl;

    // Test SquareOp
    SquareOp* squareOp = new SquareOp(variableOp);

    cout << "SquareOp name: " << squareOp->getName() << endl;
    cout << "SquareOp forward: " << squareOp->forward() << endl;
    cout << "SquareOp backward: " << squareOp->backward() << endl;

    // Test AddOp
    VariableOp* firstOp = new VariableOp(20.2);
    VariableOp* secondOp = new VariableOp(10.1);
    AddOp* addOp = new AddOp(firstOp, secondOp);

    cout << "AddOp name: " << addOp->getName() << endl;
    cout << "AddOp forward: " << addOp->forward() << endl;
    cout << "AddOp backward: " << addOp->backward() << endl;

    addOp = new AddOp(addOp, 100.0);

    cout << "AddOp name: " << addOp->getName() << endl;
    cout << "AddOp forward: " << addOp->forward() << endl;
    cout << "AddOp backward: " << addOp->backward() << endl;

    // Test MinusOp
    MinusOp* minusOp = new MinusOp(firstOp, secondOp);

    cout << "MinusOp name: " << minusOp->getName() << endl;
    cout << "MinusOp forward: " << minusOp->forward() << endl;
    cout << "MinusOp backward: " << minusOp->backward() << endl;

    // Test MultipleOp
    MultipleOp* multipleOp = new MultipleOp(firstOp, secondOp);

    cout << "MultipleOp name: " << multipleOp->getName() << endl;
    cout << "MultipleOp forward: " << multipleOp->forward() << endl;
    cout << "MultipleOp backward: " << multipleOp->backward() << endl;

    cout << "MultipleOp backward(first): " << multipleOp->backward(firstOp->getName()) << endl;
    cout << "MultipleOp backward(second): " << multipleOp->backward(secondOp->getName()) << endl;

    // Test DivideOp
    DivideOp* divideOp = new DivideOp(firstOp, secondOp);

    cout << "DivideOp name: " << divideOp->getName() << endl;
    cout << "DivideOp forward: " << divideOp->forward() << endl;
    cout << "DivideOp backward: " << divideOp->backward() << endl;

    cout << "DivideOp backward(first): " << divideOp->backward(firstOp->getName()) << endl;
    cout << "DivideOp backward(second): " << divideOp->backward(secondOp->getName()) << endl;

}

void testGraphAndSession() {
    // Create Graph
    Graph* graph = new Graph();

    ConstantOp* constantOp1 = new ConstantOp(1.0);
    ConstantOp* constantOp2 = new ConstantOp(2.5);
    AddOp* addOp = new AddOp(constantOp1, constantOp2);

    graph->addToGraph(constantOp1);
    graph->addToGraph(constantOp2);
    graph->addToGraph(addOp);

    // Create session
    Session* session = new Session(graph);

    double result = session->run(addOp->getName());
    cout << "Session run result: " << to_string(result) << endl;

}

void testPlaceholder() {
    // Create Graph
    Graph* graph = new Graph();

    PlaceholderOp* placeholderOp1 = new PlaceholderOp();
    PlaceholderOp* placeholderOp2 = new PlaceholderOp();
    AddOp* addOp = new AddOp(placeholderOp1, placeholderOp2);

    graph->addToGraph(placeholderOp1);
    graph->addToGraph(placeholderOp2);
    graph->addToGraph(addOp);

    // Create session
    Session* session = new Session(graph);

    map<string, double> feedDict;
    feedDict[placeholderOp1->getName()] = 10.1;
    feedDict[placeholderOp2->getName()] = 20.3;
    double result = session->run(addOp->getName(), feedDict);
    cout << "Run with placeholder result: " << to_string(result) << endl;
}

void testOptimizer() {
    // Create Graph
    Graph* graph = new Graph();

    VariableOp* variableOp1 = new VariableOp(10.0);
    VariableOp* variableOp2 = new VariableOp(20.5);
    AddOp* addOp = new AddOp(variableOp1, variableOp2);
    Op* lossOp = addOp;

    GradientDescentOptimizer* optimizer = new GradientDescentOptimizer(graph);
    Op* trainOp = (OptimizerMinimizeOp*) optimizer->minimize(lossOp);

    graph->addToGraph(variableOp1);
    graph->addToGraph(variableOp2);
    graph->addToGraph(addOp);
    graph->addToGraph(trainOp);

    // Create session
    Session* session = new Session(graph);

    // Run training
    session->run(trainOp->getName());
    double loss = session->run(lossOp->getName());
    cout << "Loss is " << to_string(loss) << endl;

    session->run(trainOp->getName());
    loss = session->run(lossOp->getName());
    cout << "Loss is " << to_string(loss) << endl;

}


void testOverridedOperator() {
    // Create Graph
    Graph* graph = new Graph();

    VariableOp* variableOp1 = new VariableOp(20.2);
    VariableOp* variableOp2 = new VariableOp(10.1);
    AddOp* addOp = (AddOp*) (*variableOp1 + *variableOp2);
    MinusOp* minusOp = (MinusOp*) (*variableOp1 - *variableOp2);
    MultipleOp* multipleOp = (MultipleOp*) (*variableOp1 * *variableOp2);
    DivideOp* divideOp = (DivideOp*) (*variableOp1 / *variableOp2);

    graph->addToGraph(variableOp1);
    graph->addToGraph(variableOp2);
    graph->addToGraph(addOp);
    graph->addToGraph(minusOp);
    graph->addToGraph(multipleOp);
    graph->addToGraph(divideOp);

    // Create session
    Session* session = new Session(graph);
    cout << "Overrided + operator result is " << to_string(session->run(addOp->getName())) << endl;
    cout << "Overrided - operator result is " << to_string(session->run(minusOp->getName())) << endl;
    cout << "Overrided * operator result is " << to_string(session->run(multipleOp->getName())) << endl;
    cout << "Overrided / operator result is " << to_string(session->run(divideOp->getName())) << endl;
}


void testLinearRegression() {
    // Define train data
    double learningRate = 0.01;
    int epochNumber = 20;
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

        // Print loss and model
        double lossValue = sess->run(lossOp->getName(), feedDict);
        double weightValue = sess->run(weights->getName());
        double biasValue = sess->run(bias->getName());
        cout << "Epoch: " << to_string(i) << ", loss: " << to_string(lossValue) << ", weight: "
             << to_string(weightValue) << ", bias: " << to_string(biasValue) << endl;
    }

}


int main(int argc,char* argv[]) {
    cout<<"Start main"<<endl;

    testOp();

    testGraphAndSession();

    testPlaceholder();

    testOptimizer();

    testOverridedOperator();

    testLinearRegression();

    return 0;
}