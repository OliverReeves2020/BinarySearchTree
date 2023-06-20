#include <iostream>
#include "dictionary.h"


//default constructor
Dictionary::Dictionary() {
    root= nullptr;
    size=0;
}
//Copy constructor
Dictionary &Dictionary::operator=(const Dictionary & dictToCopy) {

    std::cout<<"copy operator\n";
    deepDeleteWorker(root);
    deepCopyWorker(dictToCopy.root);
    return *this;

}
Dictionary::Dictionary(const Dictionary & dictToCopy) {

    root= nullptr;
    size=0;
    std::cout<<"copy dictionary\n";
    //loop through the dicttocopy
    //each value insert into current dictionary
    //go to next value
    //loop through the
    Node* Ptr=dictToCopy.root;

    deepCopyWorker(Ptr);


}
//move constructor
Dictionary &Dictionary::operator=(Dictionary && other) {
    std::cout<<"Moving operator\n";
    deepDeleteWorker(root);

    root=other.root ;
    size=other.size;

    other.root= nullptr;
    other.size=0;
    return *this;
}
Dictionary::Dictionary(Dictionary && other) {
    if (this != &other)
    {
        std::cout<<"Moving object\n";
        root=other.root ;
        size=other.size;

        other.root= nullptr;
        other.size=0;

    }
    else{std::cout<<"can not move object to self\n";
        root= nullptr;
        size=0;

    }




}

void Dictionary::deepCopyWorker(Node *Ptr) {

    if (Ptr == nullptr){
        return;
    }

    insert(Ptr->key,Ptr->item);
    deepCopyWorker(Ptr->left);
    //std::cout<<Ptr->key;
    //std::cout<<" ";

    deepCopyWorker(Ptr->right);
}



void Dictionary::insert(int val, std::string s) {
    insertWorker(val,s,root);

    }



void Dictionary::insertWorker(int val, std::string s, Node *Ptr) {
//creates node and sets next node value to null
    Node *new_node = new Node();
    new_node->key = val;
    new_node->left = nullptr;
    new_node->right = nullptr;
    new_node->item = s;
    //if the bst is empty(null) root=new_node
    if (root == nullptr) {
        root = new_node;

    }
        //less then current ptr
    else if (val < Ptr->key) {
        if (Ptr->left != nullptr) {
            insertWorker(val, s, Ptr->left);
        } else {
            Ptr->left = new_node;
        }
    }
        //greater than current ptr
    else if (val > Ptr->key) {
        if (Ptr->right != nullptr) {
            insertWorker(val, s, Ptr->right);
        } else {
            Ptr->right = new_node;
        }
    }
        //key is equal to current ptr
    else {
        Ptr->item = s;
    }

}



Node * Dictionary::lookup(int val) {

    {
        int depth=0;
        Node* current = root; // Initialize current
        while (current != nullptr) {
            depth=depth+1;
            if (current->key == val){
                std::cout<<"found at depth"+std::to_string(depth)<< std::endl;
                return current;}
            else if (current->key > val){
                current = current->left;
            }
            else{
                current = current->right;
            }
        }
        return nullptr;
    }

}

void Dictionary::displayEntries() {
    Node* temp = root;
    displayEntriesWorker(temp);
}

void Dictionary::displayEntriesWorker(Node * currentNode) {

    if (currentNode == nullptr){
        return;
    }

    displayEntriesWorker(currentNode->left);
    std::cout<<currentNode->depth;
    std::cout<<" ";
    std::cout<<currentNode->key;
    std::cout<<" ";
    std::cout<<currentNode->item<<std::endl;
    displayEntriesWorker(currentNode->right);
}

void Dictionary::displayTree() {
    Node* temp = root;
    int depth=0;
    displayTreeLeaf(temp,depth,2);

}

void Dictionary::displayTreeLeaf(Node * currentNode,int depth,int branch) {

    if (currentNode == nullptr) {
        std::cout<<std::string((depth)*4,' ')+"———*"<<std::endl;
        return;
    }

    depth+=1;
    displayTreeLeaf(currentNode->right,depth,0);
    if(branch==0){
        std::cout<<std::string((depth-1)*4,' ')+".———";
    }
    else if(branch==1){
        std::cout<<std::string((depth-1)*4,' ')+"`———";
    }


    std::cout<<currentNode->key << std::endl;

    displayTreeLeaf(currentNode->left,depth,1);



}
















