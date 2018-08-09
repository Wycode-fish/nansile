//
//  Matrix4f.hpp
//  bird
//
//  Created by 汪依尘 on 6/7/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Matrix4f_hpp
#define Matrix4f_hpp

#include <stdio.h>
#include "Vector3f.hpp"
#include <string>

namespace ml {
    
    class Vector4f
    {
    private:
        template <int a, int b, int c>
        class m_Swizzle4To3
        {
        private:
            float val[4];
        public:
            Vector3f& operator=(const Vector3f& rhs)
            {
                val[a] = rhs.val[0];
                val[b] = rhs.val[1];
                val[c] = rhs.val[2];
                return *this;
            }
            operator Vector3f()
            {
                return Vector3f(val[a], val[b], val[c]);
            }
        };
    public:
        union
        {
            struct
            {
                float x, y, z, w;
            };
            
            m_Swizzle4To3<0, 1, 2> xyz;
            
            float val[4];
        };
    public:
        Vector4f();
        explicit Vector4f( const Vector3f& vec3, const float& w = 1.0f);
        Vector4f( const float& x, const float& y, const float& z, const float& w);

    public:
        float&      operator[] (const int& idx);
        float       operator[](const int& idx) const;
        Vector4f&   operator= (const Vector4f& v4);
        Vector4f&   operator+=(const Vector4f& v4);
        Vector4f&   operator-=(const Vector4f& v4);
        Vector4f&   operator/=(const float& ratio);
        Vector4f&   operator*=(const float& scale);
        std::string ToString() const;
    };
    
    std::ostream& operator<< ( std::ostream& output, const Vector4f& vec );
    Vector4f    operator+ (const Vector4f& a, const Vector4f& b);
    Vector4f    operator- (const Vector4f& a, const Vector4f& b);
    Vector4f    operator- (const Vector4f& vec);
    Vector4f    operator* (const Vector4f& vec, const float& scale);
    Vector4f    operator/ (const Vector4f& vec, const float& scale);
    float       Dot (const Vector4f& a, const Vector4f& b);
    
    class Matrix4f;
    
    class Matrix3f
    {
    public:
        union
        {
            Vector3f rows[3];
            float val[12];
        };
    public:
        Matrix3f();
        Matrix3f(const float& diagnal);
        Matrix3f(const Matrix3f& mat3);
        Matrix3f(const Matrix4f& mat4);
        ~Matrix3f();
        Vector3f&   operator[](const int& idx);
        Vector3f    operator[](const int& idx) const;
        Matrix3f&   operator=(const Matrix3f& mat3);
        operator    Matrix4f() const;
    public:
        static Matrix3f Identity();
    };
    
    class Matrix4f
    {
    public:
        union
        {
            Vector4f rows[4];
            float val[16];
        };
    public:
        Matrix4f();
        Matrix4f(const float& diagnal);
        Matrix4f(const Matrix3f& mat3);
        ~Matrix4f();
        Vector4f&   operator[](const int& idx);
        Vector4f    operator[](const int& idx) const;
        Matrix4f&   operator=(const Matrix4f& mat4);
        operator    Matrix3f() const;
    public:
        static Matrix4f Identity();
        static Matrix4f Translate(const Vector3f& v3);
        static Matrix4f Rotation(const float& degree);
        static Matrix4f Scaling(const Vector3f& v3);
    };
    
    Matrix4f operator * (const Matrix4f& mat1, const Matrix4f& mat2);
    Matrix4f operator * (const Matrix4f& mat, const float& scale);
    Vector4f operator * (const Matrix4f& mat, const Vector4f& vec);
    Matrix4f operator / (const Matrix4f& mat, const float& scale);
    std::ostream& operator<< ( std::ostream& output, const Matrix4f& vec );

}


#endif /* Matrix4f_hpp */
