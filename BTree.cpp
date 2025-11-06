#ifndef BTREE_H
#define BTREE_H

#include <vector>
#include <string>
#include <stdexcept>

class BTree{
public:
    struct Record{
        int zip{};
        double price{};
        std::string info;
    };

    //Constructor
    explicit BTree(const int minDegree) : root(nullptr), t(minDegree)
    {
        if(t<2){//minDegree validation
            throw std::invalid_argument("B-Tree minimum degree must be at least 2.");
        }
    }

    //destructor
    ~BTree() {
        clear(root);
    }
    BTree(const BTree&) = delete;
    BTree& operator=(const BTree&) = delete;
    
    //Inserting a new record
    void insert(const int zip, const double price, const std::string& info){
        const Record rec{zip, price, info};

        if(root==nullptr){//Makes new root if tree is empty
            root = new Node(true, t);
            root->records.push_back(rec);
            return;
        }

        if(static_cast<int>(root->records.size()) == 2*t-1){ //root is full, increase height of tree
            const auto newRoot = new Node(false, t);
            newRoot->children.push_back(root);
            split(newRoot, 0);

            int i=0;
            if(rec.zip > newRoot->records[0].zip) { i=1;}
            insertNotFull(newRoot->children[i], rec);
            root=newRoot;
        } 
        else{insertNotFull(root, rec);}
    }

    //checking if zip exists in the tree
    [[nodiscard]] bool search(const int zip) const{
        const Record* res=search(root, zip);
        return(res!=nullptr);
    }

    [[nodiscard]] const Record* find(const int zip) const{
        return search(root, zip);
    }

private:
    struct Node {
        bool leaf;
        std::vector<Record> records;     
        std::vector<Node*> children;

        Node(const bool isLeaf, const int minDegree) : leaf(isLeaf)
        {
            //this is just to avoid reallocation 
            records.reserve(2*minDegree-1);
            children.reserve(2*minDegree);
        }
    };

    Node* root;
    int t; //min degree

    //deletion of nodes
    void clear(Node* node){
        if(node==nullptr) return;

        for(Node* child : node->children){
            clear(child);
        }

        delete node;
    }

    //helper for search
    const Record* search(const Node* node, const int zip) const {
        if (node==nullptr) return nullptr;

        int i=0;
        while (i<static_cast<int>(node->records.size()) && zip>node->records[i].zip) 
        { ++i; }

        if(i<static_cast<int>(node->records.size()) && zip==node->records[i].zip) {
            return &node->records[i];
        }

        if (node->leaf) { //not in tree
            return nullptr; 
        }

        return search(static_cast<const Node*>(node->children[i]), zip);
    }

    void split(Node* parent, const int childIndex){
        Node* xChild=parent->children[childIndex];
        const auto newChild=new Node(xChild->leaf, t);

        const int mid= t-1;
        const Record midRecord= xChild->records[mid];

        newChild->records.assign(xChild->records.begin()+t, xChild->records.end());
        xChild->records.resize(t-1);

        if (!xChild->leaf) {
            newChild->children.assign(
                xChild->children.begin() + t,
                xChild->children.end()
            );
            xChild->children.resize(t);
        }

        parent->children.insert(parent->children.begin()+ childIndex +1, newChild);
        parent->records.insert(parent->records.begin()+childIndex, midRecord);
    }

    //inserting a record into a node that is not full
    void insertNotFull(Node* node, const Record& rec){
        int i=static_cast<int>(node->records.size())-1;

        if(node->leaf){
            node->records.push_back(rec);

            while(i>=0 && rec.zip<node->records[i].zip){
                node->records[i+1] = node->records[i]; //right shift
                --i;
            }
            node->records[i + 1] = rec;
        } 
        else{
            //find the child to go down into
            while (i >= 0 && rec.zip < node->records[i].zip){
            --i;
            }++i;//index where record goes

            //if child is full, split
            if(static_cast<int>(node->children[i]->records.size())== 2*t-1){
                split(node, i);

                if (rec.zip > node->records[i].zip) {++i;}
            }

            insertNotFull(node->children[i], rec);
        }
    }
};
#endif //BTREE_H