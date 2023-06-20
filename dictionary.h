//
// Created by Oliver Reeves on 06/10/2022.
//
#include "string"
#ifndef WEEK2_DICTIONARY_H
#define WEEK2_DICTIONARY_H
struct Node{
public:
    int key;
    std::string item;
    Node* left;
    Node* right;
    int depth;
    Node();






};

class Dictionary
{
public:
    //constructor
    Dictionary();
    //copy constructor using deep copy
    Dictionary(const Dictionary &);
    Dictionary & operator = (const Dictionary &);

    //move constructor
    Dictionary(Dictionary &&other);
    Dictionary & operator = (Dictionary &&other);
    //destructor
    ~Dictionary();



    //insert new node master
    void insert(int val,std::string);;
    //finds key and returns appropriate depth
    Node* lookup(int val);;
    //display entries master default to in order
    void displayEntries();
    //display tree master
    void displayTree();
    //remove node
    void RemoveNode(int key);
    //find smallest from current branch
    std::pair<int,std::string> FindSmallest();
    //remove node if condition is true
    void removeIf(int k,std::function<bool(int,int)> Parser);
    //temporary function to call rotation
    void tempRotation(int key);


private:
    Node* root;
    int size;
    void insertWorker(int val,std::string s,Node* Ptr);
    //display in preorder worker
    void displayEntriesWorker(Node*);
    //displays each leaf of the tree
    void displayTreeLeaf(Node*,int,int);

    void RemoveNodeworker(int key,Node* parent);
    //can call this VV to find smallest in subtree
    std::pair<int,std::string> findSmallestWorker(Node* Ptr);
    //remove when matching root
    void RemoveRootMatch();
    void RemoveMatch(Node* parent, Node* match, bool left);
    Node* removeworker(Node*,int);
    // recursive worker for deep copy
    void deepCopyWorker(Node* Ptr);
    // recursive worker deep delete
    void deepDeleteWorker(Node* Ptr);

    //private rotation function
    Node* getParent(Node* A,int key);
    void rotateLeft(Node* A);
    void rotateRight(Node* A);
    void removeIfworker(int key,Node* parent,std::function<bool(int,int)> Parser);

};

#endif //WEEK2_DICTIONARY_H
