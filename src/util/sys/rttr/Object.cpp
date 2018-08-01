//
//  Object.cpp
//  bird
//
//  Created by 汪依尘 on 8/1/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "Object.hpp"

namespace rttr {
    
    Object::Object(const ClassDef* classDef)
    : m_Class(classDef)
    {}
    
    Object::~Object()
    {
        for (auto value: m_Values)
        {
            if (value != nullptr)
            {
                delete value;
            }
        }
    }
    
    void Object::BuildValueList()
    {
        ValueContainer::iterator it = m_Values.begin();
        for (auto attrIterator = InstanceOf().GetAttribsBegin();
             attrIterator != InstanceOf().GetAttribsEnd();
             attrIterator++)
        {
            *(it++) = attrIterator->GetType().NewValue();
        }
    }
    
    Value Object::GetValue(const std::string &name) const
    {
        size_t idx = InstanceOf().FindAttribute(name);
        if (idx == InstanceOf().GetAttributeCount())
        {
            std::cout<<"[ERROR]: Attribute '"<<name<<"' doesn't exist."<<std::endl;
            return Value();
        }
        return GetValue(idx);
    }
    
    void Object::SetValue(const std::string &name, const Value& value)
    {
        size_t idx = InstanceOf().FindAttribute(name);
        if (idx == InstanceOf().GetAttributeCount())
        {
            std::cout<<"[ERROR]: Attribute '"<<name<<"' doesn't exist."<<std::endl;
            return;
        }
        SetValue(idx, value);
    }
}
