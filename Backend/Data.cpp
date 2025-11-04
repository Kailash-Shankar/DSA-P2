#include "Red-Black.cpp"
#include "B.cpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

int main(){
ifstream file("DSA_P2_data.csv");

 if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }


string discard;
string zip;
string price;
vector<string> info;
string stat;




Red_Black tree;
getline(file, discard); // Get rid of first line

auto start = std::chrono::high_resolution_clock::now();

int count = 0;

while (getline(file, discard, ',')){
    count++;
    getline(file, discard, ',');
    getline(file, zip, ',');
    
    for (int i=0;i<4; i++){
        if (i == 2){
            getline(file, stat, '\"');
            getline(file, stat, '\"');
            info.push_back(stat);
            getline(file, stat, ',');
        
        } else{
            getline(file, stat, ',');
            info.push_back(stat);
        }

    }
     
    
    getline(file, price);
   
    //cout << zip << info[0] << " " << info[1] << " " << info[2] <<" " << info[3] << price << endl;
    
    tree.insert(stoi(zip), info, stof(price));


    // if (count == 1000) break;
    
    
}

auto end = std::chrono::high_resolution_clock::now();


std::chrono::duration<double> duration = end - start;

cout << "Time taken: " << duration.count() << " seconds" << endl;

return 0;

}

