#include "Config.hpp"

Config::Config(std::string configFilename, std::string textFilename):
    m_configFilename(configFilename),
    m_textFilename(textFilename) {

    loadConfig(configFilename, textFilename);

}

void Config::loadConfig(std::string configFilename, std::string textFilename) {

    m_map.clear();

    std::ifstream input(configFilename);
    std::string line;
    
    if (!input.is_open()) {
        std::cout << "[ERROR]: The specified filepath cannot be found!" << std::endl;
        return;
    }
    
    while (std::getline(input, line)) {

        line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
        
        int delimiterPosition = line.find("=");

        m_map[line.substr(0, delimiterPosition)] = line.substr(delimiterPosition + 1);

    }

    input.close();

    std::ifstream textFile;
    textFile.open(textFilename);

    std::stringstream textStream;
    textStream << textFile.rdbuf();

    m_text = textStream.str();

    textFile.close();

}

std::string Config::getValue(std::string key) {

    return m_map[key];

}

std::string Config::operator [](std::string key) {
    
    return m_map[key];

}

std::string Config::getText() {

    return m_text;

}
