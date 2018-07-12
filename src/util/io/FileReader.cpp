//
//  FileReader.cpp
//  bird
//
//  Created by 汪依尘 on 6/15/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "FileReader.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

std::string FileReader::ReadFile(const std::string& path)
{
    std::ifstream vsFile(path, std::ios::in);
    if (!vsFile.is_open()) {
        std::cout<<"FAIL: shader file loading failed."<<std::endl;
        return "";
    }
    std::string content;
    std::string line = "";
    while (!vsFile.eof()) {
        std::getline(vsFile, line);
        content.append(line+"\n");
    }
    content.append("\0");
    vsFile.close();
    return content;
}
