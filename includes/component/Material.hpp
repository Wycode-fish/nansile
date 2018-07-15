//
//  Material.hpp
//  bird
//
//  Created by 汪依尘 on 7/3/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include <stdio.h>
#include "Shader.hpp"
#include "Texture.hpp"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

struct MaterialAttribs
{
    MaterialAttribs(glm::vec3 ambient = MaterialAttribs::Default_Ambient,
                    glm::vec3 diffuse = MaterialAttribs::Default_Diffuse,
                    glm::vec3 specular = MaterialAttribs::Default_Specular,
                    float     shiness = MaterialAttribs::Default_Shiness,
                    float     transparency = MaterialAttribs::Default_Transparency);
    static glm::vec3 Default_Ambient;
    static glm::vec3 Default_Diffuse;
    static glm::vec3 Default_Specular;
    static float     Default_Shiness;
    static float     Default_Transparency;
    
    //----- SETTER -----//
    void ResetMatAttribs();
    
    inline void SetMatAmbient(const glm::vec3& ambient) {m_Ambient = ambient;}
    inline void SetMatDiffuse(const glm::vec3& diffuse) {m_Diffuse = diffuse;}
    inline void SetMatSpecular(const glm::vec3& specular) {m_Specular = specular;}
    inline void SetMatShiness(const float& shiness) {m_Shiness = shiness;}
    inline void SetMatTransparency(const float& transparency) { m_Transparency = transparency;}
    
    inline glm::vec3& GetMatAmbientRef() { return m_Ambient; }
    inline glm::vec3& GetMatDiffuseRef() { return m_Diffuse; }
    inline glm::vec3& GetMatSpecularRef() { return m_Specular; }
    inline float& GetMatShinessRef() { return m_Shiness; }
    inline float& GetMatTransparencyRef() { return m_Transparency; }
    
    void Brighter();
    void Dimmer();
    
    //----- PROPERTIES -----//
    glm::vec3 m_Ambient;
    glm::vec3 m_Diffuse;
    glm::vec3 m_Specular;
    float m_Shiness;
    float m_Transparency;
};

class Material
{
public:
    static const char* DefaultShader_Path[2];
    static const char* NoneTexShader_Path[2];
public:
    Material(Shader*            shader      =   new Shader(Material::DefaultShader_Path[0], Material::DefaultShader_Path[1]),
             Texture*           texture     =   NULL,
             MaterialAttribs*   attribs     =   new MaterialAttribs());
    ~Material();
public:
    inline Shader*  GetShader() const   { return m_Shader;  }
    inline Texture* GetTexture() const  { return m_Texture; }
    inline MaterialAttribs*         GetAttribs() const  { return m_Attribs; }
    
    inline      void     SetShader   (Shader* shader)      { Shader* temp = m_Shader; m_Shader = shader; delete temp; }
    inline      void     SetTexture  (Texture* texture)    { m_Texture = texture; }

private:
    MaterialAttribs* m_Attribs;
    Shader* m_Shader;
    Texture* m_Texture;
};
#endif /* Material_hpp */
