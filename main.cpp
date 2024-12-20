/*


Author: Aidan Levy
Email: aidanjlevy@gmail.com
Creation Date: December 18th, 2024
Description: 

This program uses the ExpressionTree.h file to
evaluate mathematical expressions. 

Added functionality:

e p sin() cos() tan();

As of right now, the program 
can handle the following
arithmetic operators: 

+ addition
- subtraction
* multiplication
/ division (denomination is not 0)
^ power (both terms are not 0)
% modulus (right term is not 0)


*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "ExpressionTree.h"
#include "sine.h"
using namespace std;

void help();

int main() {

    srand(time(0));
    ExpressionTree tree;
    bool run = true;
    string expr = "";
    double result = 0.0;

    cout << "Welcome to Aidan's Expression Tree!" << endl;
    cout << "Enter 'q' or 'quit' to quit." << endl;
    cout << "Enter 'h' or 'help' for help." << endl;

    do {

        cout << endl;
        cout << ">> ";
        cin >> expr;

        if (expr == "q" || expr == "quit")
            run = false;

        if (expr == "h" || expr == "help") {
            help();
            continue;
        }


        if (run) {
            try {
                tree.buildFromInfix(expr);
                result = tree.evaluate();
                cout << " = " << result << endl;
            } catch (string& e) {
                cout << e << endl;
                tree.clear();
            } catch (const exception& e) {
                cout << "Unexpected error: " << e.what() << endl;
                tree.clear();
            } catch (...) {
                cout << "An unknown error occured." << endl;
                tree.clear();
            }
        }

    } while (run);

    return 0;
}

/*
help()
Description: Provides a list
of all supported arithmetic
operators and transcedental
numbers
*/
void help() {
    cout << endl;
    cout << "Author: Aidan Levy" << endl;
    cout << "Email: aidanjlevy@gmail.com" << endl;
    cout << "Creation Date: December 18th, 2024" << endl;
    cout << "Supported arithmetic operators:" << endl;
    cout << "\t+ - * / ^ %" << endl;
    cout << "Supported transcedental numbers:" << endl;
    cout << "\te p" << endl;
    cout << "Supported functions:" << endl;
    cout << "\tsin() cos() tan();" << endl;
}