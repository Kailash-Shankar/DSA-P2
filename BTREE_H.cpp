#ifndef BTREE_H
#define BTREE_H

#include <vector>
#include <string>
#include <stdexcept>

class BTree{
public:
    struct Record{
        int zip;
        double price;
        std::string info;
    };

    //Constructor
    BTree(int minDegree) : root(nullptr), t(minDegree)
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
    
    }

    //checking if zip exists in the tree
    bool search(int zip) const{
        const Record* res=search(root, zip);
        return(res!=nullptr);
    }

    const Record* find(int zip) const{
        return search(root, zip);
    }

private:
    struct Node {
        bool leaf;
        std::vector<Record> records;     
        std::vector<Node*> children;

        Node(bool isLeaf, int minDegree) : leaf(isLeaf)
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
    const Record* search(Node* node, int zip) const {
        if (node==nullptr) return nullptr;

        int i=0;
        while (i<(int)node->records.size() && zip>node->records[i].zip) 
        { ++i; }

        if(i<(int)node->records.size() && zip==node->records[i].zip) {
            return &node->records[i];
        }

        if (node->leaf) { //not in tree
            return nullptr; 
        }

        return search(node->children[i], zip);
    }

#endif //BTREE_H
