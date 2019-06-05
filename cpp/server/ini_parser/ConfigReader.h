#ifndef CONFIG_READER_H
#define CONFIG_READER_H
/**
 *  Desc: ini config reader 
 *  Date: 20190222
 *  Author: yumin.gao
 *  History: v1.0
 */

#include <unordered_map>
#include <string>
class ConfigReader {
public:
    ConfigReader();
    bool Init(std::string ini_file_path);
    bool Get(std::string key, std::string &value, std::string default_value="");
    bool Get(std::string key, int64_t &value, int64_t default_value = 0);
    bool Get(std::string key, uint64_t &value, uint64_t default_value = 0);
    bool Get(std::string key, float &value, float default_value = 0.0);
    bool Get(std::string key, bool &value, bool default_value = false);
private:
    std::string Trim(std::string &word);
    std::string LTrim(std::string &word);
    std::string RTrim(std::string &word);
private:
    std::unordered_map<std::string, std::string> table_;
};

#endif
