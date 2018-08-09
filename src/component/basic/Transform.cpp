//
//  Transform.cpp
//  bird
//
//  Created by 汪依尘 on 6/16/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "Transform.hpp"

ml::Vector3f Transform::Up = ml::Vector3f(0.f, 1.f, 0.f);

Transform::Transform(ml::Vector3f pos, ml::Vector3f rot, ml::Vector3f scale)
: m_Position(pos), m_Rotation(rot), m_Scale(scale)
{
    // TODO: nothing yet.
}

Transform::~Transform()
{
    // TODO: nothing yet.
}

void Transform::Update()
{
    
}
