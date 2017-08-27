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
    PowerOp(double inputValue, int power);
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


/*
 * The add operation;
 */
class AddOp : public Op {
private:
    Op* firstInputOp;
    Op* secondInputOp;

public:
    AddOp(Op* firstInputOp, Op* secondInputOp);
    AddOp(Op* firstInputOp, double secondInputValue);
    AddOp(double firstInputValue, Op* secondInputOp);
    AddOp(double firstInputValue, double secondInputValue);
    double forward();
    double backward(string partialDerivativeOpname="");
};

/*
 * The add operation;
 */
class MinusOp : public Op {
private:
    Op* firstInputOp;
    Op* secondInputOp;

public:
    MinusOp(Op* firstInputOp, Op* secondInputOp);
    MinusOp(Op* firstInputOp, double secondInputValue);
    MinusOp(double firstInputValue, Op* secondInputOp);
    MinusOp(double firstInputValue, double secondInputValue);
    double forward();
    double backward(string partialDerivativeOpname="");
};


} // namespace hplearn

#endif //HPLEARN_OP_H

