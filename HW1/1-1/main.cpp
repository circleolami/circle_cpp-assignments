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

        // 추가한 부분
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

        // 추가한 부분
        string target_column = argv[3];
        int sum = SumColumn(target_column, data_map);

        // 합계를 지정된 형식으로 출력
        cout << "SumColumn(\"" << target_column << "\", data_map)" << endl;
        cout << ">>> " << sum << endl;
    }

    else if (prob_no == "c") {
    if (argc != 5) {
        cout << "Please check your command line arguments, Problem c requires four command line arguments: [Problem no.] [CSV file name] [Key column name] [Value column name]" << endl;
        return -1;
    }

    // 추가한 부분
    string key_column = argv[3];
    string value_column = argv[4];

    // FilterMostFrequentAvg 함수를 호출하여 결과를 계산
    double avg = FilterMostFrequentAvg(key_column, value_column, data_map);

    // 결과를 지정된 형식으로 출력
    cout << "FilterMostFrequentAvg (\"" << key_column << "\", \"" << value_column << "\", data_map)" << endl;
    cout << ">>> " << avg << endl;
}


 else if (prob_no == "d") {
    if (argc != 6) {
        cout << "Please check your command line arguments, Problem d requires five command line arguments: [Problem no.] [CSV file name] [Value column name1] [Value column name2] [Output file name]" << endl;
        return -1;
    }

    // 추가한 부분
    string value_col1 = argv[3];
    string value_col2 = argv[4];
    string out_filename = argv[5];

    // SumTwoColumns 함수를 호출하여 두 열의 값을 합산하고 결과를 새 CSV 파일에 작성 
    SumTwoColumns(value_col1, value_col2, out_filename, header_cols, data_map);

    cout << "The output CSV file '" << out_filename << "' has been created." << endl;
}

    
    return 0;
}
