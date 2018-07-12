//
//  Transform.cpp
//  bird
//
//  Created by 汪依尘 on 6/16/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "Transform.hpp"

glm::vec3 Transform::Up = glm::vec3(0.f, 1.f, 0.f);

Transform::Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
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
