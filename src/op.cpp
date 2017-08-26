//
// Created by tobe on 26/8/2017.
//

#include "op.h"

namespace hplearn {

// Op
Op::Op() : name(""), value(0.0) {

}

Op::Op(string name) : name(name), value(0.0) {

}

Op::Op(string name, double value) {
    this->name = name;
    this->value = value;
}

string Op::getName() {
    return this->name;
}

void Op::setName(string name) {
    this->name = name;
}

double Op::getValue() {
    return this->value;
}

void Op::setValue(double value) {
    this->value = value;
}


// ConstantOp
ConstantOp::ConstantOp() : Op("ConstantOp") {

}

ConstantOp::ConstantOp(double value) : Op("ConstantOp", value) {

}

double ConstantOp::forward() {
    return this->getValue();
}

double ConstantOp::backward() {
    return 0;
}


// PlaceholderOp
PlaceholderOp::PlaceholderOp() : Op("PlaceholderOp") {

}

PlaceholderOp::PlaceholderOp(double value) : Op("PlaceholderOp", value) {

}

double PlaceholderOp::forward() {
    return this->getValue();
}

double PlaceholderOp::backward() {
    return 0;
}

// VariableOp
VariableOp::VariableOp() : Op("VariableOp") {

}

VariableOp::VariableOp(double value) : Op("VariableOp", value) {

}

double VariableOp::forward() {
    return this->getValue();
}

double VariableOp::backward() {
    // TODO: Return 1 or 0
    return 0;
}

// PowerOp
PowerOp::PowerOp() : Op("PowerOp") {

}

PowerOp::PowerOp(double value) : Op("PowerOp", value) {

}

double PowerOp::forward() {
    // TODO: Check value type
    return this->getValue();
}

double PowerOp::backward() {
    // TODO: Check value type
    return 0;
}


} // namespace hplearn
