//
//  Attribute.cpp
//  bird
//
//  Created by 汪依尘 on 7/30/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "Attribute.hpp"

namespace rttr {
    
    Attribute::Attribute(Type type, const char*& name)
    : m_Type(type), m_Name(name)
    {}
    
}

