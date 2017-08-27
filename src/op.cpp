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

#include <math.h>

#include "op.h"

namespace hplearn {

// Op
Op::Op() : name("") {

}

Op::Op(string name) : name(name) {

}

string Op::getName() {
    return this->name;
}

void Op::setName(string name) {
    this->name = name;
}

// ConstantOp
ConstantOp::ConstantOp() : Op("ConstantOp") {

}

ConstantOp::ConstantOp(double value) : Op("ConstantOp"), value(value) {

}

double ConstantOp::getValue() {
    return this->value;
}

void ConstantOp::setValue(double value) {
    this->value = value;
}

double ConstantOp::forward() {
    return this->getValue();
}

double ConstantOp::backward(string partialDerivativeOpname) {
    return 0;
}


// PlaceholderOp
PlaceholderOp::PlaceholderOp() : Op("PlaceholderOp") {

}

PlaceholderOp::PlaceholderOp(double value) : Op("PlaceholderOp"), value(value) {

}

double PlaceholderOp::getValue() {
    return this->value;
}

void PlaceholderOp::setValue(double value) {
    this->value = value;
}

double PlaceholderOp::forward() {
    return this->getValue();
}

double PlaceholderOp::backward(string partialDerivativeOpname) {
    return 0;
}

// VariableOp
VariableOp::VariableOp() : Op("VariableOp"), isTrainable(true) {

}

VariableOp::VariableOp(double value) : Op("VariableOp"), value(value), isTrainable(true) {

}

VariableOp::VariableOp(double value, bool isTrainable) : Op("VariableOp"), value(value), isTrainable(isTrainable) {

};

double VariableOp::getValue() {
    return this->value;
}

void VariableOp::setValue(double value) {
    this->value = value;
}

double VariableOp::forward() {
    return this->getValue();
}

double VariableOp::backward(string partialDerivativeOpname) {
    double grad;

    if (partialDerivativeOpname == "") {
        grad = 1;
    } else if (this->getName() == partialDerivativeOpname) {
        grad = 1;
    } else {
        grad = 0;
    }

    return grad;
}

bool VariableOp::getIsTrainable() {
    return this->isTrainable;
}

void VariableOp::setIsTrainable(bool isTrainable) {
    this->isTrainable = isTrainable;
}

// PowerOp
PowerOp::PowerOp(Op* inputOp, int power) : Op("PowerOp"), inputOp(inputOp), power(power) {

}

PowerOp::PowerOp(double inputValue, int power) : Op("PowerOp"), power(power) {
    this->inputOp = new ConstantOp(inputValue);
}

double PowerOp::forward() {
    double x = this->inputOp->forward();
    return pow(x, this->power);
}

double PowerOp::backward(string partialDerivativeOpname) {
    double x = this->inputOp->forward();
    double grad;

    if (PlaceholderOp* op = dynamic_cast<PlaceholderOp*>(this->inputOp)) {
        grad = 0;
    } else if(ConstantOp* op = dynamic_cast<ConstantOp*>(this->inputOp)) {
        grad = 0;
    } else if(VariableOp* op = dynamic_cast<VariableOp*>(this->inputOp)) {
        grad = this->power * pow(x, this->power - 1);
    } else {
        grad = this->power * pow(x, this->power - 1) * this->inputOp->backward(partialDerivativeOpname);
    }

    return grad;
}


// SquareOp
SquareOp::SquareOp(Op* inputOp) : PowerOp(inputOp, 2) {

}

// AddOp
AddOp::AddOp(Op* firstInputOp, Op* secondInputOp) : Op("AddOp"), firstInputOp(firstInputOp), secondInputOp(secondInputOp) {

}

AddOp::AddOp(Op* firstInputOp, double secondInputValue) : Op("AddOp"), firstInputOp(firstInputOp) {
    this->secondInputOp = new ConstantOp(secondInputValue);
}

AddOp::AddOp(double firstInputValue, Op* secondInputOp) : Op("AddOp"), secondInputOp(secondInputOp) {
    this->firstInputOp = new ConstantOp(firstInputValue);
}

AddOp::AddOp(double firstInputValue, double secondInputValue) : Op("AddOp") {
    this->firstInputOp = new ConstantOp(firstInputValue);
    this->secondInputOp = new ConstantOp(secondInputValue);
}

double AddOp::forward() {
    return this->firstInputOp->forward() + this->secondInputOp->forward();
}

double AddOp::backward(string partialDerivativeOpname) {
    double grad = this->firstInputOp->backward(partialDerivativeOpname) + this->secondInputOp->backward(partialDerivativeOpname);
    return grad;
}

// MinusOp
MinusOp::MinusOp(Op* firstInputOp, Op* secondInputOp) : Op("MinusOp"), firstInputOp(firstInputOp), secondInputOp(secondInputOp) {

}

MinusOp::MinusOp(Op* firstInputOp, double secondInputValue) : Op("MinusOp"), firstInputOp(firstInputOp) {
    this->secondInputOp = new ConstantOp(secondInputValue);
}

MinusOp::MinusOp(double firstInputValue, Op* secondInputOp) : Op("MinusOp"), secondInputOp(secondInputOp) {
    this->firstInputOp = new ConstantOp(firstInputValue);
}

MinusOp::MinusOp(double firstInputValue, double secondInputValue) : Op("MinusOp") {
    this->firstInputOp = new ConstantOp(firstInputValue);
    this->secondInputOp = new ConstantOp(secondInputValue);
}

double MinusOp::forward() {
    return this->firstInputOp->forward() - this->secondInputOp->forward();
}

double MinusOp::backward(string partialDerivativeOpname) {
    double grad = this->firstInputOp->backward(partialDerivativeOpname) - this->secondInputOp->backward(partialDerivativeOpname);
    return grad;
}

// MultipleOp
MultipleOp::MultipleOp(Op* firstInputOp, Op* secondInputOp) : Op("MultipleOp"), firstInputOp(firstInputOp), secondInputOp(secondInputOp) {

}

MultipleOp::MultipleOp(Op* firstInputOp, double secondInputValue) : Op("MultipleOp"), firstInputOp(firstInputOp) {
    this->secondInputOp = new ConstantOp(secondInputValue);
}

MultipleOp::MultipleOp(double firstInputValue, Op* secondInputOp) : Op("MultipleOp"), secondInputOp(secondInputOp) {
    this->firstInputOp = new ConstantOp(firstInputValue);
}

MultipleOp::MultipleOp(double firstInputValue, double secondInputValue) : Op("MultipleOp") {
    this->firstInputOp = new ConstantOp(firstInputValue);
    this->secondInputOp = new ConstantOp(secondInputValue);
}

double MultipleOp::forward() {
    return this->firstInputOp->forward() * this->secondInputOp->forward();
}

double MultipleOp::backward(string partialDerivativeOpname) {
    double grad;
    double firstInputOpValue = this->firstInputOp->forward();
    double secondInputOpValue = this->secondInputOp->forward();
    double firstInputOpGrad = this->firstInputOp->backward(partialDerivativeOpname);
    double secondInputOpGrad = this->secondInputOp->backward(partialDerivativeOpname);

    grad = firstInputOpGrad * secondInputOpValue + firstInputOpValue * secondInputOpGrad;
    return grad;
}

// DivideOp
DivideOp::DivideOp(Op* firstInputOp, Op* secondInputOp) : Op("DivideOp"), firstInputOp(firstInputOp), secondInputOp(secondInputOp) {

}

DivideOp::DivideOp(Op* firstInputOp, double secondInputValue) : Op("DivideOp"), firstInputOp(firstInputOp) {
    this->secondInputOp = new ConstantOp(secondInputValue);
}

DivideOp::DivideOp(double firstInputValue, Op* secondInputOp) : Op("DivideOp"), secondInputOp(secondInputOp) {
    this->firstInputOp = new ConstantOp(firstInputValue);
}

DivideOp::DivideOp(double firstInputValue, double secondInputValue) : Op("DivideOp") {
    this->firstInputOp = new ConstantOp(firstInputValue);
    this->secondInputOp = new ConstantOp(secondInputValue);
}

double DivideOp::forward() {
    return this->firstInputOp->forward() * this->secondInputOp->forward();
}

double DivideOp::backward(string partialDerivativeOpname) {
    double grad;
    double firstInputOpValue = this->firstInputOp->forward();
    double secondInputOpValue = this->secondInputOp->forward();
    double firstInputOpGrad = this->firstInputOp->backward(partialDerivativeOpname);
    double secondInputOpGrad = this->secondInputOp->backward(partialDerivativeOpname);

    if (secondInputOpGrad == 0) {
        // TODO: Throw exception because of no reasonable grad
        grad = 0;
    } else {
        grad = firstInputOpGrad * secondInputOpValue - firstInputOpValue * secondInputOpGrad;
        grad = grad / pow(secondInputOpValue, 2);
    }
    return grad;
}


} // namespace hplearn
