#include "Red-Black.cpp"
#include "httplib.h"
#include "B.cpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
using namespace std;

Red_Black RB; // Declare trees
BTree B(3);

vector<string> fetch_data(int zip, double& dur, bool isRB){

    auto start = std::chrono::high_resolution_clock::now();


    cout << "searching..." << endl;
    Node* n = nullptr;
    if (isRB){
        n = RB.search(zip);
        cout << "RB tree!" << endl;
     } else {
         cout << "B tree!" << endl;
        const BTree::Record* r = B.find(zip);
        if (r)
        n = new Node(r->zip, r->info, r->price);
     }

    
    vector<string> res;
    if (n) {
        cout << "FOUND in tree!" << " price:" << n->price << endl;
        res.push_back(to_string(n->price));
        for (auto i : n->info)
        res.push_back(i);

        delete n;

        

} else cout << "NOT FOUND in tree!" << endl;

    auto end = std::chrono::high_resolution_clock::now();  // Move this earlier if necessary

    std::chrono::duration<double> duration = end - start;
    
    dur = duration.count();


return res;
}


void load_data(){

ifstream file("DSA_P2_data.csv");

 if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }
cout << "CSV file opened successfully!" << endl;

string discard, zip, price, stat;
vector<string> info;


getline(file, discard); // Skip first line (header)
cout << "Header: " << discard << endl;


int count = 0;

while (getline(file, discard, ',')){
    count++;
    getline(file, discard, ',');
    getline(file, zip, ',');

     if (count <= 5) {
            cout << "Loading zip: " << zip << endl;
        }

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

    
    float Default = 100000.000;
   
    try {
    RB.insert(stoi(zip), info, stof(price));
    B.insert(stoi(zip), info, stof(price));
} catch (const std::exception &e) {
    
    RB.insert(stoi(zip), info, Default);  // Handle typos/formatting issues in dataset
    B.insert(stoi(zip), info, Default);
}


    
    
    
}
}


int main(){

auto start = std::chrono::high_resolution_clock::now();

load_data();

auto end = std::chrono::high_resolution_clock::now();


std::chrono::duration<double> duration = end - start;



cout << "Time taken: " << duration.count() << " seconds" << endl;



httplib::Server svr;
    
    
svr.Get(R"(/node/(\d+))", [](const httplib::Request& req, httplib::Response& res) {
    
    int zip = stoi(req.matches[1].str());

    string type = req.get_param_value("tree");
    cout << type << endl;
    
    cout << "Request for zip: " << zip << endl;
    
    
    double dur = 0;
    vector<string> result = fetch_data(zip, dur, type=="red-black");
    
    if (result.empty()) {
        res.status = 404;
        res.set_content(R"({"error": "Zip code not found"})", "application/json");
        return;
    }
    
    
    stringstream json;
    json << "{";
    json << "\"price\": " << result[0] << ",";
    json << "\"time\": " << fixed << setprecision(6) << dur << ",";
    json << "\"info\": [";
    for (size_t i = 1; i < result.size(); i++) {
        json << "\"" << result[i] << "\"";
        if (i < result.size() - 1) json << ",";
    }
    json << "]}";
    
    
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_content(json.str(), "application/json");
});


svr.Options(R"(/node/(\d+))", [](const httplib::Request&, httplib::Response& res) {
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Methods", "GET, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
});

cout << "Server running on http://localhost:8080" << endl;
cout << "Try: http://localhost:8080/node/77494" << endl;

svr.listen("0.0.0.0", 8080);
    

return 0;

}

