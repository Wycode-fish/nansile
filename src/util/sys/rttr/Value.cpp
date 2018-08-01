//
//  Value.cpp
//  bird
//
//  Created by 汪依尘 on 7/30/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "Value.hpp"

namespace rttr {
    
    Value::Value(BaseValue* value)
    : m_Value(value)
    {}
    
    Value::Value(const Value& rhs)
    : m_Value(rhs.m_Value?rhs.m_Value->Clone():nullptr)
    {}
    
    Value::~Value()
    {
        if (m_Value != nullptr)
            delete m_Value;
    }
    
    Value& Value::operator=(const rttr::Value & rhs)
    {
        if (m_Value != nullptr)
        {
            if (rhs.m_Value)
            {
                m_Value->Set(rhs);
            }
            else
            {
                BaseValue* temp = m_Value;
                m_Value = nullptr;
                delete temp;
            }
        }
        else
        {
            m_Value = rhs.m_Value?rhs.m_Value->Clone():nullptr;
        }
        return *this;
    }
    
    std::string Value::AsString()
    {
        return m_Value?m_Value->AsString():std::string();
    }
    
}
