#include "ConfigReader.h"
#include <fstream>

#include <iostream>
using namespace std;

using std::string;
using std::ifstream;
using std::unordered_map;

ConfigReader::ConfigReader() {}
bool ConfigReader::Init(string ini_file_path) {
    if (ini_file_path.empty()) {
        return false;
    }

    ifstream ini_file(ini_file_path);
    if (!ini_file.is_open()) {
        return false;
    }

    string line;
    string section_name;
    string item_name, item_value;
    while (getline(ini_file, line)) {
        line = LTrim(line);
        if (line.empty() || line[0] == '#') {
            continue;
        }
        if (line[0] == '[') {
            size_t pos = line.find(']');
            if (pos == string::npos) {
                return false;
            }
            string tmp = line.substr(1, pos-1);
            section_name = Trim(tmp);
	    cout << "section_name: " << section_name << endl;
            if (section_name.empty()) {
                return false;
            }
        } else {
            if (section_name.empty()) {
                return false;
            }
            size_t pos = line.find('=');
            if (pos == string::npos) {
                return false;
            }
            string tmp = line.substr(0, pos);
            item_name = Trim(tmp);
            tmp = line.substr(pos+1);
            item_value = Trim(tmp);
	    cout << "item_name: " << item_name;
	    cout << " item_value: " << item_value << endl;
            if (item_name.empty() || item_value.empty()) {
                return false;
            }
            table_[section_name + "." + item_name] = item_value;
        }
    }
    return true;
}

bool ConfigReader::Get(string key, string &value, string default_value)
{
    bool rc = false;
    value = default_value;
    unordered_map<string, string>::const_iterator iter = table_.find(key);
    if (iter != table_.end()) {
        value = iter->second;
        rc = true;
    }

    return true;
}

bool ConfigReader::Get(string key, int64_t &value, int64_t default_value)
{
    string v;
    bool rc = false;
    value = default_value;
    if (Get(key, v)) {
        value = strtol(v.c_str(), NULL, 10);
        rc = true;
    }
    return rc;
}
bool ConfigReader::Get(std::string key, uint64_t &value, uint64_t default_value)
{
    string v;
    bool rc = false;
    value = default_value;
    if (Get(key, v)) {
        value = strtoul(v.c_str(), NULL, 10);
        rc = true;
    }
    return rc;
}

bool ConfigReader::Get(std::string key, float &value, float default_value)
{
    string v;
    bool rc = false;
    value = default_value;
    if (Get(key, v)) {
        value = strtof(v.c_str(), NULL);
        rc = true;
    }
    return rc;
}

bool ConfigReader::Get(std::string key, bool &value, bool default_value)
{
    string v;
    bool rc = false;
    value = default_value;
    if (Get(key, v) && v == "true") {
        value = true;
        rc = true;
    }
    return rc;
}

std::string ConfigReader::Trim(std::string &word) 
{
    string result;
    size_t start = 0;
    size_t end = word.size() - 1;
    while (start <= end && isspace(word[start])) {
        ++start;
    }

    while (start <= end && isspace(word[end])) {
        --end;
    }

    if (start < end) {
        result = word.substr(start, end - start + 1);
    }
    return result;
}

std::string ConfigReader::LTrim(std::string &word) 
{
    string result;
    size_t start = 0;
    size_t end = word.size() - 1;
    while (start <= end && isspace(word[start])) {
        ++start;
    }

    if (start < end) {
        result = word.substr(start, end - start + 1);
    }
    return result;
}

std::string ConfigReader::RTrim(std::string &word) 
{
    string result;
    size_t start = 0;
    size_t end = word.length() - 1;
    while (start <= end && isspace(word[end])) {
        --end;
    }

    if (start < end) {
        result = word.substr(start, end - start + 1);
    }
    return result;
}

int main(int argc, char **argv) {
    ConfigReader reader;
    bool rc = reader.Init("./conf.ini");
    long age = -1;
    rc = reader.Get("name.age", age);
    cout << "age rc:" << rc << " " << age << endl;
    bool is_xx = false;
    rc = reader.Get("name2.xx", is_xx);
    cout << "xx rc:" << rc << " " << is_xx << endl;
    return 0;
}
