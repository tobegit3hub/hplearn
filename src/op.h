//
// Created by tobe on 26/8/2017.
//

#ifndef HPLEARN_OP_H
#define HPLEARN_OP_H

#include<string>
using namespace std;

namespace hplearn {

/*
 * The abstract operation.
 */
class Op {
protected:
    string name;

public:
    Op();
    Op(string name);
    string getName();
    void setName(string name);
    virtual double forward() = 0;
    virtual double backward(string partialDerivativeOpname="") = 0;
};

/*
 * The constant operation.
 */
class ConstantOp : public Op {
private:
    double value;

public:
    ConstantOp();
    ConstantOp(double value);
    double getValue();
    void setValue(double value);
    double forward();
    double backward(string partialDerivativeOpname="");
};

/*
 * The placeholder operation.
 */
class PlaceholderOp : public Op {
private:
    double value;

public:
    PlaceholderOp();
    PlaceholderOp(double value);
    double getValue();
    void setValue(double value);
    double forward();
    double backward(string partialDerivativeOpname="");
};

/*
 * The variable operation.
 */
class VariableOp : public Op {
private:
    double value;

public:
    VariableOp();
    VariableOp(double value);
    double getValue();
    void setValue(double value);
    double forward();
    double backward(string partialDerivativeOpname="");
};

/*
 * The power operation.
 */
class PowerOp : public Op {
private:
    Op* inputOp;
    int power;

public:
    PowerOp(Op* inputOp, int power);
    double forward();
    double backward(string partialDerivativeOpname="");
};

/*
 * The square operation;
 */
class SquareOp : public PowerOp {
public:
    SquareOp(Op* inputOp);
};




} // namespace hplearn

#endif //HPLEARN_OP_H

