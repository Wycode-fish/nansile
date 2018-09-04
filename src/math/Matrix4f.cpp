//
//  Matrix4f.cpp
//  bird
//
//  Created by 汪依尘 on 6/7/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "Matrix4f.hpp"
#include "Vector3f.hpp"
#include "ml.h"
#include <cmath>
#include <sstream>

namespace ml {
    
    Vector4f::Vector4f()
    : x(0.0f), y(0.0f), z(0.0f), w(1.0f)
    {}
    
    Vector4f::Vector4f(const Vector3f& vec3, const float& rhs_w)
    : x(vec3.x), y(vec3.y), z(vec3.z), w(rhs_w)
    {}
    
    Vector4f::Vector4f( const float& rhs_x, const float& rhs_y, const float& rhs_z, const float& rhs_w)
    : x(rhs_x), y(rhs_y), z(rhs_z), w(rhs_w)
    {}
    
    float& Vector4f::operator[](const int& idx)
    {
        return val[idx];
    }
    
    float Vector4f::operator[](const int& idx) const
    {
        return val[idx];
    }
    
    Vector4f& Vector4f::operator=(const Vector4f& v3)
    {
        x = v3.x;
        y = v3.y;
        z = v3.z;
        w = v3.w;
        return *this;
    }
    
    Vector4f& Vector4f::operator+=(const Vector4f& v3)
    {
        x += v3.x;
        y += v3.y;
        z += v3.z;
        w += v3.w;
        return *this;
    }
    
    Vector4f& Vector4f::operator-=(const Vector4f& v3)
    {
        x -= v3.x;
        y -= v3.y;
        z -= v3.z;
        w -= v3.w;
        return *this;
    }
    
    Vector4f& Vector4f::operator/=(const float& ratio)
    {
        x /= ratio;
        y /= ratio;
        z /= ratio;
        w /= ratio;
        return *this;
    }
    
    Vector4f& Vector4f::operator*=(const float& scale)
    {
        x *= scale;
        y *= scale;
        z *= scale;
        z *= scale;
        return *this;
    }
    
    std::string Vector4f::ToString() const
    {
        std::ostringstream os;
        os << "( " << x << ", " << y << ", " << z << ", " << w << " )";
        return os.str();
    }
    
    std::ostream& operator<< ( std::ostream& output, const Vector4f& vec )
    {
        return output << "( " << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << " )\n";
    }
    
    Vector4f operator+(const Vector4f& a, const Vector4f& b)
    {
        Vector4f res;
        res.x = a.x + b.x;
        res.y = a.y + b.y;
        res.z = a.z + b.z;
        res.w = a.w + b.w;
        return res;
    }
    
    Vector4f operator- (const Vector4f& a, const Vector4f& b)
    {
        Vector4f res;
        res.x = a.x - b.x;
        res.y = a.y - b.y;
        res.z = a.z - b.z;
        res.w = a.w - b.w;
        return res;
    }
    
    Vector4f operator- (const Vector4f& vec)
    {
        return vec * (-1.0f);
    }

    Vector4f operator* (const Vector4f& vec, const float& scale)
    {
        Vector4f res;
        res.x = vec.x * scale;
        res.y = vec.y * scale;
        res.z = vec.z * scale;
        res.w = vec.w * scale;
        return res;
    }
    
    Vector4f operator/ (const Vector4f& vec, const float& scale)
    {
        Vector4f res;
        res.x = vec.x / scale;
        res.y = vec.y / scale;
        res.z = vec.z / scale;
        res.w = vec.w / scale;
        return res;
    }
    
    float Dot (const Vector4f& a, const Vector4f& b)
    {
        float res = 0;
        res += a.x * b.x;
        res += a.y * b.y;
        res += a.z * b.z;
        res += a.w * b.w;
        return res;
    }
    
    Matrix3f::Matrix3f()
    {
        for (int i=0; i<9; i++)
        {
            val[i] = 0.0f;
        }
    }
    
    Matrix3f::Matrix3f(const float& diagnal)
    {
        for (int i=0; i<9; i++)
        {
            val[i] = 0.0f;
        }
        val[0] = 1.0f;
        val[4] = 1.0f;
        val[8] = 1.0f;
    }
    
    Matrix3f::Matrix3f(const Matrix3f& mat3)
    {
        this->rows[0] = mat3.rows[0];
        this->rows[1] = mat3.rows[1];
        this->rows[2] = mat3.rows[2];
    }
    
    Matrix3f::Matrix3f(const Matrix4f& mat4)
    {
        this->rows[0] = Vector3f(mat4.rows[0]);
        this->rows[1] = Vector3f(mat4.rows[1]);
        this->rows[2] = Vector3f(mat4.rows[2]);
    }
    
    Matrix3f::~Matrix3f()
    {
        // TODO: nothing yet.
    }
    
    Vector3f& Matrix3f::operator[](const int &idx)
    {
        return rows[idx];
    }
    
    Vector3f Matrix3f::operator[](const int &idx) const
    {
        return rows[idx];
    }
    
    Matrix3f& Matrix3f::operator=(const Matrix3f& mat3)
    {
        for (int i=0; i<9; i++)
        {
            val[i] = mat3.val[i];
        }
        return *this;
    }
    