Node *Dictionary::removeworker(Node * root, int val){



    // parent node to temp

        if(val==root->key){
            std::cout<<root->key;
            return root;
        }
        //left branch
        if (val < root->key) {
            root = root->left;
            return removeworker(root,val);
        }
            //right branch
        else {
            root = root->right;
            return removeworker(root,val);

        }

    }

void Dictionary::RemoveNode(int key) {
    RemoveNodeworker(key, root);
}

void Dictionary::RemoveNodeworker(int key, Node *parent) {
    //if it has nodes
    if(root != nullptr){
        //if the root matches
        if (root->key==key){
            RemoveRootMatch();
        }
        //else
        else{

            if(key < parent->key && parent->left!= nullptr){
                //if equal else not == ?
                parent->left->key == key ?
                RemoveMatch(parent,parent->left,true):
                RemoveNodeworker(key, parent->left);
            }
            else if(key > parent->key && parent->right != nullptr){
                parent->right->key == key ?
                RemoveMatch(parent,parent->right,false):
                RemoveNodeworker(key, parent->right);
            }
            //key doesn't exist
            else{
                std::cout<<"key does not exist\n";
            }
        }
    }
    //if empty
    else{
        std::cout<<"the tree is empty";
    }
}
//if root matches the key
void Dictionary::RemoveRootMatch() {

    if (root != nullptr){
        Node* delptr = root;
        int rootKey = root->key;
        //if two branches available will choose smallest
        std::pair<int,std::string> temp;
        int smallestInRightBranch;
        std::string newitem;
        //if 0 children
        if(root->left == nullptr && root->right== nullptr){
            root= nullptr;
            delete delptr;
        }
        //if 1 child only
        ////child on right but not left
        else if (root->left== nullptr && root->right != nullptr){
            root=root->right;
            //remove old node
            delptr->right=nullptr;
            delete delptr;
            std::cout << "the root has been deleted\n";
        }
        ////child on left but not right
        else if (root->right== nullptr && root->left != nullptr){
            root=root->left;
            //remove old node
            delptr->left=nullptr;
            delete delptr;
            std::cout << "the root has been deleted\n";

        }
        //if 2 children
        else{
            temp=findSmallestWorker(root->right);
            smallestInRightBranch=temp.first;
            newitem=temp.second;
            //delete smallest in right branch
            RemoveNodeworker(smallestInRightBranch,root);
            root->key = smallestInRightBranch;
            root->item = newitem;
            //change to allow for item to also come from function
            std::cout<<"the root key was overwritten with new key\n";
        }
    }
    else{
        std::cout<<"Unable to remove node, tree is empty\n";
    }
}

std::pair<int,std::string> Dictionary::FindSmallest() {
    return findSmallestWorker(root);

}

std::pair<int,std::string> Dictionary::findSmallestWorker(Node* Ptr) {
    if(root== nullptr){
        std::cout<<"tree is empty\n";
        return std::pair<int,std::string>(-1,"none");
    }
    else{
        //traverse left branch, no need to look
        // at right branch since left is smaller

        if(Ptr->left != nullptr){
            return findSmallestWorker(Ptr->left);
        }
        else{
            return std::pair<int,std::string>(Ptr->key,Ptr->item);
        }
    }
}

void Dictionary::RemoveMatch(Node *parent, Node *match, bool left) {
    if(root != nullptr){
        Node* delPtr;
        int matchKey = match->key;
        int smallestInRightBranch;
        std::string newitem;
        std::pair<int,std::string> temp;

        //0 children
        if(match->left== nullptr && match->right== nullptr){
            delPtr = match;
            left ?
            parent->left= nullptr :parent->right= nullptr;
            std::cout<<match->item<<"node removed\n";
            std::cout<<"removed has no leafs\n";
            delete delPtr;
        }
        //if 1 child
        else if(match->left== nullptr && match->right!= nullptr){
            left ?
            parent->left=match->right :parent->right=match->right;
            match->right= nullptr;
            std::cout<<"removed has one leaf\n";
            delete  match;}
        else if(match->left!= nullptr && match->right== nullptr){
            left ?
            parent->left=match->left :parent->right=match->left;
            match->left= nullptr;
            std::cout<<"removed has one leaf\n";
            delete  match;}

        //if 2 children
        else{
            temp=findSmallestWorker(match->right);
            smallestInRightBranch=temp.first;
            newitem=temp.second;
            RemoveNodeworker(smallestInRightBranch,match);
            //overwrite after deletion
            match->key=smallestInRightBranch;
            match->item=newitem;
            std::cout<<"removed has 2 leafs\n";
        }

    }
    else{
        std::cout<<"can not remove match line removematch function\n";
    }
}

