//
//  FileReader.hpp
//  bird
//
//  Created by 汪依尘 on 6/15/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef FileReader_hpp
#define FileReader_hpp

#include <stdio.h>
#include <string>

class FileReader
{
private:
    FileReader() = delete;
public:
    static std::string ReadFile(const std::string& filePath);
};

#endif /* FileReader_hpp */
