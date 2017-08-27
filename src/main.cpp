//
// Created by tobe on 26/8/2017.
//

#include <iostream>

#include "op.h"

using namespace std;
using namespace hplearn;


void testOp() {
    // Test ConstantOp
    ConstantOp* constantOp = new ConstantOp(10.5);

    cout << "ConstantOp name: " << constantOp->getName() << endl;
    cout << "ConstantOp forward: " << constantOp->forward() << endl;
    cout << "ConstantOp backword: " << constantOp->backward() << endl;

    // Test PlaceholderOp
    PlaceholderOp* placeholderOp = new PlaceholderOp();
    placeholderOp->setValue(10.5);

    cout << "PlaceholderOp name: " << placeholderOp->getName() << endl;
    cout << "PlaceholderOp forward: " << placeholderOp->forward() << endl;
    cout << "PlaceholderOp backword: " << placeholderOp->backward() << endl;

    // Test VariableOp
    VariableOp* variableOp = new VariableOp(10.5);

    cout << "VariableOp name: " << variableOp->getName() << endl;
    cout << "VariableOp forward: " << variableOp->forward() << endl;
    cout << "VariableOp backword: " << variableOp->backward() << endl;

    // Test PowerOp
    PowerOp* powerOp = new PowerOp(variableOp, 3);

    cout << "PowerOp name: " << powerOp->getName() << endl;
    cout << "PowerOp forward: " << powerOp->forward() << endl;
    cout << "PowerOp backword: " << powerOp->backward() << endl;


    // Test SquareOp
    SquareOp* squareOp = new SquareOp(variableOp);

    cout << "SquareOp name: " << squareOp->getName() << endl;
    cout << "SquareOp forward: " << squareOp->forward() << endl;
    cout << "SquareOp backword: " << squareOp->backward() << endl;
}

int main() {
    cout<<"Start main"<<endl;

    testOp();

    return 0;
}