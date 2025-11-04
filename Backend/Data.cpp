#include "Red-Black.cpp"
#include "httplib.h"
#include "B.cpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

Red_Black tree; // Declare tree

vector<string> fetch_data(int zip){
    Node* n = tree.search(zip);
    vector<string> res;
    if (n) {
        res.push_back(to_string(n->price));
        for (auto i : n->info)
        res.push_back(i);
        

}
return res;
}


void load_data(){

ifstream file("DSA_P2_data.csv");

 if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }


string discard, zip, price, stat;
vector<string> info;


getline(file, discard); // Skip first line (header)



int count = 0;

while (getline(file, discard, ',')){
    count++;
    getline(file, discard, ',');
    getline(file, zip, ',');
    info.clear();
    
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


    if (count == 1000) break;
    
    
}
}


int main(){

auto start = std::chrono::high_resolution_clock::now();

load_data();

auto end = std::chrono::high_resolution_clock::now();


std::chrono::duration<double> duration = end - start;

cout << "Time taken: " << duration.count() << " seconds" << endl;


httplib::Server svr;
    
    // Define the /node/:zip endpoint
    svr.Get(R"(/node/(\d+))", [](const httplib::Request& req, httplib::Response& res) {
        // Extract zip code from URL
        int zip = stoi(req.matches[1].str());
        
        cout << "Request for zip: " << zip << endl;
        
        // Call your getNode function
        vector<string> result = fetch_data(zip);
        
        if (result.empty()) {
            // Zip code not found
            res.status = 404;
            res.set_content(R"({"error": "Zip code not found"})", "application/json");
            return;
        }
        
        // Build JSON response manually
        stringstream json;
        json << "{";
        json << "\"price\": " << result[0] << ",";
        json << "\"info\": [";
        for (size_t i = 1; i < result.size(); i++) {
            json << "\"" << result[i] << "\"";
            if (i < result.size() - 1) json << ",";
        }
        json << "]}";
        
        // Set CORS headers (allows React to call this)
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(json.str(), "application/json");
    });
    
    // Handle OPTIONS requests for CORS
    svr.Options(R"(/node/(\d+))", [](const httplib::Request&, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
    });
    
    // Start server
    cout << "Server running on http://localhost:8080" << endl;
    cout << "Try: http://localhost:8080/node/12345" << endl;
    
    svr.listen("0.0.0.0", 8080);
    

return 0;

}

