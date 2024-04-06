#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <list>
#include "json/json.h"

#include "functions.hpp"

using namespace std;

int main(int argc, char *argv[]){

    if (argc < 3) {
        cout << "Usage: " << argv[0] << " [Problem no.] [JSON file name] <additional arguments>" << endl;
        return -1;
    }

    string prob_no = argv[1];   
    string filename = argv[2];

    Json::Value root;  

    ParseJSON(filename, root);
    // a번은 따로 출력 없음 
    
    if (prob_no == "b") {
    if (argc != 4) {
        cout << "Please check your command line arguments, Problem b requires three command line arguments: [Problem no.] [JSON file name] [Target key]" << endl;
        return -1;
    }

    const string target_key = argv[3];
    unique_ptr<string> res = CheckTarget(root, target_key);

    cout << "CheckTarget(root, \"" << target_key << "\")" << endl;
    cout << ">>> ";
    if (res) {
        cout << "\"" << *res << "\"" << endl;
    } else {
        cout << "nullptr" << endl;
    }
}
else if (prob_no == "c") {
    if (argc != 3) {
        cout << "Please check your command line arguments, Problem c requires two command line arguments: [Problem no.] [JSON file name]" << endl;
        return -1;
    }

    list<string> lst;
    CompleteList(root, lst);

    if (!lst.empty()) {
        cout << "list({";
        for (auto it = lst.begin(); it != lst.end(); ++it) {
            if (it != lst.begin()) {
                cout << ",";
            }
            cout << "\"" << *it << "\"";
        }
        cout << "})" << endl;
    } else {
        cout << "list({\"NO_STRING\"})" << endl;
    }
}
else if (prob_no == "d") {
        if (argc != 6){
            cout << "Please check your command line arguments, Problem d requires five command line arguments: [Problem no.] [JSON file name] [Key name 1] [Key name 2] [Output file name]" << endl;
            return -1;
        }

        string key1 = argv[3];
        string key2 = argv[4];
        string out_filename = argv[5];

        SumTwoMembers(key1, key2, out_filename, root);
    }
    return 0;
}
