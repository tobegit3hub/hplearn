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
    cout << "ConstantOp backward: " << constantOp->backward() << endl;

    // Test PlaceholderOp
    PlaceholderOp* placeholderOp = new PlaceholderOp();
    placeholderOp->setValue(10.5);

    cout << "PlaceholderOp name: " << placeholderOp->getName() << endl;
    cout << "PlaceholderOp forward: " << placeholderOp->forward() << endl;
    cout << "PlaceholderOp backward: " << placeholderOp->backward() << endl;

    // Test VariableOp
    VariableOp* variableOp = new VariableOp(10.5);

    cout << "VariableOp name: " << variableOp->getName() << endl;
    cout << "VariableOp forward: " << variableOp->forward() << endl;
    cout << "VariableOp backward: " << variableOp->backward() << endl;

    // Test PowerOp
    PowerOp* powerOp = new PowerOp(variableOp, 3);

    cout << "PowerOp name: " << powerOp->getName() << endl;
    cout << "PowerOp forward: " << powerOp->forward() << endl;
    cout << "PowerOp backward: " << powerOp->backward() << endl;

    powerOp = new PowerOp(10, 3);

    cout << "PowerOp name: " << powerOp->getName() << endl;
    cout << "PowerOp forward: " << powerOp->forward() << endl;
    cout << "PowerOp backward: " << powerOp->backward() << endl;

    // Test SquareOp
    SquareOp* squareOp = new SquareOp(variableOp);

    cout << "SquareOp name: " << squareOp->getName() << endl;
    cout << "SquareOp forward: " << squareOp->forward() << endl;
    cout << "SquareOp backward: " << squareOp->backward() << endl;

    // Test AddOp
    VariableOp* firstOp = new VariableOp(20.2);
    VariableOp* secondOp = new VariableOp(10.1);
    AddOp* addOp = new AddOp(firstOp, secondOp);

    cout << "AddOp name: " << addOp->getName() << endl;
    cout << "AddOp forward: " << addOp->forward() << endl;
    cout << "AddOp backward: " << addOp->backward() << endl;

    addOp = new AddOp(addOp, 100.0);

    cout << "AddOp name: " << addOp->getName() << endl;
    cout << "AddOp forward: " << addOp->forward() << endl;
    cout << "AddOp backward: " << addOp->backward() << endl;

    // Test MinusOp
    MinusOp* minusOp = new MinusOp(firstOp, secondOp);

    cout << "MinusOp name: " << minusOp->getName() << endl;
    cout << "MinusOp forward: " << minusOp->forward() << endl;
    cout << "MinusOp backward: " << minusOp->backward() << endl;

    // Test MultipleOp
    MultipleOp* multipleOp = new MultipleOp(firstOp, secondOp);

    cout << "MultipleOp name: " << multipleOp->getName() << endl;
    cout << "MultipleOp forward: " << multipleOp->forward() << endl;
    cout << "MultipleOp backward: " << multipleOp->backward() << endl;

    cout << "MultipleOp backward(first): " << multipleOp->backward(firstOp->getName()) << endl;
    cout << "MultipleOp backward(second): " << multipleOp->backward(secondOp->getName()) << endl;

    // Test DivideOp
    DivideOp* divideOp = new DivideOp(firstOp, secondOp);

    cout << "DivideOp name: " << divideOp->getName() << endl;
    cout << "DivideOp forward: " << divideOp->forward() << endl;
    cout << "DivideOp backward: " << divideOp->backward() << endl;

    cout << "DivideOp backward(first): " << divideOp->backward(firstOp->getName()) << endl;
    cout << "DivideOp backward(second): " << divideOp->backward(secondOp->getName()) << endl;

}

int main() {
    cout<<"Start main"<<endl;

    testOp();

    return 0;
}