//
//  Type.cpp
//  bird
//
//  Created by 汪依尘 on 7/30/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "Type.hpp"
#include "Value.hpp"
#include <string>

namespace rttr {
    
    std::vector<BaseValue*> Type::m_Prototypes = {new RealValue<int>(0), new RealValue<float>(1.0f), new RealValue<unsigned>(0), new RealValue<std::string>("")};
    
    Type::Type(Type::TypeT typeId)
    : m_TypeId(typeId)
    {}
    
    BaseValue* Type::NewValue() const
    {
        return m_Prototypes[this->m_TypeId]->Clone();
    }
}

