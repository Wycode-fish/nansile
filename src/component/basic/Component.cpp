//
//  Component.cpp
//  bird
//
//  Created by 汪依尘 on 6/16/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "Component.hpp"

COMPONENT_GENERATORS Component::m_Generators = { std::vector<const char*>(), std::vector<std::function<Component*()> >() };

const char* const Component::AvailableComponents[] =
{
    "Mesh Renderer",
    "Collider",
    "Lua Script"
};

int Component::AvailableComponentsCount = 3;

Component::Component(std::string tag)
: m_Tag(tag), m_GameObject(NULL)
{
    
}

Component::Component(GameObject* gameObject)
: m_Tag("default"), m_GameObject(gameObject)
{
    
}

Component::Component(GameObject* gameObject, const std::string& tag)
: m_Tag(tag), m_GameObject(gameObject)
{
    
}

Component::~Component()
{
    // TODO: nothing yet.
}

void Component::Update()
{
    
}
