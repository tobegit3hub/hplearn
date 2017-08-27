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

#ifndef HPLEARN_OPTIMIZER_H
#define HPLEARN_OPTIMIZER_H

#include<string>

#include "op.h"
#include "graph.h"

using namespace std;

namespace hplearn {






class Optimizer {
protected:
    string name;

public:
    Optimizer();
    Optimizer(string name);

    string getName();
    void setName(string name);

    virtual void minimize() = 0;
    virtual void computeGradients() = 0;
    virtual void applyGradients() = 0;
};


/**
* The minimize operation for optimizer.
*/
class OptimizerMinimizeOp : public Op {
private:
    Graph* graph;
    Optimizer* optimizer;
    Op* lossOp;


public:
    OptimizerMinimizeOp(Graph* graph, Optimizer* optimizer, Op* lossOp);

    Graph* getGraph();
    void setGraph(Graph* graph);
    Optimizer* getOptimizer();
    void setOptimizer(Optimizer* optimizer);
    Op* getLossOp();
    void setLossOp(Op* lossOp);

    double forward();
    double backward(string partialDerivativeOpname="");

};


class GradientDescentOptimizer : public Optimizer {
private:
    Graph* graph;
    double learningRate;


public:
    GradientDescentOptimizer(Graph* graph);
    GradientDescentOptimizer(Graph* graph, double learningRate);

    Graph* getGraph();
    void setGraph(Graph* graph);
    double getLearningRate();
    void setLearningRate(double learningRate);

    void minimize();
    void computeGradients();
    void applyGradients();
};



} // namespace hplearn

#endif //HPLEARN_OPTIMIZER_H