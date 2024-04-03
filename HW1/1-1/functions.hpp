#include <map>
#include <string>
#include <vector>

using namespace std;

void ParseCSV(const std::string & filename, std::map<int, std::string> & header_cols, map<std::string, vector<std::string>> & value_map);
int SumColumn(const std::string &column_name, map<std::string, vector<std::string>> &value_map);
double FilterMostFrequentAvg(const std::string &key_col, std::string &value_col, map<std::string, vector<std::string>> &value_map);
void SumTwoColumns(std::string &value_col1, std::string &value_col2, const std::string & out_filename, std::map<int, std::string> & header_cols, map<std::string, vector<std::string>> & value_map);