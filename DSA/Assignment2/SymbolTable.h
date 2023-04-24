#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "main.h"
class Node
{
public:
    string identifier;
    string type;
    string val;
    int level;
    bool static_insert;
    Node* left;
    Node* right;
    Node* parent;
    Node() : identifier(""), type(""), val(""), level(0), static_insert(0), left(NULL), right(NULL), parent(NULL) {};
};

class SymbolTable
{
private:
    Node* root;
    int num_splay;
    int num_com;
public:
    SymbolTable() : root(NULL), num_splay(0), num_com(0) {};

    void deleteSymbol(Node* &node);

    Node* newNode(string identifier, string type, string val, int level, bool static_insert);

    void leftRotate(Node* x);

    void rightRotate(Node *x);

    void splay(Node *x);

    void insertNode(int level, string identifier, string type, bool static_insert, string val, string instruction);

    Node* searchTreeHelper(Node* node, int level, string identifier);

    Node* searchTreeHelper1(Node* node, int level, string identifier);

    bool searchTree(int level, string identifier);

    bool searchTree1(int level, string identifier);

    Node* searchNode(int level, string identifier);

    void Check_compare(int level, string func, string type, string instruction);

    void assignNode(int level, string identifier, string val, string instruction);

    void split(Node* &x, Node* &s, Node* &t);

    Node* maximum(Node* node);

    Node* join(Node* s, Node* t);

    void deleteNodeHelper(Node* node, int level, string identifier);

    void preOrder(Node* node);

    void run(string filename);

    ~SymbolTable()
    {
        deleteSymbol(root);
    }
};
#endif
