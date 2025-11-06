#include <iostream>
#include <cstdlib>
#include <ctime>
#include "BTree.cpp"
using namespace std;

int main(){
    srand(static_cast<unsigned>(time(nullptr)));

    //B Tree with min degree 3
    BTree tree(3);

    int num=1000;
    vector<int> codes;
    codes.reserve(num);

    //Insert 1000 random codes
    for(int i=0;i<num;++i){
        int zip=rand()%100000; //random zip between 0 and 99999

        //just to check for now
        double price=0.0;
        string info="";

        codes.push_back(zip);
        tree.insert(zip, price, info);
    }

    bool found=true;
    for(int zip : codes){
        if(!tree.search(zip)){
            cout << "Could not find inserted zip " << zip << "\n";
            found=false;
            break;
        }
    }

    if(found)
        {cout << "All inserted codes were found successfully.\n";}

    //checking zip codes that are probably not in the tree
    int count=0;
    for(int i=0;i<20;++i){
        int zip=200000+i; //these are outside the 0-99999 range we used
        if(!tree.search(zip))
            {++count;}
    }
    cout << "For zips that do not exist, " << count << " out of 20 were correctly not found.\n";

    //When main ends, destructor runs and deletes all nodes
    return 0;
}
