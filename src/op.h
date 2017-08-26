//
// Created by tobe on 26/8/2017.
//

#ifndef HPLEARN_OP_H
#define HPLEARN_OP_H

#include<string>
using namespace std;

namespace hplearn {

/*
 * The abstract operation;
 */
class Op {
protected:
    string name;
    double value;

public:
    Op();

    Op(string name);

    Op(string name, double value);

    string getName();

    void setName(string name);

    double getValue();

    void setValue(double value);

    virtual double forward() = 0;

    virtual double backward() = 0;
};

/*
 * The constant operation;
 */
class ConstantOp : public Op {

public:
    ConstantOp();
    ConstantOp(double value);
    double forward();
    double backward();
};

/*
 * The placeholder operation;
 */
class PlaceholderOp : public Op {
public:
    PlaceholderOp();
    PlaceholderOp(double value);
    double forward();
    double backward();
};

/*
* The variable operation;
*/
class VariableOp : public Op {
public:
    VariableOp();
    VariableOp(double value);
    double forward();
    double backward();
};

/*
* The power operation;
*/
class PowerOp : public Op {
public:
    PowerOp();
    PowerOp(double value);
    double forward();
    double backward();
};


} // namespace hplearn

#endif //HPLEARN_OP_H

