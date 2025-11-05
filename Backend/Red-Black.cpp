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

        Node* RotateLeft(Node* node){
            Node* temp = node->right;
            node->right = temp->left;    // Link node to temp->left
            if (temp->left) temp->left->parent = node; // Link temp->left to node
            temp->parent = node->parent;
           
            if (node->parent){
            if (node->parent->left == node){ // Node is a left child
                node->parent->left = temp;
            } else { // Node is a right child
                node->parent->right = temp;
            }
        }
            temp->left = node;   // Connect node to temp
            node->parent = temp;
            return temp;
        }

        Node* RotateRight(Node* node){
            Node* temp = node->left;
            node->left = temp->right;    // Link root to temp->right
            if (temp->right) temp->right->parent = node; // Link temp->right to root
            temp->parent = node->parent;
            
            if (node->parent){
            if (node->parent->right == node){ // Node is a left child
                node->parent->right = temp;
            } else { // Node is a right child
                node->parent->left = temp;
            }
        }
            temp->right = node;   // Connect node to temp
            node->parent = temp;
            return temp;
        }


        void insert(int zip, vector<string> info, float price){
            Node* New = insertRecursion(zip, info, price, this->root); //Insert nodes
            this->root = Rebalance(New);  // Maintain invariants
            setcolor(this->root, 0);  // Root is always black 
        }


        Node* Rebalance(Node* node){
           
            
            while (node != this->root && IsRed(node->parent)){  // Check for consecutive red nodes - child and parent are red
            Node* Parent = node->parent;
            Node* Grandparent = Parent ? Parent->parent : nullptr;

            if (!Grandparent) return Parent;
            
                if (Grandparent->right == Parent){   // Uncle is on left side
                    Node* Uncle = Grandparent->left;
                    if (IsRed(Uncle)){ // Uncle is red - Color Flip
                        setcolor(Parent, 0);
                        setcolor(Grandparent, 1);
                        setcolor(Uncle, 0);
                        node = Grandparent;      // Propagate upwards
                        continue;                
                        
                    
                    } else {                                // Uncle is black - Rotation
                    if (Parent->left == node){            // Right-Left Case
                        Parent = RotateRight(Parent);
                        Grandparent->right = Parent;
                        Parent->parent = Grandparent;    
                    
                    }
                    Node* New = RotateLeft(Grandparent);              // Right-Right Case
        

                    setcolor(New, 0);
                    setcolor(New->left, 1);
                    while (New->parent != nullptr){            // Done here - go back up and return root
                        New = New->parent;
                    }
                    return New;              
                    
                    
                    }
                        
                }
                else {  // Uncle is on right side
                    Node* Uncle = Grandparent->right;
                    if (IsRed(Uncle)){ //    Uncle is red - Color Flip
                        setcolor(Parent, 0);
                        setcolor(Grandparent, 1);
                        setcolor(Uncle, 0);
                        node = Grandparent;                 // Propagate upwards
                        continue;
                        
                        
                    } else {                                // Uncle is black - Rotation
                    if (Parent->right == node){            // Left-Right Case
                        Parent = RotateLeft(Parent);    
                        Grandparent->left = Parent;
                        Parent->parent = Grandparent;  
                    }
                    Node* New = RotateRight(Grandparent);              // Left-left Case
                    setcolor(New, 0);
                    setcolor(New->right, 1);
                    while (New->parent != nullptr){                   // Done here - go back up and return root
                        New = New->parent;
                    }
                    return New;            
                        
                    
            
                } 
            } 
        
    }
            while (node->parent != nullptr){
                node = node->parent;
            }

            return node;
        }

        Node* insertRecursion(int zip, vector<string> info, float price, Node* root, Node* par = nullptr ){
            if (root==nullptr){
                return new Node(zip, info, price, par);
                }
            
            if (zip > root->zip){
                root->right = insertRecursion(zip, info, price, root->right, root);
                if (root->right) {root->right->parent = root;}   // Safety
            }

            else if (zip < root->zip){
                root->left = insertRecursion(zip, info, price, root->left, root);
                if (root->left) {root->left->parent = root;}
            }

            else {return root;} //Unlikely to happen in data
        

        return root;


       
    }

        
    Node* search(int zip){ 
        Node* curr = root; 
        while (curr){
            if (zip > curr->zip){ 
                curr = curr->right; 
            } 
            else if (zip < curr->zip){
                curr = curr->left; 
                    
            } else {
                return curr; 
                } 
                    
            } 
            return nullptr; 
                
        }

        //Implementation:
        // Node* n = search(zip)
        // if (n) {output n->price;}


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



    // int main(){
    //     //Testing
    //     Red_Black tree;
    //     vector<string> v = {"a", "b", "c", "d"};
        
        
    //     for (int i=0; i< 10000; i++){
    //     tree.insert(i, v, (float)i*2);
       
    //     }
    
    //     cout << tree.search(9999)->price << endl;

    //     return 0;
    // }
