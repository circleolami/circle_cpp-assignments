#include <string>
#include <map>
#include <vector>
#include <list>
#include <memory>
#include "json/json.h"

using namespace std;

void ParseJSON(const std::string filename, Json::Value & json_object);
std::unique_ptr<std::string> CheckTarget(const Json::Value &json_object, const std::string &target_key);
void CompleteList(const Json::Value & json_object,  std::list<std::string> & empty_list);
void SumTwoMembers(const std::string &key1, const std::string &key2, const std::string &out_filename, Json::Value &json_object);
