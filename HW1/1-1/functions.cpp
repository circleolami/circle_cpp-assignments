#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

#include "functions.hpp"

using namespace std;

// a. CSV 파일 파싱 
void ParseCSV(const std::string &filename, std::map<int, std::string> &header_cols, map<std::string, vector<std::string>> &data_map) {
    ifstream file(filename); 
    string line;
    vector<string> header; 

    // 헤더 정보 파싱 
    if (getline(file, line)) {
        stringstream ss(line);
        string column;
        int index = 0;
        // ,로 구분된 헤더 정보 구분 
        while (getline(ss, column, ',')) {
            header.push_back(column); // 헤더 벡터에 추가
            header_cols[index++] = column; // 인덱스와 컬럼 이름을 맵에 저장
            data_map[column] = vector<string>(); // 데이터 맵에 컬럼 이름으로 빈 벡터 생성
        }
    }

    // 파일의 나머지 부분을 읽으며 데이터 행 파싱
    while (getline(file, line)) {
        stringstream ss(line);
        string data;
        vector<string> row_data; // 한 행의 데이터를 저장
        bool invalidRow = false; // 유효한 행인지 검사 
        // ,로 구분된 데이터 읽기 
        while (ss >> ws, getline(ss, data, ',')) {
            // 큰따옴표 조건 
            if (data.front() == '"' && data.back() != '"') {
                string temp;
                while (getline(ss, temp, ',')) {
                    data += "," + temp;
                    if (temp.back() == '"') break;
                }
            }

            // 빈 요소 조건 
            if (data.empty()) {
                invalidRow = true;
                break;
            }

            row_data.push_back(data); // 행 데이터 벡터에 추가
        }

        // 헤더와 열의 수가 다르거나 빈 요소가 있는 행 무시
        if (row_data.size() != header.size() || invalidRow) continue;

        // 데이터 맵에 행 데이터 추가
        for (size_t i = 0; i < header.size(); ++i) {
            data_map[header[i]].push_back(row_data[i]);
        }
    }
}

int SumColumn(const std::string &column_name, map<std::string, vector<std::string>> &data_map){
    return -1; 
}

double FilterMostFrequentAvg(const std::string &key_col, std::string &value_col, map<std::string, vector<std::string>> &data_map){
    return -1; 
}

void SumTwoColumns(std::string &value_col1, std::string &value_col2, const std::string & out_filename, std::map<int, std::string> & header_cols, map<std::string, vector<std::string>> & data_map){
}
