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
#include "Operations.hpp"

class Transform
{
public:
    Transform(ml::Vector3f pos = ml::Vector3f(0.0f),
              ml::Vector3f rot = ml::Vector3f(0.0f),
              ml::Vector3f scale = ml::Vector3f(1.0f));
    ~Transform();

public:
    static      ml::Vector3f       Up;
public:
    void        Update();
    
public:
    inline      ml::Vector3f       GetPosition()  const            {return m_Position;}
    inline      ml::Vector3f       GetRotation()  const            {return m_Rotation;}
    inline      ml::Vector3f       GetScale()     const            {return m_Scale;}
    inline      void            SetPosition(ml::Vector3f pos)      { m_Position = pos;}
    inline      void            SetRotation(ml::Vector3f rot)      { m_Rotation = rot;}
    inline      void            SetScale(ml::Vector3f scale)       { m_Scale = scale;}
    inline      ml::Vector3f       GetLocalPosition()              {return m_LocalPosition;}
    inline      ml::Vector3f       GetLocalRotation()              {return m_LocalRotation;}
    inline      ml::Vector3f       GetLocalScale()                 {return m_LocalScale;}
    inline      void            SetLocalPosition(ml::Vector3f pos) { m_LocalPosition = pos;}
    inline      void            SetLocalRotation(ml::Vector3f rot) { m_LocalRotation = rot;}
    inline      void            SetLocalScale(ml::Vector3f scale)  { m_LocalScale = scale;}
    
public:
    inline      ml::Vector3f&      GetPositionRef()                {return m_Position;}
    inline      ml::Vector3f&      GetRotationRef()                {return m_Rotation;}
    inline      ml::Vector3f&      GetScaleRef()                   {return m_Scale;}
    
public:
    inline      ml::Vector3f       GetForward()     {return ml::Normalize(m_Rotation);}
    inline      ml::Vector3f       GetRight()       {return ml::Normalize(ml::Cross(GetForward(), Up));}
    
private:
    ml::Vector3f   m_Position;
    ml::Vector3f   m_Rotation;
    ml::Vector3f   m_Scale;
    ml::Vector3f   m_LocalPosition;
    ml::Vector3f   m_LocalRotation;
    ml::Vector3f   m_LocalScale;
};
#endif /* Transform_hpp */
