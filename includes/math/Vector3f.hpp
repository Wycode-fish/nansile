//
//  Vector3f.hpp
//  bird
//
//  Created by 汪依尘 on 6/7/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Vector3f_hpp
#define Vector3f_hpp

#include <stdio.h>
#include <iostream>
#include <sstream>
#include "Vector2f.hpp"

namespace ml {
    
    class Vector4f;
    
    class Vector3f
    {
    private:
        template <int x, int y, int z>
        class m_Swizzle3
        {
        private:
            float val[3];
        public:
            Vector3f& operator=(const Vector3f& rhs)
            {
                val[x] = rhs.val[0];
                val[y] = rhs.val[1];
                val[z] = rhs.val[2];
                return *this;
            }
            operator Vector3f()
            {
                return Vector3f(val[x], val[y], val[z]);
            }
        };
        
        template <int a, int b>
        class m_Swizzle3To2
        {
        private:
            float val[3];
        public:
            Vector2f& operator=(const Vector2f& rhs)
            {
                val[a] = rhs.val[0];
                val[b] = rhs.val[1];
                return *this;
            }
            
            operator Vector2f()
            {
                return Vector2f(val[a], val[b]);
            }
        };
        
    public:
        union
        {
            struct
            {
                float x, y, z;
            };
            
            m_Swizzle3To2<0, 0> xx;
            m_Swizzle3To2<0, 1> xy;
            m_Swizzle3To2<0, 2> xz;
            
            m_Swizzle3To2<1, 0> yx;
            m_Swizzle3To2<1, 1> yy;
            m_Swizzle3To2<1, 2> yz;
            
            m_Swizzle3To2<2, 0> zx;
            m_Swizzle3To2<2, 1> zy;
            m_Swizzle3To2<2, 2> zz;
            
            m_Swizzle3<0, 0, 0> xxx;
            m_Swizzle3<1, 1, 1> yyy;
            m_Swizzle3<2, 2, 2> zzz;
            
            m_Swizzle3<0, 1, 2> xyz;
            m_Swizzle3<0, 2, 1> xzy;
            m_Swizzle3<1, 0, 2> yxz;
            m_Swizzle3<1, 2, 0> yzx;
            m_Swizzle3<2, 0, 1> zxy;
            m_Swizzle3<2, 1, 0> zyx;

            float val[3];
        };
    public:
        Vector3f();
        Vector3f(const float& v1, const float& v2, const float& v3);
        Vector3f(const Vector2f& v2, const float& v);
        Vector3f(const float& v, const Vector2f& v2);
        Vector3f(const float& v);
        Vector3f(const Vector3f& v3);
        Vector3f(const Vector4f& v4);
        ~Vector3f();
        
        float&      operator[] (const int& idx);
        float       operator[] (const int& idx) const;
        Vector3f&   operator= (const Vector3f& v3);
        Vector3f&   operator+=(const Vector3f& v3);
        Vector3f&   operator-=(const Vector3f& v3);
        Vector3f&   operator/=(const float& ratio);
        Vector3f&   operator*=(const float& scale);
        
        float*      ValuePtr();
    };
    
    std::ostream& operator<< ( std::ostream& output, const Vector3f& vec );
    Vector3f    operator+ (const Vector3f& a, const Vector3f& b);
    Vector3f    operator- (const Vector3f& vec);
    Vector3f    operator- (const Vector3f& a, const Vector3f& b);
    Vector3f    operator* (const Vector3f& vec, const float& scale);
    Vector3f    operator* (const float& scale, const Vector3f& vec);
    Vector3f    operator* (const Vector3f& a, const Vector3f& b);
    Vector3f    operator/ (const Vector3f& vec, const float& scale);
    
}


#endif /* Vector3f_hpp */
