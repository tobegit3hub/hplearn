//
// Created by tobe on 26/8/2017.
//

#include "op.h"

namespace hplearn{


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


} // namespace hplearn
