//
//  Vector3f.cpp
//  bird
//
//  Created by 汪依尘 on 6/7/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "Vector3f.hpp"
#include "Matrix4f.hpp"

namespace ml {
    
    Vector3f::Vector3f()
    : x(0.0f), y(0.0f), z(0.0f)
    {}
    
    Vector3f::Vector3f(const float& v1, const float& v2, const float& v3)
    : x(v1), y(v2), z(v3)
    {}
    
    Vector3f::Vector3f(const float& v)
    : x(v), y(v), z(v)
    {}
    
    Vector3f::Vector3f(const Vector2f& v2, const float& v)
    : x(v2.x), y(v2.y), z(v)
    {}
    
    Vector3f::Vector3f(const float& v, const Vector2f& v2)
    : x(v), y(v2.x), z(v2.y)
    {}
    
    Vector3f::Vector3f(const Vector3f& v3)
    : x(v3.x), y(v3.y), z(v3.z)
    {}
    
    Vector3f::Vector3f(const Vector4f& v4)
    : x(v4.x), y(v4.y), z(v4.z)
    {}
    
    Vector3f::~Vector3f()
    {
        // TODO: handle
    }
    
    float* Vector3f::ValuePtr()
    {
        return val;
    }
    
    float& Vector3f::operator[](const int& idx)
    {
        return val[idx];
    }
    
    float Vector3f::operator[](const int& idx) const
    {
        return val[idx];
    }
    
    Vector3f& Vector3f::operator=(const Vector3f& v3)
    {
        x = v3.x;
        y = v3.y;
        z = v3.z;
        return *this;
    }
    
    Vector3f& Vector3f::operator+=(const Vector3f& v3)
    {
        x += v3.x;
        y += v3.y;
        z += v3.z;
        return *this;
    }
    
    Vector3f& Vector3f::operator-=(const Vector3f& v3)
    {
        x -= v3.x;
        y -= v3.y;
        z -= v3.z;
        return *this;
    }
    
    Vector3f& Vector3f::operator/=(const float& ratio)
    {
        x /= ratio;
        y /= ratio;
        z /= ratio;
        return *this;
    }
    
    Vector3f& Vector3f::operator*=(const float& scale)
    {
        x *= scale;
        y *= scale;
        z *= scale;
        return *this;
    }
    
    std::ostream& operator<< ( std::ostream& output, const Vector3f& vec )
    {
        return output << "( " << vec.x << ", " << vec.y << ", " << vec.z << " )\n";
    }
    
    Vector3f operator+(const Vector3f& a, const Vector3f& b)
    {
        Vector3f res;
        res.x = a.x + b.x;
        res.y = a.y + b.y;
        res.z = a.z + b.z;
        return res;
    }
    
    Vector3f operator- (const Vector3f& a, const Vector3f& b)
    {
        Vector3f res;
        res.x = a.x - b.x;
        res.y = a.y - b.y;
        res.z = a.z - b.z;
        return res;
    }
    
    Vector3f operator- (const Vector3f& vec)
    {
        return vec * (-1.0f);
    }

    
    Vector3f operator* (const Vector3f& vec, const float& scale)
    {
        Vector3f res;
        res.x = vec.x * scale;
        res.y = vec.y * scale;
        res.z = vec.z * scale;
        return res;
    }
    
    Vector3f operator* (const float& scale, const Vector3f& vec)
    {
        Vector3f res;
        res.x = vec.x * scale;
        res.y = vec.y * scale;
        res.z = vec.z * scale;
        return res;
    }
    
    Vector3f operator/ (const Vector3f& vec, const float& scale)
    {
        Vector3f res;
        res.x = vec.x / scale;
        res.y = vec.y / scale;
        res.z = vec.z / scale;
        return res;
    }
    
    Vector3f operator* (const Vector3f& a, const Vector3f& b)
    {
        Vector3f res;
        res.x = a.x * b.x;
        res.y = a.y * b.y;
        res.z = a.z * b.z;
        return res;
    }

}
