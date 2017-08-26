//
// Created by tobe on 26/8/2017.
//

#ifndef HPLEARN_OP_H
#define HPLEARN_OP_H

#include<string>
using namespace std;

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


class ConstantOp : public Op {

public:

    ConstantOp();

    ConstantOp(double value);

    double forward();

    double backward();
};



#endif //HPLEARN_OP_H

