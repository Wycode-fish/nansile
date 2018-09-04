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
    for (int i=static_cast<int>(path.length()-1); i>=0; i--)
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

std::string TextEditor::GetDirectoryFromPath(const std::string& path)
{
    int firstSlashPos = -1;
    for (int i=static_cast<int>(path.length()-1); i>=0; i--)
    {
        if (path[i] == '/')
        {
            firstSlashPos = i;
            break;
        }
    }
    if (firstSlashPos < 0) return NULL;
    
    std::string res = path.substr(0, firstSlashPos);
    return res;
}

const char* TextEditor::CStrConcate(const char* str1, const char* str2)
{
    std::string res = str1;
    res = res + std::string(str2);
    
    return Str2ValuePtr(res);
}

char* TextEditor::Str2ValuePtr (const std::string& str)
{
    char* valuePtr = new char[str.length()+1];
    strcpy(valuePtr, str.c_str());
    return valuePtr;
}

std::string TextEditor::GetFileSuffix(const char *fileName)
{
    std::string name(fileName);
    std::string suffix = "";
    for (int i=static_cast<int>(name.length())-1; i>=0; i--)
    {
        if (name[i] == '.')
            break;
        suffix += name[i];
    }
    std::reverse(std::begin(suffix), std::end(suffix));
    return suffix;
}
