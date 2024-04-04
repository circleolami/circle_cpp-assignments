#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

#include "functions.hpp"

using namespace std;

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
        while (getline(ss, data, ',')) {
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
        for (int i = 0; i < header.size(); ++i) {
            data_map[header[i]].push_back(row_data[i]);
        }
    }
}

int SumColumn(const std::string &column_name, map<std::string, vector<std::string>> &data_map){
    int sum = 0; // 합계를 저장할 변수 초기화
    // data_map에서 column_name을 키로 사용해 해당 벡터에 접근
    auto it = data_map.find(column_name);
    if (it != data_map.end()) { 
        for (const string& value : it->second) { // 벡터의 각 문자열 값을 순회
            sum += stoi(value); // 문자열을 정수로 변환하여 합계에 추가
        }
    }
    return sum; // 합계 반환
}

double FilterMostFrequentAvg(const std::string &key_col, std::string &value_col, map<std::string, vector<std::string>> &data_map){
    map<string, int> frequency;
    for (const string &key : data_map[key_col]) {
        frequency[key]++;
    }

    // 가장 빈번한 키 찾기
    string mostFrequentKey;
    int maxFrequency = 0;
    for (const auto &pair : frequency) {
        if (pair.second > maxFrequency) {
            mostFrequentKey = pair.first;
            maxFrequency = pair.second;
        }
    }

    // 해당 키에 대응하는 값들의 평균 계산
    vector<string> &values = data_map[value_col];
    long long sum = 0;
    int count = 0;
    for (int i = 0; i < data_map[key_col].size(); ++i) {
        if (data_map[key_col][i] == mostFrequentKey) {
            sum += stoi(values[i]);
            count++;
        }
    }

    if (count == 0) return 0; // 분모 0 방지
    return static_cast<double>(sum) / count; // 평균 return
}

void SumTwoColumns(std::string &value_col1, std::string &value_col2, const std::string &out_filename, std::map<int, std::string> &header_cols, map<std::string, vector<std::string>> &data_map) {
    ofstream outFile(out_filename); 
    vector<string> sumColumn; 
    string newColumnName = "SumOf" + value_col1 + "And" + value_col2; // 새 열 이름 생성

    for (auto &col : header_cols) {
        outFile << col.second << ",";
    }
    outFile << newColumnName << endl; // 새 열 이름을 헤더에 추가

    // 행별로 합산 결과 계산 
    for (size_t i = 0; i < data_map[value_col1].size(); ++i) {
        int sum = stoi(data_map[value_col1][i]) + stoi(data_map[value_col2][i]); // 문자열을 정수로 변환하여 합산
        sumColumn.push_back(to_string(sum)); // 합산된 값을 문자열로 변환하여 저장
    }

    // 새로운 CSV 데이터 쓰기 
    for (size_t i = 0; i < data_map[header_cols[0]].size(); ++i) {
        for (auto &col : header_cols) {
            outFile << data_map[col.second][i] << ",";
        }
        outFile << sumColumn[i] << endl; // 합산된 열 값 추가
    }
}

