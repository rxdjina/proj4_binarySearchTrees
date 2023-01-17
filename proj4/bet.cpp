#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include "bet.h"

#define ADDITION_OPERATOR '+'
#define SUBTRACTION_OPERATOR '-'
#define MULTIPLICATION_OPERATOR '*'
#define DIVISION_OPERATOR '/'
#define EXPONENTIAL_OPERATOR '^'
#define OPEN_PARENTHESIS '('
#define CLOSED_PARENTHESIS ')'

BET::BET() : root{nullptr} {
}

BET::BET(const std::string postfix) : root{nullptr} {
    buildFromPostfix(postfix);
}

BET::BET(const BET & rhs) : root{nullptr} {
    root = clone(rhs.root);
}

BET::~BET() {
    makeEmpty(root);
}

bool BET::buildFromPostfix(const std::string postfix) {
	std::stringstream ss(postfix);
	std::string token;
    std::stack<BinaryNode*> mStack;
	
	if (!empty()) {
        makeEmpty(root);
    }
	
	while(ss >> token) {
        if (isOperand(token[0])) {
            BinaryNode* tempNode = new BinaryNode(token);
            mStack.push(tempNode);

        } else if (isOperator(token[0])) {
            
            if (mStack.size() < 2) {
                std::cout << "ERROR: INVALID POSTFIX EXPRESSION" << std::endl;
                return false;
            }

            BinaryNode* tempTree = new BinaryNode(token, nullptr, mStack.top());
            mStack.pop();

            tempTree->left = mStack.top();
            mStack.pop();

            mStack.push(tempTree);
        }
	}
	
	if (mStack.size() != 1) {
		std::cout << "ERROR: MISSING OPERATORS" << std::endl;
		return false;

	} else {
		root = mStack.top();
		mStack.pop();

		return true;
	}
}

const BET & BET::operator=(const BET & rhs) {
    root = clone(rhs.root);
    return *this;
}

void BET::printInfixExpression() {
    printInfixExpression(root);
    std::cout << std::endl;
}

void BET::printPostfixExpression() {
    printPostfixExpression(root);
    std::cout << std::endl;
}

size_t BET::size() {
    return size(root);
}

size_t BET::leaf_nodes() {
    return leaf_nodes(root);
}

bool BET::empty() {
    return root == nullptr;
}

void BET::printInfixExpression(BET::BinaryNode *n) {
    if (n != nullptr) { // Inorder Binary Tree Traversal
        if (isOperator(n->element[0]) && n != root) {
            std::cout << OPEN_PARENTHESIS << " ";
        }

        printInfixExpression(n->left);
        std::cout << n->element << " ";
        printInfixExpression(n->right);

        if (isOperator(n->element[0]) && n != root) {
            std::cout << CLOSED_PARENTHESIS << " ";
        }
    }
}

void BET::printPostfixExpression(BET::BinaryNode *n) {
    if (n != nullptr) { // Postorder Binary Tree Traversal
        printPostfixExpression(n->left);
        printPostfixExpression(n->right);
        std::cout << n->element << " ";
    }
}

void BET::makeEmpty(BET::BinaryNode* &t) {
    if (t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);

        delete t;
    }

    t = nullptr;
}

BET::BinaryNode * BET::clone(BET::BinaryNode *t) const {
    if (t == nullptr) {
        return nullptr;
    } else {
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }
}

size_t BET::size(BET::BinaryNode *t) {
    if (t == nullptr) {
        return 0;

    } else {
        return size(t->left) + size(t->right) + 1;
    }
}

size_t BET::leaf_nodes(BET::BinaryNode *t) {
    if (t == nullptr) {
        return 0;

    } else if (t->left == nullptr && t->right == nullptr) {
        return 1;

    } else {
        return leaf_nodes(t->left) + leaf_nodes(t->right);
    }
}

bool BET::isOperator(const char c) {
    return (c == ADDITION_OPERATOR || c == SUBTRACTION_OPERATOR || c == MULTIPLICATION_OPERATOR || c == DIVISION_OPERATOR || c== EXPONENTIAL_OPERATOR);
}

bool BET::isOperand(const char c) {
    return std::isalnum(c);
}

int BET::precedance(const char c) {
    if (c == ADDITION_OPERATOR || c == SUBTRACTION_OPERATOR) {
        return 1;

    } else if (c == MULTIPLICATION_OPERATOR || c == DIVISION_OPERATOR) {
        return 2;

    } else if (c == EXPONENTIAL_OPERATOR) {
        return 3;
    }
        
    return -1;
}