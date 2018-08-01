//
//  Type.hpp
//  bird
//
//  Created by 汪依尘 on 7/30/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Type_hpp
#define Type_hpp

#include <stdio.h>
#include <vector>

namespace rttr {
    
    class BaseValue;
    
    class Type
    {
    public:
        enum TypeT
        {
            intT, floatT, unsignedT, stringT
        };
        explicit Type(TypeT typeId);
        
    public:
        inline TypeT GetType() const {return m_TypeId;}
        BaseValue* NewValue() const;
        
    private:
        TypeT m_TypeId;
        static std::vector<BaseValue*> m_Prototypes;
    };
    
}


#endif /* Type_hpp */
