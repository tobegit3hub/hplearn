//
// Created by tobe on 26/8/2017.
//

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
VariableOp::VariableOp() : Op("VariableOp") {

}

VariableOp::VariableOp(double value) : Op("VariableOp"), value(value) {

}

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


} // namespace hplearn
