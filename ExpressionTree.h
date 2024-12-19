#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include "Headers.h"

class ExpressionTree {
private:
    // TreeNode struct
    struct TreeNode {
        char op;
        double value;
        TreeNode *left;
        TreeNode *right;

        TreeNode(char o) {
            op = o;
            value = 0;
            left = right = nullptr;
        }

        TreeNode(double v) {
            op = '\0';
            value = v;
            left = right = nullptr;
        }

        TreeNode() {
            op = '\0';
            value = 0;
            left = right = nullptr;
        }
    };
    TreeNode *root;
    double prevResult;

    // Helper functions
    void destroyTree(TreeNode*&);
    double evaluateTree(TreeNode*);
    queue<string> infixToPostfix(const string&);
    int precedence(char op);

    void inorder(TreeNode*);
    void preorder(TreeNode*);
    void postorder(TreeNode*);

public:
    ExpressionTree();
    ~ExpressionTree();

    void buildFromInfix(const string&);
    double evaluate();
    void clear();

    void inorder();
    void preorder();
    void postorder();
};

#endif
