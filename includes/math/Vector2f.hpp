//
//  Vector2f.hpp
//  bird
//
//  Created by 汪依尘 on 8/7/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Vector2f_hpp
#define Vector2f_hpp

#include <stdio.h>
#include <iostream>

namespace ml {
    
    class Vector2f
    {
    private:
        template <int x, int y>
        class m_Swizzle2
        {
        private:
            float val[3];
        public:
            Vector2f& operator=(const Vector2f& rhs)
            {
                val[x] = rhs.x;
                val[y] = rhs.y;
                return *this;
            }
            operator Vector2f()
            {
                return Vector2f(val[x], val[y]);
            }
        };
        
    public:
        union
        {
            struct
            {
                float x, y;
            };
            
            struct
            {
                float xx, yy;
            };
            
            m_Swizzle2<0, 1> xy;
            m_Swizzle2<1, 0> yx;
            
            float val[2];
        };
    public:
        Vector2f();
        Vector2f(const float& v1, const float& v2);
        Vector2f(const float& v);
        Vector2f(const Vector2f& v2);
        ~Vector2f();
        float&      operator[] (const int& idx);
        float       operator[] (const int& idx) const;
        Vector2f&   operator= (const Vector2f& v2);
        Vector2f&   operator+=(const Vector2f& v2);
        Vector2f&   operator-=(const Vector2f& v2);
        Vector2f&   operator/=(const float& ratio);
        Vector2f&   operator*=(const float& scale);
        
        float* ValuePtr();
    };
    
    std::ostream& operator<< ( std::ostream& output, const Vector2f& vec );
    Vector2f    operator+ (const Vector2f& a, const Vector2f& b);
    Vector2f    operator- (const Vector2f& a, const Vector2f& b);
    Vector2f    operator* (const Vector2f& vec, const float& scale);
    Vector2f    operator/ (const Vector2f& vec, const float& scale);
    
    float       Dot (const Vector2f& a, const Vector2f& b);
}


#endif /* Vector2f_hpp */
