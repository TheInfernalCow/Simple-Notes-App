#ifndef SOURCE_CONFIG_HPP
#define SOURCE_CONFIG_HPP

#include <algorithm>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Config
{
public:
    Config(std::string configFilename, std::string textFilname);
    void loadConfig(std::string configFilename, std::string textFilename);
    std::string getValue(std::string key);
    std::string operator [](std::string key);
    std::string getText();

private:
    std::string m_configFilename, m_textFilename, m_text;
    std::unordered_map<std::string, std::string> m_map;

};

#endif
