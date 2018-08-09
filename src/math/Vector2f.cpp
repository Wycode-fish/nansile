//
//  Vector2f.cpp
//  bird
//
//  Created by 汪依尘 on 8/7/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "Vector2f.hpp"

namespace ml {
    
    Vector2f::Vector2f()
    : x(0.0f), y(0.0f)
    {}
    
    Vector2f::Vector2f(const float& v1, const float& v2)
    : x(v1), y(v2)
    {}
    
    Vector2f::Vector2f(const float& v)
    : x(v), y(v)
    {}
    
    
    Vector2f::Vector2f(const Vector2f& v2)
    : x(v2.x), y(v2.y)
    {}
    
    Vector2f::~Vector2f()
    {
        // TODO: handle
    }
    
    float& Vector2f::operator[](const int& idx)
    {
        return val[idx];
    }
    
    float Vector2f::operator[](const int& idx) const
    {
        return val[idx];
    }
    
    Vector2f& Vector2f::operator=(const Vector2f& v2)
    {
        x = v2.x;
        y = v2.y;
        return *this;
    }
    
    Vector2f& Vector2f::operator+=(const Vector2f& v3)
    {
        x += v3.x;
        y += v3.y;
        return *this;
    }
    
    Vector2f& Vector2f::operator-=(const Vector2f& v3)
    {
        x -= v3.x;
        y -= v3.y;
        return *this;
    }
    
    Vector2f& Vector2f::operator/=(const float& ratio)
    {
        x /= ratio;
        y /= ratio;
        return *this;
    }
    
    Vector2f& Vector2f::operator*=(const float& scale)
    {
        x *= scale;
        y *= scale;
        return *this;
    }
    
    float*  Vector2f::ValuePtr()
    {
        return val;
    }
    
    std::ostream& operator<< ( std::ostream& output, const Vector2f& vec )
    {
        return output << "( " << vec.x << ", " << vec.y << " )\n";
    }
    
    Vector2f operator+(const Vector2f& a, const Vector2f& b)
    {
        Vector2f res;
        res.x = a.x + b.x;
        res.y = a.y + b.y;
        return res;
    }
    
    Vector2f operator- (const Vector2f& a, const Vector2f& b)
    {
        Vector2f res;
        res.x = a.x - b.x;
        res.y = a.y - b.y;
        return res;
    }
    
    Vector2f operator* (const Vector2f& vec, const float& scale)
    {
        Vector2f res;
        res.x = vec.x * scale;
        res.y = vec.y * scale;
        return res;
    }
    
    Vector2f operator/ (const Vector2f& vec, const float& scale)
    {
        Vector2f res;
        res.x = vec.x / scale;
        res.y = vec.y / scale;
        return res;
    }
    
    float Dot (const Vector2f& a, const Vector2f& b)
    {
        float res = 0;
        res += a.x * b.x;
        res += a.y * b.y;
        return res;
    }
    
    
}
