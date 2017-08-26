//
// Created by tobe on 26/8/2017.
//

#include <iostream>

#include "op.h"

using namespace std;


void testOp() {
    //Op* op = new Op("AddOp");
    //cout<<op->getName()<<endl;

    // Test ConstantOp
    ConstantOp* constantOp = new ConstantOp();
    constantOp->setValue(100.1);

    cout << "ConstantOp name: " << constantOp->getName() << endl;
    cout << "ConstantOp forward: " << constantOp->forward() << endl;
    cout << "ConstantOp backword: " << constantOp->backward() << endl;

}

int main() {

    cout<<"Hello main"<<endl;

    testOp();


    return 0;
}