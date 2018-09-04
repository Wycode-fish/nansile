//
//  Attribute.hpp
//  bird
//
//  Created by 汪依尘 on 7/30/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Attribute_hpp
#define Attribute_hpp

#include <stdio.h>
#include "Type.hpp"

namespace rttr {
    
    class Attribute
    {
    public:
        Attribute(Type type, const char*& name);
        inline const char*  GetName() const { return m_Name; }
        inline Type         GetType() const { return m_Type; }
    private:
        Type        m_Type;
        const char* m_Name;
    };
}

#endif /* Attribute_hpp */
