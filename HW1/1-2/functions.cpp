#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <list>
#include <memory>
#include "json/json.h"

using namespace std;

void ParseJSON(const std::string filename, Json::Value & json_object){
    std::ifstream file(filename, std::ifstream::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    file >> json_object;
    if (file.fail()) {
        throw std::runtime_error("Failed to parse JSON from file: " + filename);
    }
}

std::unique_ptr<std::string> CheckTarget(const Json::Value &json_object, const std::string &target_key) {
    // 키의 값이 문자열인지 확인 
    if (json_object.isMember(target_key) && json_object[target_key].isString()) { 
        return std::make_unique<std::string>(json_object[target_key].asString());
    }
    // 문자열 아니면 nullptr 리턴 
    return nullptr; 
}

void CompleteList(const Json::Value &json_object, std::list<std::string> &empty_list) {
    bool foundString = false; // 문자열이 존재하는지 확인 

    // value를 순회하면서 확인 
    for (const auto& key : json_object.getMemberNames()) {
        const Json::Value& value = json_object[key];
        // 문자열이면 리스트에 삽입 
        if (value.isString()) {
            foundString = true;
            empty_list.push_back(value.asString());
        }
    }

    // 문자열이 하나도 없으면 
    if (!foundString) {
        empty_list.push_back("NO_STRING");
    } else {
        // 문자열 정렬 
        empty_list.sort([](const std::string &a, const std::string &b) { return a > b; });
    }
}


void SumTwoMembers(const string &key1, const string &key2, const string &out_filename, Json::Value &json_object) {
    const Json::Value &array1 = json_object[key1];
    const Json::Value &array2 = json_object[key2];

    // 배열 길이 다르면 종료 
    if (array1.size() != array2.size() || (array1.size() == 0 && array2.size() == 0)) {
        return;
    }

    // 합 계산 
    Json::Value sumArray(Json::arrayValue);
    for (Json::Value::ArrayIndex i = 0; i < array1.size(); ++i) {
        sumArray.append(array1[i].asInt() + array2[i].asInt());
    }

    // 새 키 이름 지정 
    string sumFieldName = "SumOf" + key1 + "And" + key2;
    json_object[sumFieldName] = sumArray;

    // 파일 수정 
    ofstream outFile(out_filename);
    if (!outFile.is_open()) {
        cerr << "Unable to open file for writing: " << out_filename << endl;
        return;
    }
    outFile << json_object.toStyledString();
    outFile.close();
}