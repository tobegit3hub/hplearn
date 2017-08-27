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
    bool isTrainable;

public:
    VariableOp();
    VariableOp(double value);
    VariableOp(double value, bool isTrainable);
    double getValue();
    void setValue(double value);
    double forward();
    double backward(string partialDerivativeOpname="");
    bool getIsTrainable();
    void setIsTrainable(bool isTrainable);
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
 * The square operation.
 */
class SquareOp : public PowerOp {
public:
    SquareOp(Op* inputOp);
};


/*
 * The add operation.
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
 * The minus operation.
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

/*
 * The multiple operation.
 */
class MultipleOp : public Op {
private:
    Op* firstInputOp;
    Op* secondInputOp;

public:
    MultipleOp(Op* firstInputOp, Op* secondInputOp);
    MultipleOp(Op* firstInputOp, double secondInputValue);
    MultipleOp(double firstInputValue, Op* secondInputOp);
    MultipleOp(double firstInputValue, double secondInputValue);
    double forward();
    double backward(string partialDerivativeOpname="");
};

/*
 * The divide operation.
 */
class DivideOp : public Op {
private:
    Op* firstInputOp;
    Op* secondInputOp;

public:
    DivideOp(Op* firstInputOp, Op* secondInputOp);
    DivideOp(Op* firstInputOp, double secondInputValue);
    DivideOp(double firstInputValue, Op* secondInputOp);
    DivideOp(double firstInputValue, double secondInputValue);
    double forward();
    double backward(string partialDerivativeOpname="");
};





} // namespace hplearn

#endif //HPLEARN_OP_H

