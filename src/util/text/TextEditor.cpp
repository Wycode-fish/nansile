//
//  TextEditor.cpp
//  bird
//
//  Created by 汪依尘 on 7/30/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "TextEditor.hpp"
#include <iostream>

std::string TextEditor::StripLuaFileName(const std::string& path)
{
    int dotPos = -1;
    int firstSlashPos = -1;
    for (int i=path.length()-1; i>=0; i--)
    {
        if (path[i] == '.')
        {
            dotPos = i;
        }
        if (path[i] == '/')
        {
            firstSlashPos = i;
            break;
        }
    }
    if (firstSlashPos > dotPos) return NULL;
    
    std::string res = path.substr(firstSlashPos + 1, dotPos - firstSlashPos - 1);
    return res;
}

char* TextEditor::Str2ValuePtr (const std::string& str)
{
    char* valuePtr = new char[str.length()+1];
    strcpy(valuePtr, str.c_str());
    return valuePtr;
}
