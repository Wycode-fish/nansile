//
//  Operations.hpp
//  bird
//
//  Created by 汪依尘 on 8/8/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Operations_hpp
#define Operations_hpp

#include <stdio.h>
#include <cmath>
#include "Matrix4f.hpp"

namespace ml {
    
    // ---------- Number ----------
    float ToRadian(const float& degree);
    
    
    // ---------- Vector ----------
    float       Length(const Vector3f& vec);
    Vector3f    Normalize(const Vector3f& vec);
    float       Dot (const Vector3f& a, const Vector3f& b);
    Vector3f    Cross (const Vector3f& a, const Vector3f& b);
    float*      ValuePtr(Vector3f& vec);
    
    // ---------- Matrix ----------
    Matrix4f    Translate(const Matrix4f& baseMat,
                          const Vector3f& translateVec);
    
    Matrix4f    Rotate(const Matrix4f& baseMat,
                       const float& angle,
                       const Vector3f& axis);
    
    Matrix4f    Scale(const Matrix4f& baseMat,
                       const Vector3f& scale);
        
    Matrix4f    Perspective(const float& fov,
                            const float& width2Height,
                            const float& nearClip,
                            const float& farClip);
    
    Matrix4f    Ortho(const float& left,
                      const float& right,
                      const float& up,
                      const float& down,
                      const float& near,
                      const float& far);
    
    Matrix4f    LookAt(const Vector3f& eye,
                       const Vector3f& center,
                       const Vector3f& up);
}

#endif /* Operations_hpp */
