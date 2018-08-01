//
//  Object.hpp
//  bird
//
//  Created by 汪依尘 on 8/1/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include <stdio.h>
#include <vector>
#include "ClassDef.hpp"
#include "Value.hpp"

namespace rttr {
    
    class Object
    {
        typedef std::vector<BaseValue*> ValueContainer;
        
    public:
        explicit Object(const ClassDef* classDef);
        ~Object();
        inline const ClassDef& InstanceOf() const { return *m_Class; }
        inline Value GetValue(size_t idx) const { return Value(m_Values[idx]);}
        inline void SetValue(size_t idx, const Value& value) { m_Values[idx]->Set(value); }
        
    public:
        Value GetValue(const std::string& name) const;
        void SetValue(const std::string& name, const Value& value);
        
    private:
        void BuildValueList();
        
    private:
        const ClassDef* m_Class;
        ValueContainer m_Values;
    };
}
#endif /* Object_hpp */
