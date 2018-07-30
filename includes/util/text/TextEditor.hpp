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

class TextEditor
{
public:
    static std::string StripLuaFileName(const std::string& path);
    static char* Str2ValuePtr(const std::string& str);
private:
    
};
#endif /* TextEditor_hpp */
