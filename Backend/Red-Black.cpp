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

    Node* RotateLeft(Node* root){
        Node* temp = root->parent->left; 
        root->parent->left = root->parent->parent;
        root->parent->parent->right = temp;
    }

    Node* RotateRight(Node* root){
        Node* temp = root->parent->right; 
        root->parent->right = root->parent->parent;
        root->parent->parent->left = temp;
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
        
        //Rebalancing
        
        bool parentIsLeftChild = false;
        
        if (root->parent && root->parent->parent && root->parent->parent->left == root->parent){
            parentIsLeftChild = true;
        }

        
        if (IsRed(root) && IsRed(root->parent)){  // Check for consecutive red nodes - current and parent are red
            if (!parentIsLeftChild){   // Left uncle case
                if (IsRed(root->parent->parent->left)){ // Uncle is red
                    setcolor(root->parent, 0);
                    setcolor(root->parent->parent, 1);
                    setcolor(root->parent->parent->left, 0);
                } else {                                // Uncle is black
                   root = RotateLeft(root);
                    
                }
                    
            }
            else if (parentIsLeftChild && IsRed(root->parent->parent->right)){  // Right uncle case
                if (IsRed(root->parent->parent->right)){ // Uncle is red
                    setcolor(root->parent, 0);
                    setcolor(root->parent->parent, 1);
                    setcolor(root->parent->parent->right, 0);
                } else {                                // Uncle is black
                    root = RotateRight(root);
                }
        
        
        
            } 
        }
        

       return root;



    }

    Node* search(int zip, Node* root = nullptr, bool first_call = true){
        if (root == nullptr){
            if (first_call){
                root = this->root;
                
            } else {
                return nullptr;
            }
        }

        if (zip > root->zip){
            return search(zip, root->right, false);
        }

        else if (zip < root->zip){
            return search(zip, root->left, false);
        }

        else {
            return root;
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
    Red_Black tree;
    vector<string> v = {"a", "b", "c", "d"};
    tree.insert(5, v, 2.5); 
    tree.insert(7, v, 44.0); 
    Node* r = tree.search(7);
    cout << r->price << endl;



    return 0;
}