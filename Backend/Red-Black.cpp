#include <iostream>
#include <vector>

using namespace std;

struct Node{

    bool isRed = true;
    int zip = 0;
    vector<string> info;
    float price;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;


    Node(int z, vector<string> i, float p, Node* par = nullptr){
    zip = z;
    info = i;
    price = p;
    parent = par;
}



};

// Implementation:
// Red_black tree;
// Node* root = nullptr;
// for (auto row : CSV_file){
//     tree.insert(row[zip], row[info], row[price]);
// }

class Red_Black{
    Node* root;

    public:

    Red_Black(){
        root = nullptr;
    }
    Node* getRoot(){
        return root;
    }
    bool IsRed(Node* root){
        if (!root){
            return false;
        }
        return root->isRed;
    }

    void setcolor(Node* root, bool red){
        if (root){
            if (red) root->isRed = true;
            else root->isRed = false;
        }

    }

    Node* RotateLeft(Node*& node){
        Node* temp = node->right;
        node->right = temp->left;    // Link node to temp->left
        if (temp->left) temp->left->parent = node; // Link temp->left to node
        temp->parent = node->parent;
        if (!node->parent) {
           this->root = temp;
        } else if (node->parent->left == node){ // Node is a left child
            node->parent->left = temp;
        } else { // Node is a right child
            node->parent->right = temp;
        }
        temp->left = node;   // Connect node to temp
        node->parent = temp;
        return temp;
    }

    Node* RotateRight(Node*& node){
      Node* temp = node->left;
        node->left = temp->right;    // Link root to temp->left
        if (temp->right) temp->right->parent = node; // Link temp->left to root
        temp->parent = node->parent;
        if (!node->parent) {
           this->root = temp;
        } else if (node->parent->right == node){ // Node is a left child
            node->parent->right = temp;
        } else { // Node is a right child
            node->parent->left = temp;
        }
        temp->right = node;   // Connect node to temp
        node->parent = temp;
        return temp;
    }

    void insert(int zip, vector<string> info, float price){
        this->root = insertRecursion(zip, info, price, this->root);

         // Root is always black
        if (root && root->isRed){
            root->isRed = false;
        }
    }

    Node* insertRecursion(int zip, vector<string> info, float price, Node* root = nullptr, Node* par = nullptr ){
        if (root==nullptr){
             return new Node(zip, info, price, par);
            }
        

        if (zip > root->zip){
            root->right = insertRecursion(zip, info, price, root->right, root);
        }

        else if (zip < root->zip){
            root->left = insertRecursion(zip, info, price, root->left, root);

        }

        else {return root;} //Unlikely to happen in data
        
        //Rebalancing------------------------------------------------------------------------------------------------------
        
      
        
        
        
        Node* Parent = root->parent;
        Node* Grandparent = Parent ? Parent->parent : nullptr;
        if (!Parent || !Grandparent) return root;
        
        
        if (IsRed(root) && IsRed(Parent)){  // Check for consecutive red nodes - current and parent are red
            if (Grandparent->right == Parent){   // Left uncle case
                Node* Uncle = Grandparent->left;
                if (IsRed(Uncle)){ // Uncle is red
                    setcolor(Parent, 0);
                    setcolor(Grandparent, 1);
                    setcolor(Uncle, 0);
                   
                } else {                                // Uncle is black
                   if (Parent->left == root){            // Right-Left Case
                    RotateRight(Parent);    
                  
                   }
                   RotateLeft(Grandparent);              // Right-Right Case
                   setcolor(Parent, 0);
                   setcolor(Grandparent, 1);
                 
                    
                }
                    
            }
            else {  // Right uncle case
                Node* Uncle = Grandparent->right;
                if (IsRed(Uncle)){ // Uncle is red
                    setcolor(Parent, 0);
                    setcolor(Grandparent, 1);
                    setcolor(Uncle, 0);
                    
                } else {                                // Uncle is black
                   if (Parent->right == root){            // Left-Right Case
                    Parent = RotateLeft(Parent);    
                    
                   }
                   Grandparent = RotateRight(Grandparent);              // Left-left Case
                   setcolor(Parent, 0);
                   setcolor(Grandparent, 1);
                 
                    
                
                    
        
        
            } 
        } 
    }
        

       return root;



    }

    Node* search(int zip){
        Node* curr = root;
        while (curr){
           
        if (zip > root->zip){
            curr = curr->right;
        }
        else if (zip < root->zip){
            curr = curr->left;
        } 
        else {
            return curr;
        }

        return nullptr;

    }

    }

    void Delete_All(Node* root){
        if (root == nullptr){
            return;
        }

        Delete_All(root->left);   // Postorder traversal

        Delete_All(root->right);

        delete root;
    }

    ~Red_Black(){
        Delete_All(root);

    }
};

int main(){
    //Testing
    Red_Black tree;
    vector<string> v = {"a", "b", "c", "d"};
    tree.insert(5, v, 2.5); 
    tree.insert(7, v, 44.0); 
     tree.insert(1, v, 44.0); 
      tree.insert(2, v, 44.0); 
       tree.insert(63, v, 44.0); 
    Node* r = tree.search(7);   
    cout << r->price << endl;



    return 0;
}