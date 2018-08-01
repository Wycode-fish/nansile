//
//  Value.hpp
//  bird
//
//  Created by 汪依尘 on 7/30/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Value_hpp
#define Value_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>

namespace rttr {
    
    class Value;
    
    // ---------- BaseValue; ----------
    class BaseValue
    {
    public:
        virtual BaseValue* Clone() const = 0;
        virtual inline ~BaseValue() {};
        virtual std::string AsString() const = 0;
        virtual void Set(const Value& value) = 0;
    };
    
    template <typename T>
    class TypedValue : public BaseValue
    {
    public:
        virtual inline ~TypedValue() {}
        virtual operator T() const = 0;
        
    };
    
    
    // ---------- Value; ----------
    class Value
    {
    public:
        explicit Value(BaseValue* = nullptr);
        Value(const Value& value);
        ~Value();
        
        template<typename T>
        T Get() const
        {
            if (m_Value != nullptr)
            {
                const TypedValue<T>& res = dynamic_cast<const TypedValue<T>&>(*m_Value);
                return res;
            }
            else
            {
                return T();
            }
        }
        
        Value& operator=(const Value& rhs);
        
        std::string AsString();
    private:
        BaseValue* m_Value;
    };
    
    
    // ---------- RealValue; ----------
    template<typename T>
    class RealValue: public TypedValue<T>
    {
    public:
        RealValue( T val )
        : m_Value(val)
        {}
        
        ~RealValue()
        {}
        
        RealValue* Clone() const
        {
            return new RealValue(m_Value);
        }
        
        std::string AsString() const
        {
            std::ostringstream os;
            os << m_Value;
            return os.str();
        }
        
        void Set(const Value& value)
        {
            m_Value = value.Get<T>();
        }
        
        operator T() const
        {
            return m_Value;
        }
        
    private:
        T m_Value;
    };
    
    template<>
    class RealValue<std::string>: public TypedValue<std::string>, public std::string
    {
    public:
        RealValue( std::string val )
        : std::string(val)
        {}
        
        RealValue( const char* val)
        : std::string(val)
        {}
        
        ~RealValue()
        {}
        
        RealValue* Clone() const
        {
            return new RealValue(*this);
        }
        
        std::string AsString() const
        {
            return static_cast<std::string>(*this);
        }
        
        void Set(const Value& value)
        {
            std::string::operator = ( value.Get<std::string>() );
        }
        
        operator std::string() const
        {
            return *this;
        }
    };

}

#endif /* Value_hpp */
