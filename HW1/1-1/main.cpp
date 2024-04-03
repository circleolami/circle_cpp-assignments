#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include "functions.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <command> <CSV file name>" << endl;
        return 1;
    }

    string prob_no = argv[1];    
    string filename = argv[2];

    map<string, vector<string>> data_map;
    map<int, string> header_cols;
    
    ParseCSV(filename, header_cols, data_map);

    if (prob_no == "a") {
        if (argc != 3) {
            cout << "Please check your command line arguments, Problem a requires two command line arguments: [Problem no.] [CSV file name]" << endl;
            return -1;
        }

        // 추가한 부분 - 결과 출력 
        cout << "[header_cols is constructed as below]" << endl;
        cout << "{";
        for (auto it = header_cols.begin(); it != header_cols.end(); ) {
            cout << it->first << ": \"" << it->second << "\"";
            if (++it != header_cols.end()) cout << ", ";
        }
        cout << "}" << endl;

        cout << endl<< "[data_map is constructed as below]" << endl;
        cout << "{";
        for (auto it = data_map.begin(); it != data_map.end(); ) {
            cout << "\"" << it->first << "\": {";
            for (size_t i = 0; i < it->second.size(); ++i) {
                cout << "\"" << it->second[i] << "\"";
                if (i < it->second.size() - 1) cout << ",";
            }
            cout << "}";
            if (++it != data_map.end()) cout << ", "<<endl;
        }
        cout << "}" << endl;

    } else if (prob_no == "b") {
        if (argc != 4) {
            cout << "Please check your command line arguments, Problem b requires three command line arguments: [Problem no.] [CSV file name] [Target column]" << endl;
            return -1;
        }

    } else if (prob_no == "c") {
        if (argc != 5) {
            cout << "Please check your command line arguments, Problem c requires four command line arguments: [Problem no.] [CSV file name] [Key column name] [Value column name]" << endl;
            return -1;
        }


    } else if (prob_no == "d") {
        if (argc != 6) {
            cout << "Please check your command line arguments, Problem d requires five command line arguments: [Problem no.] [CSV file name] [Value column name1] [Value column name2] [Output file name]" << endl;
            return -1;
        }

    }
    
    return 0;
}
