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
isOperator()
Returns true if a valid operator
*/
bool isOperator(char c) {
    return c=='+'||c=='-'||c=='*'||c=='/'||c=='^'||c=='%';
}

/*
precedence()
Description: Returns the precedence of operators
*/
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '^') return 3;
    return 0;
}

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
        // If the token is 'p', use the transcedental number pi.
        else if (token == "p") {
            treeStack.push(new TreeNode(3.1415926535));
        }
        // If the token is "sin", use sin operator
        else if (token == "sin") {

            if (treeStack.empty())
                throw string("Error: Invalid syntax for 'sin'");

            TreeNode *operand = treeStack.top();
            treeStack.pop();

            TreeNode *sinNode = new TreeNode('s');
            sinNode->left = operand;
            sinNode->right = nullptr;

            treeStack.push(sinNode);
        }
        // If the token is "cos", use cos operator
        else if (token == "cos") {
            if (treeStack.empty())
                throw string("Error: Invalid syntax for 'cos'");

            TreeNode *operand = treeStack.top();
            treeStack.pop();

            TreeNode *cosNode = new TreeNode('c');
            cosNode->left = operand;
            cosNode->right = nullptr;

            treeStack.push(cosNode);
        }
        // If the token is "tan", use tan operator
        else if (token == "tan") {
            if (treeStack.empty())
                throw string("Error: Invalid syntax for 'tan'");

            TreeNode *operand = treeStack.top();
            treeStack.pop();

            TreeNode *tanNode = new TreeNode('t');
            tanNode->left = operand;
            tanNode->right = nullptr;

            treeStack.push(tanNode);
        }
        // If the token is an operator, create a parent node
        else {

            if (treeStack.size() < 2)
                throw string("Error: Invalid syntax for operator.");

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
queue<string> ExpressionTree::infixToPostfix(const string& expression) {
    stack<string> operatorStack;
    queue<string> postfixQueue;
    string token;

    for (size_t i = 0; i < expression.length(); ++i) {
        char c = expression[i];

        if (isspace(c)) continue;

        if (isdigit(c) || c == '.') {
            token.clear();
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                token += expression[i++];
            }
            --i;
            postfixQueue.push(token);
        } else if (isalpha(c)) {
            token.clear();
            while (i < expression.length() && isalpha(expression[i])) {
                token += expression[i++];
            }
            --i;
            if (token == "p") {
                postfixQueue.push("p");
            } else if (token == "e") {
                postfixQueue.push("e");
            } else {
                operatorStack.push(token);
            }
        } else if (c == '(') {
            operatorStack.push(string(1, c));
        } else if (c == ')') {
            while (!operatorStack.empty() && operatorStack.top() != "(") {
                postfixQueue.push(operatorStack.top());
                operatorStack.pop();
            }
            if (operatorStack.empty() || operatorStack.top() != "(") {
                throw string("Error: Mismatched parentheses");
            }
            operatorStack.pop();

            if (!operatorStack.empty() && isalpha(operatorStack.top()[0])) {
                postfixQueue.push(operatorStack.top());
                operatorStack.pop();
            }
        } else if (isOperator(c)) {
            while (!operatorStack.empty() &&
                   precedence(operatorStack.top()[0]) >= precedence(c)) {
                postfixQueue.push(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.push(string(1, c));
        } else {
            throw string("Error: Invalid character in expression");
        }
    }

    while (!operatorStack.empty()) {
        postfixQueue.push(operatorStack.top());
        operatorStack.pop();
    }

    return postfixQueue;
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
    if (nodeptr->op == 's')
        return parallelSine(evaluateTree(nodeptr->left));
    if (nodeptr->op == 'c')
        return parallelCosine(evaluateTree(nodeptr->left));
    if (nodeptr->op == 't')
        return parallelTan(evaluateTree(nodeptr->left));

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
