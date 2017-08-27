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

#include "optimizer.h"

namespace hplearn {





// Optimizer
Optimizer::Optimizer() : name("Optimizer") {

}

Optimizer::Optimizer(string name) : name(name) {

}

string Optimizer::getName() {
    return this->name;
}

void Optimizer::setName(string name) {
    this->name = name;
}


// OptimizerMinimizeOp
OptimizerMinimizeOp::OptimizerMinimizeOp(Graph *graph, Optimizer *optimizer, Op *lossOp) : Op("DivideOp"), graph(graph), optimizer(optimizer), lossOp(lossOp) {


}

Graph * OptimizerMinimizeOp::getGraph() {
    return this->graph;
}

void OptimizerMinimizeOp::setGraph(Graph *graph) {
    this->graph = graph;
}

Optimizer * OptimizerMinimizeOp::getOptimizer() {
    return this->optimizer;
}

void OptimizerMinimizeOp::setOptimizer(Optimizer *optimizer) {
    this->optimizer = optimizer;
}

Op* OptimizerMinimizeOp::getLossOp() {
    return this->lossOp;
}

void OptimizerMinimizeOp::setLossOp(Op *lossOp) {
    this->lossOp = lossOp;
}

double OptimizerMinimizeOp::forward() {


    //variablename_grad_map = self._optimizer.compute_gradients(self._loss)
    //self._optimizer.apply_gradients(variablename_grad_map)
    return 0.0;
}

double OptimizerMinimizeOp::backward(string partialDerivativeOpname) {
    // TODO: Unimplement and throw exception if needed
    return 0.0;
}


// GradientDescentOptimizer
GradientDescentOptimizer::GradientDescentOptimizer(Graph* graph) : Optimizer("GradientDescentOptimizer"), graph(graph), learningRate(0.01) {

}

GradientDescentOptimizer::GradientDescentOptimizer(Graph* graph, double learningRate): Optimizer("GradientDescentOptimizer"), graph(graph), learningRate(learningRate) {

}

Graph* GradientDescentOptimizer::getGraph() {
    return this->graph;
}


void GradientDescentOptimizer::setGraph(Graph *graph) {
    this->graph = graph;
}

double GradientDescentOptimizer::getLearningRate() {
    return this->learningRate;
}

void GradientDescentOptimizer::setLearningRate(double learningRate) {
    this->learningRate = learningRate;
}


void GradientDescentOptimizer::minimize() {

}

void GradientDescentOptimizer::computeGradients() {

}


void GradientDescentOptimizer::applyGradients() {


}


} // namespace hplearn
