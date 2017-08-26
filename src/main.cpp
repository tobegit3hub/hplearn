//
// Created by tobe on 26/8/2017.
//

#include <iostream>

#include "op.h"

using namespace std;
using namespace hplearn;


void testOp() {
    //Op* op = new Op("AddOp");
    //cout<<op->getName()<<endl;

    // Test ConstantOp
    ConstantOp* constantOp = new ConstantOp();
    constantOp->setValue(100.1);

    cout << "ConstantOp name: " << constantOp->getName() << endl;
    cout << "ConstantOp forward: " << constantOp->forward() << endl;
    cout << "ConstantOp backword: " << constantOp->backward() << endl;

    // Test PlaceholderOp
    PlaceholderOp* placeholderOp = new PlaceholderOp();
    placeholderOp->setValue(100.1);

    cout << "PlaceholderOp name: " << placeholderOp->getName() << endl;
    cout << "PlaceholderOp forward: " << placeholderOp->forward() << endl;
    cout << "PlaceholderOp backword: " << placeholderOp->backward() << endl;

    // Test VariableOp
    VariableOp* variableOp = new VariableOp();
    variableOp->setValue(100.1);

    cout << "VariableOp name: " << variableOp->getName() << endl;
    cout << "VariableOp forward: " << variableOp->forward() << endl;
    cout << "VariableOp backword: " << variableOp->backward() << endl;
}

int main() {
    cout<<"Start main"<<endl;

    testOp();

    return 0;
}