Dictionary::~Dictionary() {
    std::cout<<"start destructor\n";

    deepDeleteWorker(root);
    std::cout<<"end destructor\n";
}

void Dictionary::deepDeleteWorker(Node *Ptr) {

    //post order traversal

    if (Ptr != nullptr){

        if(Ptr->left != nullptr){
        deepDeleteWorker(Ptr->left);
        }
        if(Ptr->right != nullptr){
            deepDeleteWorker(Ptr->right);
        }
        //once gone to left and right most
        delete Ptr;

}
}



void Dictionary::tempRotation(int key) {

    auto found=lookup(key);
    if (found!= nullptr){
        std::cout<<"exists";
        rotateRight(found);

    }
    else{std::cout<<"error: node does not exist\n";}

}

void Dictionary::rotateLeft(Node* A) {

    Node* parent= getParent(root,A->key);
    if(parent!= nullptr){
    Node* B=A->right;
    if(B!= nullptr) {

        //Node* t1=A->left;
        Node* t2=B->left;
        //Node* t3=B->right;

        B->left=A;
        A->right=t2;
        //if on right side of parent

        if (parent->right->key==A->key){
            parent->right=B;
        }
        else if(parent->left->key==A->key){
            parent->left=B;
        }
        else{std::cout<<"error";}


    }
    else{
        std::cout<<"value B does not exist";
    }}
    //if value is root node
    else{
        Node* B=A->right;
        if(B!= nullptr) {

            //Node* t1=A->left;
            Node* t2=B->left;
            //Node* t3=B->right;

            B->left=A;
            A->right=t2;
            root=B;


        }
        else{
            std::cout<<"value B does not exist";
        }
    }

}

Node *Dictionary::getParent(Node *A,int key) {
    {
        //if node has no parent
        if (A == nullptr or A->key == key) {
            return nullptr;
        }

        //if current node is parent
        if ((A->left != nullptr && A->left->key == key) or (A->right != nullptr && A->right->key == key)) {
            return A;
        }

        //traverse the tree until node has either node on left or right with key
        Node* parent = getParent(A->left, key);

        if (parent != nullptr) {
            return parent;
        }

        parent = getParent(A->right, key);
        return parent;
    }

    return nullptr;
}

void Dictionary::rotateRight(Node* A) {
    std::cout<<A->left->key;
    Node* parent= getParent(root,A->key);
    if(parent!= nullptr){
        Node* B=A->left;
        if(B!= nullptr) {

            Node* t1=B->left;
            Node* t2=B->right;
            //Node* t3=A->right;

            B->right=A;
            B->left=t1;
            A->left=t2;
            //if on right side of parent

            if (parent->right->key==A->key){
                parent->right=B;
            }
            else if(parent->left->key==A->key){
                parent->left=B;
            }
            else{std::cout<<"error";}


        }
        else{
            std::cout<<"value B does not exist";
        }}
        //if value is root node
    else{
        Node* B=A->left;
        if(B!= nullptr) {

            Node* t1=B->left;
            Node* t2=B->right;
            //Node* t3=A->right;

            B->right=A;
            B->left=t1;
            A->left=t2;
            root=B;


        }
        else{
            std::cout<<"value B does not exist";
        }
    }
}

void Dictionary::removeIfworker(int key,Node* Ptr,std::function<bool(int,int)> Parser) {



    if (Ptr != nullptr){

        if(Ptr->left != nullptr){
            removeIfworker(key,Ptr->left,Parser);
        }
        if(Ptr->right != nullptr){
            removeIfworker(key,Ptr->right,Parser);
        }
        if(Parser(key,Ptr->key)){
            RemoveNode(Ptr->key);}

    }
}

void Dictionary::removeIf(int k,std::function<bool(int,int)> Parser) {

    removeIfworker(k,root,Parser);
}




Node::Node() {

 left= nullptr;
 right=nullptr;

}

