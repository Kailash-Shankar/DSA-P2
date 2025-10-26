#include <iostream>
#include <vector>

using namespace std;

struct Node{

    bool isRed = true;
    int zip = 0;
    vector<string> info;
    float price;
    Node* left;
    Node* right;


    Node(int z, vector<string> i, float p){
    zip = z;
    info = i;
    price = p;
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

    void insert(int zip, vector<string> info, float price ){
        this->root = insertRecursion(zip, info, price);
    }

    Node* insertRecursion(int zip, vector<string> info, float price, Node* root = nullptr, bool first_call = true ){
        if (root==nullptr){
            if (first_call){
                root = this->root;
                if (!root){
                    return new Node(zip, info, price);
                }
            } else{
            return new Node(zip, info, price);
            }
        }

        if (zip > root->zip){
            root->right = insertRecursion(zip, info, price, root->right, false);
        }

        else if (zip < root->zip){
            root->left = insertRecursion(zip, info, price, root->left, false);

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

    
};

int main(){
    Red_Black tree;
    vector<string> v = {"a", "b", "c", "d"};
    tree.insert(5, v, 2.5);   


    
    return 0;
}