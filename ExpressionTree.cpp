#include "Headers.h"
#include "ExpressionTree.h"

/*
Default constructor
*/
ExpressionTree::ExpressionTree() { 
    root = nullptr; 
    prevResult = 0;
}

/*
Destructor
*/
ExpressionTree::~ExpressionTree() { clear(); }

/*
clear()
Description: Destroys the tree from the root
*/
void ExpressionTree::clear() { destroyTree(root); }

/*
destroyTree()
Description: Recursively deletes nodes
*/
void ExpressionTree::destroyTree(TreeNode *&nodeptr) {
    if (nodeptr) {
        destroyTree(nodeptr->left);
        destroyTree(nodeptr->right);
        delete nodeptr;
        nodeptr = nullptr;
    }
}

/*
buildFromInfix()
Description: Converts infix to postfix
*/
void ExpressionTree::buildFromInfix(const string& infix) {
    clear();

    // Convert the infix expression to postfix
    queue<string> postfix = infixToPostfix(infix);

    // Use a stack to build the expression tree
    stack<TreeNode*> treeStack;

    while (!postfix.empty()) {
        string token = postfix.front();
        postfix.pop();

        // If the token is a number, create a leaf node
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            treeStack.push(new TreeNode(stod(token)));
        } 
        // If the token is 'e', use the transcedental number e.
        else if (token == "e") {
            treeStack.push(new TreeNode(2.7182818284));
        }
        // If the token is an operator, create a parent node
        else {
            TreeNode* right = treeStack.top();
            treeStack.pop();
            TreeNode* left = treeStack.top();
            treeStack.pop();

            TreeNode* operatorNode = new TreeNode(token[0]);
            operatorNode->left = left;
            operatorNode->right = right;

            treeStack.push(operatorNode);
        }
    }

    // The last node in the stack is the root of the expression tree
    if (!treeStack.empty()) {
        root = treeStack.top();
        treeStack.pop();
    }

}

/*
infixToPostfix()
Description: Converts infix expr to postfix expr
*/
queue<string> ExpressionTree::infixToPostfix(const string& infix) {
    stack<char> operators;
    queue<string> output;
    string number;

    auto pushNumber = [&]() {
        if (!number.empty()) {
            output.push(number);
            number.clear();
        }
    };

    for (size_t i = 0; i < infix.size(); ++i) {
        char c = infix[i];

        if (isdigit(c) || c == '.') {
            number += c;
        } else {
            pushNumber();

            if (c == 'A') {
                output.push(to_string(prevResult));
            } else if (c == 'e') {
                output.push("2.7182818284");
            } else if (c == 'p') {
                output.push("3.1415926535");
            } else if (c == '(') {
                operators.push(c);
            } else if (c == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    output.push(string(1, operators.top()));
                    operators.pop();
                }
                operators.pop();
            } else if (c == '-' && (i == 0 || infix[i - 1] == '(' || infix[i - 1] == '+' || infix[i - 1] == '-' || infix[i - 1] == '*' || infix[i - 1] == '/')) {
                number += c;
            } else {
                while (!operators.empty() && precedence(c) <= precedence(operators.top())) {
                    output.push(string(1, operators.top()));
                    operators.pop();
                }
                operators.push(c);
            }
        }
    }

    pushNumber();

    while (!operators.empty()) {
        output.push(string(1, operators.top()));
        operators.pop();
    }

    return output;
}

/*
precedence()
Description: Returns the precedence of operators
*/
int ExpressionTree::precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '^') return 3;
    return 0;
}

/*
evaluate()
Description: Calls recursive evaluateTree() function
            to evaluate the tree.
*/
double ExpressionTree::evaluate() {
    if (!root) {
        throw string("Error: Nothing to evaluate");
    }
    prevResult = evaluateTree(root);
    return prevResult;
}

/*
evaluateTree()
Description: Evaluates the tree
*/
double ExpressionTree::evaluateTree(TreeNode *nodeptr) {
    if (!nodeptr)
        return 0;
    if (nodeptr->op == '\0')
        return nodeptr->value;

    // Recursive traversals to calculate left and right subtrees
    double leftVal = evaluateTree(nodeptr->left);
    double rightVal = evaluateTree(nodeptr->right);

    // Perform operation
    switch (nodeptr->op) {
        case '+': return leftVal+rightVal;
        case '-': return leftVal-rightVal;
        case '*': return leftVal*rightVal;
        case '/': 
            if (rightVal==0) throw string("Error: Cannot divide by 0");
            return leftVal/rightVal;
        case '^':
            if (leftVal==0&&rightVal==0) throw string("Error: Cannot compute 0^0");
            return pow(leftVal, rightVal);
        case '%':
            if (static_cast<int>(rightVal)==0) throw string("Error: Cannot compute modulus 0");
            return static_cast<int>(leftVal) % static_cast<int>(rightVal);
        default: throw string("Error: Unknown operator");
    }

}

/*
inorder()
Description: Calls recursive inorder()
*/
void ExpressionTree::inorder() { inorder(root); }

/*
inorder()
Description: Recursively prints expression inorder
*/
void ExpressionTree::inorder(TreeNode *nodeptr) {
    if (nodeptr) {
        if (nodeptr->op != '\0') cout << "(";
        inorder(nodeptr->left);
        if (nodeptr->op != '\0') cout << nodeptr->op << " ";
        else cout << nodeptr->value << " ";
        inorder(nodeptr->right);
        if (nodeptr->op != '\0') cout << ")";
    }
}

/*
preorder()
Description: Calls recursive preorder()
*/
void ExpressionTree::preorder() { preorder(root); }

/*
preorder()
Description: Recursively prints expression preorder
*/
void ExpressionTree::preorder(TreeNode *nodeptr) {
    if (nodeptr) {
        if (nodeptr->op != '\0') cout << nodeptr->op << " ";
        else cout << nodeptr->value << " ";
        preorder(nodeptr->left);
        preorder(nodeptr->right);
    }
}

/*
postorder()
Description: Calls recursive postorder()
*/
void ExpressionTree::postorder() { postorder(root); }

/*
postorder()
Description: Recursively prints expression postorder
*/
void ExpressionTree::postorder(TreeNode *nodeptr) {
    if (nodeptr) {
        postorder(nodeptr->left);
        postorder(nodeptr->right);
        if (nodeptr->op != '\0') cout << nodeptr->op << " ";
        else cout << nodeptr->value << " ";
    }
}
