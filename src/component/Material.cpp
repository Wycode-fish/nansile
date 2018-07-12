//
//  Material.cpp
//  bird
//
//  Created by 汪依尘 on 7/3/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "Material.hpp"

glm::vec3 MaterialAttribs::Default_Ambient = glm::vec3(0.3, 0.3, 0.31);
glm::vec3 MaterialAttribs::Default_Diffuse = glm::vec3(0.3, 0.3, 0.31);
glm::vec3 MaterialAttribs::Default_Specular = glm::vec3(0.5, 0.5, 0.5);
float MaterialAttribs::Default_Shiness = 128.0f;

MaterialAttribs::MaterialAttribs(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shiness)
: m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular), m_Shiness(shiness)
{
}

void MaterialAttribs::ResetMatAttribs()
{
    m_Ambient = Default_Ambient;
    m_Diffuse = Default_Diffuse;
    m_Specular = Default_Specular;
    m_Shiness = Default_Shiness;
}

void MaterialAttribs::Brighter()
{
    m_Ambient.x++;
    m_Ambient.x = (m_Ambient.x > 1.0f)?1.0f:m_Ambient.x;
    m_Ambient.y++;
    m_Ambient.y = (m_Ambient.y > 1.0f)?1.0f:m_Ambient.y;
    m_Ambient.z++;
    m_Ambient.z = (m_Ambient.z > 1.0f)?1.0f:m_Ambient.z;
}

void MaterialAttribs::Dimmer()
{
    m_Ambient.x--;
    m_Ambient.x = (m_Ambient.x < 0.0f)?0.0f:m_Ambient.x;
    m_Ambient.y--;
    m_Ambient.y = (m_Ambient.y < 0.0f)?0.0f:m_Ambient.y;
    m_Ambient.z--;
    m_Ambient.z = (m_Ambient.z < 0.0f)?0.0f:m_Ambient.z;
}


const char* Material::DefaultShader_Path[] =
{
    "src/gl/shaders/test/none.vertex", "src/gl/shaders/test/none.fragment"
};

Material::Material(Shader* shader, Texture* texture, MaterialAttribs* attribs)
: m_Shader(shader), m_Texture(texture), m_Attribs(attribs)
{
    
}

Material::~Material()
{
    
}
