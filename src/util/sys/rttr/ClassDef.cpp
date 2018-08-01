//
//  ClassDef.cpp
//  bird
//
//  Created by 汪依尘 on 7/31/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "ClassDef.hpp"
#include "Object.hpp"
namespace rttr {
    
    ClassDef::ClassDef(ClassDef* const base, const char*& name)
    : m_Base(base), m_Name(name), m_IsDefined(CLASSDEF_UNDEFINED)
    {
        BaseInit();
        m_EffectiveAttributes.insert(m_EffectiveAttributes.end(),
                                     m_OwnAttributes.begin(),
                                     m_OwnAttributes.end());
    }
    
    ClassDef::ClassDef(ClassDef* const base, const char*& name, AttrIterator begin, AttrIterator end)
    : m_Base(base), m_Name(name), m_IsDefined(CLASSDEF_UNDEFINED), m_OwnAttributes(begin, end)
    {
        BaseInit();
        m_EffectiveAttributes.insert(m_EffectiveAttributes.end(),
                                     m_OwnAttributes.begin(),
                                     m_OwnAttributes.end());
    }
    
    void ClassDef::BaseInit()
    {
        if (m_Base!=nullptr)
        {
            m_Base->m_IsDefined = CLASSDEF_DEFINED;
            std::copy(m_Base->GetAttribsBegin(), m_Base->GetAttribsEnd(), std::back_inserter<AttributeContainer>(m_EffectiveAttributes));
        }
    }
    
    size_t ClassDef::FindAttribute(std::string const & name) const
    {
        AttributeContainer::const_reverse_iterator it;
        for (it = m_EffectiveAttributes.rbegin(); it != m_EffectiveAttributes.rend(); it++)
        {
            if (strcmp(it->GetName(), name.c_str()) == 0)
            {
                return std::distance(it, m_EffectiveAttributes.rend()) - 1;
            }
        }
        return GetAttributeCount();
    }
    
    Object* ClassDef::New()
    {
        m_IsDefined = CLASSDEF_DEFINED;
        return new Object(this);
    }

}
