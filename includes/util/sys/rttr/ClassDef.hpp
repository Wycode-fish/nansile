//
//  ClassDef.hpp
//  bird
//
//  Created by 汪依尘 on 7/31/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef ClassDef_hpp
#define ClassDef_hpp

#include <stdio.h>
#include "Attribute.hpp"
#include <vector>
#include <string>

#define CLASSDEF_DEFINED    0x01
#define CLASSDEF_UNDEFINED  0x00

namespace rttr {
    
    class Object;
    class ClassDef
    {
        typedef std::vector<Attribute> AttributeContainer;
        typedef std::vector<Attribute>::const_iterator AttrIterator;
        
    public:
        ClassDef(ClassDef* const base, const char*& name);
        ClassDef(ClassDef* const base, const char*& name, AttrIterator begin, AttrIterator end);
        
    public:
        inline      Attribute const &    GetAttribute(size_t idx) const { return m_EffectiveAttributes[idx]; }
        inline      void                 AddAttribute(const Attribute & attr) { m_OwnAttributes.push_back(attr); }
        inline      size_t               GetAttributeCount() const { return m_EffectiveAttributes.size(); }
        size_t      FindAttribute(std::string const & name) const;
        
    public:
        Object*     New();
        
    public:
        inline AttrIterator GetAttribsBegin() const { return m_EffectiveAttributes.begin(); }
        inline AttrIterator GetAttribsEnd() const { return m_EffectiveAttributes.end(); }

    public:
        inline const char* GetName() const { return m_Name; }
        inline unsigned char GetIsDefined() const { return m_IsDefined; }
        inline const AttributeContainer GetEffectiveAttribs() const { return m_EffectiveAttributes; }
        inline const AttributeContainer GetOwnAttribs() const { return m_OwnAttributes; }
        
    private:
        void BaseInit();
        
    private:
        ClassDef* const m_Base;
        const char* m_Name;
        AttributeContainer m_OwnAttributes, m_EffectiveAttributes;
        unsigned char m_IsDefined;
    };
}
#endif /* ClassDef_hpp */