    Matrix3f Matrix3f::Identity()
    {
        Matrix3f res;
        res.val[0+0*3] = 1;
        res.val[1+1*3] = 1;
        res.val[2+2*3] = 1;
        
        return res;
    }
    
    Matrix3f::operator Matrix4f() const
    {
        Matrix4f res;
        res.rows[0] = Vector4f(this->rows[0], 0.0f);
        res.rows[1] = Vector4f(this->rows[1], 0.0f);
        res.rows[2] = Vector4f(this->rows[2], 0.0f);
        res.rows[3] = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
        return res;
    }
    
    
    Matrix4f::Matrix4f()
    {
        for (int i=0; i<16; i++)
        {
            val[i] = 0.0f;
        }
    }
    
    Matrix4f::Matrix4f(const float& diagnal)
    {
        for (int i=0; i<16; i++)
        {
            val[i] = 0.0f;
        }
        val[0] = 1.0f;
        val[5] = 1.0f;
        val[10] = 1.0f;
        val[15] = 1.0f;
    }

    Matrix4f::Matrix4f(const Matrix3f& mat3)
    {
        rows[0] = Vector4f(mat3.rows[0], 0.0f);
        rows[1] = Vector4f(mat3.rows[1], 0.0f);
        rows[2] = Vector4f(mat3.rows[2], 0.0f);
        rows[3] = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    Matrix4f::~Matrix4f()
    {
        // TODO: nothing yet.
    }
    
    Vector4f& Matrix4f::operator[](const int &idx)
    {
        return rows[idx];
    }
    
    Vector4f Matrix4f::operator[](const int &idx) const
    {
        return rows[idx];
    }
    
    Matrix4f& Matrix4f::operator=(const Matrix4f& mat4)
    {
        for (int i=0; i<16; i++)
        {
            val[i] = mat4.val[i];
        }
        return *this;
    }
    
    Matrix4f::operator Matrix3f() const
    {
        Matrix3f res;
        Vector3f row1(this->rows[0]);
        res.rows[0] = this->rows[0];
        res.rows[1] = this->rows[1];
        res.rows[2] = this->rows[2];
        return res;
    }
    
    Matrix4f Matrix4f::Identity()
    {
        Matrix4f res;
        res.val[0+0*4] = 1;
        res.val[1+1*4] = 1;
        res.val[2+2*4] = 1;
        res.val[3+3*4] = 1;
        
        return res;
    }
    
    Matrix4f Matrix4f::Translate(const Vector3f& v3)
    {
        Matrix4f res = Identity();
        res.val[0+3*4] = v3[0];
        res.val[1+3*4] = v3[1];
        res.val[2+3*4] = v3[2];
        return res;
    }
    
    Matrix4f Matrix4f::Rotation(const float& degree)    // only along z-axis
    {
        float rad = ToRadian(degree);
        float cosine = cos(rad);
        float sine = sin(rad);
        
        Matrix4f res = Identity();
        res.val[0+0*4] = cosine;
        res.val[1+0*4] = sine;
        res.val[0+1*4] = -1* sine;
        res.val[1+1*4] = cosine;
        
        return res;
    }
    
    Matrix4f Matrix4f::Scaling(const Vector3f& v3)
    {
        Matrix4f res = Identity();
        res.val[0+0*4] = v3[0];
        res.val[1+1*4] = v3[1];
        res.val[2+2*4] = v3[2];
        return res;
    }
    
    Matrix4f operator * (const Matrix4f& mat1, const Matrix4f& mat2)
    {
        Matrix4f res;
        for (int i=0; i<4; i++)
        {
            Vector4f row = mat2[i];
            for (int j=0; j<4; j++)
            {
                Vector4f col(mat1[0][j], mat1[1][j], mat1[2][j], mat1[3][j]);
                res.val[j + i*4] = Dot(row, col);
            }
        }
        return res;
    }
    
    Matrix4f operator * (const Matrix4f& mat, const float& scale)
    {
        Matrix4f res;
        for (int i=0; i<4; i++)
        {
            for (int j=0; j<4; j++)
            {
                res.val[j + 4 * i] = mat[i][j] * scale;
            }
        }
        return res;
    }
    
    Vector4f operator * (const Matrix4f& mat, const Vector4f& vec)
    {
        Vector4f res;
        for (int i=0; i<4; i++)
        {
            res.val[i] = Dot( Vector4f( mat.val[i + 0 * 4],
                                        mat.val[i + 1 * 4],
                                        mat.val[i + 2 * 4],
                                        mat.val[i + 3 * 4]),
                              vec);
        }
        return res;
    }

    Matrix4f operator / (const Matrix4f& mat, const float& scale)
    {
        Matrix4f res;
        for (int i=0; i<4; i++)
        {
            for (int j=0; j<4; j++)
            {
                res.val[j + 4 * i] = mat[i][j] / scale;
            }
        }
        return res;
    }
    
    std::ostream& operator<< ( std::ostream& output, const Matrix4f& mat )
    {
        return output << mat[0] << mat[1] << mat[2] << mat[3] << "\n";
    }
    
}
