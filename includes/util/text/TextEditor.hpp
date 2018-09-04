//
//  TextEditor.hpp
//  bird
//
//  Created by 汪依尘 on 7/30/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef TextEditor_hpp
#define TextEditor_hpp

#include <stdio.h>
#include <string>
#include <sstream>

class TextEditor
{
public:
    static std::string StripLuaFileName(const std::string& path);
    static std::string GetDirectoryFromPath(const std::string& path);
    static const char*  CStrConcate(const char* str1, const char* str2);
    static char* Str2ValuePtr(const std::string& str);
    static std::string GetFileSuffix(const char* fileName);
    
    template <typename T>
    static bool GetValueFromString( const std::string & value, T & result )
    {
        std::istringstream iss( value );
        return !( iss >> result ).fail();
    }
private:
    
};
#endif /* TextEditor_hpp */
