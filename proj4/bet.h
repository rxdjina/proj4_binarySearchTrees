#ifndef BET_H
#define BET_H

#include <iostream>
#include <string>
#include <stack>

class BET {
    private:
        struct BinaryNode {
            std::string element;
            BinaryNode* left;
            BinaryNode* right;

            BinaryNode(const std::string & data = std::string{}, BinaryNode *leftNode = nullptr, BinaryNode *rightNode = nullptr)
            		: element{data}, left{leftNode}, right{rightNode} {}
 			BinaryNode(std::string && data, BinaryNode *leftNode = nullptr, BinaryNode *rightNode = nullptr)
            		: element{std::move(data)}, left{leftNode}, right{rightNode} {}   
        };

    public:
        BET(); // Constructor
        BET(const std::string postfix); // One-Parameter Constructor
        BET(const BET&); // Copy Constructor
        ~BET(); // Deconstructor
        bool buildFromPostfix(const std::string postfix); // Build From Postfix Expression
        const BET & operator=(const BET &); // Assignment Operator
        void printInfixExpression(); // Print Infix Expression
        void printPostfixExpression(); // Print Postfix Expression
        size_t size(); // Tree Size
        size_t leaf_nodes(); // Number of Nodes in Tree
        bool empty(); // Returns True if Tree Empty

        // Additional Functions
        bool isOperator(const char c);
        bool isOperand(const char c);
        int precedance(const char c);
         
    private:
        void printInfixExpression(BinaryNode *n); // Print Infix Expression Recurrsively
        void printPostfixExpression(BinaryNode *n); // Print Postfix Expression Recurrsively
        void makeEmpty(BinaryNode* &t); // Empty Tree
        BinaryNode * clone(BinaryNode *t) const; // Copy Tree
        size_t size(BinaryNode *t); // Tree Size
        size_t leaf_nodes(BinaryNode *t); // Number of Nodes in Tree

        BinaryNode* root; // Tree root
};

#endif