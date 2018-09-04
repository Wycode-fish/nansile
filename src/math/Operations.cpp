//
//  Operations.cpp
//  bird
//
//  Created by 汪依尘 on 8/8/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "Operations.hpp"
#include <math.h>

namespace ml {
    
    // ---------- Number ----------
    float ToRadian(const float& degree)
    {
        return degree * 3.141593f / 180.0f;
    }
    
    int Rand(const int& start, const int& end)
    {
        return rand() % (end + 1 - start) + start;
    }
    
    
    // ---------- Vector ----------
    float Length(const Vector3f& vec)
    {
        return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    }
    
    Vector3f Normalize(const Vector3f& vec)
    {
        float len = Length(vec);
        Vector3f res( vec.x / len, vec.y / len, vec.z / len );
        return res;
    }
    
    float Dot (const Vector3f& a, const Vector3f& b)
    {
        float res = 0;
        res += a.x * b.x;
        res += a.y * b.y;
        res += a.z * b.z;
        return res;
    }
    
    Vector3f Cross (const Vector3f& a, const Vector3f& b)
    {
        Vector3f res;
        res.x = a.y * b.z - a.z * b.y;
        res.y = a.z * b.x - a.x * b.z;
        res.z = a.x * b.y - a.y * b.x;
        return res;
    }
    
    float* ValuePtr(Vector3f& vec)
    {
        return vec.ValuePtr();
    }

    
    
    // ---------- Matrix ----------
    Matrix4f Translate(const Matrix4f& baseMat, const Vector3f& translateVec)
    {
        Matrix4f res( baseMat );
        res.val[0+3*4] = translateVec[0];
        res.val[1+3*4] = translateVec[1];
        res.val[2+3*4] = translateVec[2];
        return res;
        return res;
    }
    
    Matrix4f Rotate(const Matrix4f& baseMat, const float& angle, const Vector3f& axis)
    {
        Matrix4f res;
        
        Vector3f n = Normalize(axis);
        float cosine = cos(angle);
        float sine = sin(angle);
        
        float OneMinusCosine = 1 - cosine;
        
        res.val[0 + 0 * 4] = n.x * n.x * OneMinusCosine + cosine;
        res.val[1 + 0 * 4] = n.x * n.y * OneMinusCosine + n.z * sine;
        res.val[2 + 0 * 4] = n.x * n.z * OneMinusCosine - n.y * sine;
        
        res.val[0 + 1 * 4] = n.y * n.x * OneMinusCosine - n.z * sine;
        res.val[1 + 1 * 4] = n.y * n.y * OneMinusCosine + cosine;
        res.val[2 + 1 * 4] = n.y * n.z * OneMinusCosine + n.x * sine;
        
        res.val[0 + 2 * 4] = n.z * n.x * OneMinusCosine + n.y * sine;;
        res.val[1 + 2 * 4] = n.z * n.y * OneMinusCosine - n.x * sine;
        res.val[2 + 2 * 4] = n.z * n.z * OneMinusCosine + cosine;

        Matrix4f result;
        result[0] = baseMat[0] * res[0][0] + baseMat[1] * res[0][1] + baseMat[2] * res[0][2];
        result[1] = baseMat[0] * res[1][0] + baseMat[1] * res[1][1] + baseMat[2] * res[1][2];
        result[2] = baseMat[0] * res[2][0] + baseMat[1] * res[2][1] + baseMat[2] * res[2][2];
        result[3] = baseMat[3];

        return result;
    }
    
    Matrix4f Scale(const Matrix4f& baseMat, const Vector3f& scale)
    {
        Matrix4f res;
        res[0] = baseMat[0] * scale.x;
        res[1] = baseMat[1] * scale.y;
        res[2] = baseMat[2] * scale.z;
        res[3] = baseMat[3];
        return res;
    }
    
    Matrix4f    Perspective(const float& fov,
                            const float& width2Height,
                            const float& nearClip,
                            const float& farClip)
    {
        Matrix4f res;
        float t = tan( fov/2.0f ) * nearClip;
        float r = t * width2Height;
        float l = -1.0f * r;
        float b = -1.0f * t;
        
        res.val[0 + 0 * 4] = 2.f * nearClip / (r - l);
        res.val[2 + 0 * 4] = (r + l) / (r - l);

        res.val[1 + 1 * 4] = 2.f * nearClip / (t - b);
        res.val[2 + 1 * 4] = (t + b) / (t - b);
        
        res.val[2 + 2 * 4] = (-1.0f) * (farClip + nearClip) / (farClip - nearClip);
        res.val[2 + 3 * 4] = (-2.0f) * farClip * nearClip / (farClip - nearClip);
        
        res.val[3 + 2 * 4] = -1.0f;
        
        return res;
    }
    
    Matrix4f    Ortho(const float& left,
                      const float& right,
                      const float& up,
                      const float& down,
                      const float& near,
                      const float& far)
    {
        Matrix4f res = Matrix4f::Identity();
        res.val[0+0*4] = 2.0f/(right-left);
        res.val[1+1*4] = 2.0f/(up-down);
        res.val[2+2*4] = 2.0f/(near-far);
        res.val[0+3*4] = (left+right)/(right-left);
        res.val[1+3*4] = (up+down)/(up-down);
        res.val[2+3*4] = (near+far)/(near-far);
        return res;
    }
    
    Matrix4f    LookAt(const Vector3f& eye,
                       const Vector3f& center,
                       const Vector3f& up)
    {
        Vector3f Front = Normalize(center - eye);
        Vector3f Side = Normalize(Cross(Front, up));
        Vector3f Up = Cross(Side, Front);
        
        Matrix4f res = Matrix4f::Identity();
        res.val[0 + 0 * 4] = Side.x;
        res.val[0 + 1 * 4] = Side.y;
        res.val[0 + 2 * 4] = Side.z;
        
        res.val[1 + 0 * 4] = Up.x;
        res.val[1 + 1 * 4] = Up.y;
        res.val[1 + 2 * 4] = Up.z;
        
        res.val[2 + 0 * 4] = -Front.x;
        res.val[2 + 1 * 4] = -Front.y;
        res.val[2 + 2 * 4] = -Front.z;
        
        res.val[0 + 3 * 4] = -Dot(Side, eye);
        res.val[1 + 3 * 4] = -Dot(Up, eye);
        res.val[2 + 3 * 4] = Dot(Front, eye);
        
        return res;
    }
}
