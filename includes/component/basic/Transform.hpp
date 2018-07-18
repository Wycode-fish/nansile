//
//  Transform.hpp
//  bird
//
//  Created by 汪依尘 on 6/16/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Transform_hpp
#define Transform_hpp

#include <stdio.h>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

class Transform
{
public:
    Transform(glm::vec3 pos = glm::vec3(0.0f),
              glm::vec3 rot = glm::vec3(0.0f),
              glm::vec3 scale = glm::vec3(1.0f));
    ~Transform();

public:
    static      glm::vec3       Up;
public:
    void        Update();
    
public:
    inline      glm::vec3       GetPosition()  const            {return m_Position;}
    inline      glm::vec3       GetRotation()  const            {return m_Rotation;}
    inline      glm::vec3       GetScale()     const            {return m_Scale;}
    inline      void            SetPosition(glm::vec3 pos)      { m_Position = pos;}
    inline      void            SetRotation(glm::vec3 rot)      { m_Rotation = rot;}
    inline      void            SetScale(glm::vec3 scale)       { m_Scale = scale;}
    inline      glm::vec3       GetLocalPosition()              {return m_LocalPosition;}
    inline      glm::vec3       GetLocalRotation()              {return m_LocalRotation;}
    inline      glm::vec3       GetLocalScale()                 {return m_LocalScale;}
    inline      void            SetLocalPosition(glm::vec3 pos) { m_LocalPosition = pos;}
    inline      void            SetLocalRotation(glm::vec3 rot) { m_LocalRotation = rot;}
    inline      void            SetLocalScale(glm::vec3 scale)  { m_LocalScale = scale;}
    
public:
    inline      glm::vec3&      GetPositionRef()                {return m_Position;}
    inline      glm::vec3&      GetRotationRef()                {return m_Rotation;}
    inline      glm::vec3&      GetScaleRef()                   {return m_Scale;}
    
public:
    inline      glm::vec3       GetForward()                    {return glm::normalize(m_Rotation);}
    inline      glm::vec3       GetRight()                      {return glm::normalize(glm::cross(GetForward(), Up));}
    
private:
    glm::vec3   m_Position;
    glm::vec3   m_Rotation;
    glm::vec3   m_Scale;
    glm::vec3   m_LocalPosition;
    glm::vec3   m_LocalRotation;
    glm::vec3   m_LocalScale;
};
#endif /* Transform_hpp */
