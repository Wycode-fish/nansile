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
                    float     shiness = MaterialAttribs::Default_Shiness);
    static glm::vec3 Default_Ambient;
    static glm::vec3 Default_Diffuse;
    static glm::vec3 Default_Specular;
    static float     Default_Shiness;

    //----- SETTER -----//
    void ResetMatAttribs();
    
    inline void SetMatAmbient(const glm::vec3& ambient) {m_Ambient = ambient;}
    inline void SetMatDiffuse(const glm::vec3& diffuse) {m_Diffuse = diffuse;}
    inline void SetMatSpecular(const glm::vec3& specular) {m_Specular = specular;}
    inline void SetMatShiness(const float& shiness) {m_Shiness = shiness;}
    
    inline glm::vec3& GetMatAmbientRef() { return m_Ambient; }
    inline glm::vec3& GetMatDiffuseRef() { return m_Diffuse; }
    inline glm::vec3& GetMatSpecularRef() { return m_Specular; }
    inline float& GetMatShinessRef() { return m_Shiness; }
    
    void Brighter();
    void Dimmer();
    //----- PROPERTIES -----//
    glm::vec3 m_Ambient;
    glm::vec3 m_Diffuse;
    glm::vec3 m_Specular;
    float m_Shiness;
};

class Material
{
public:
    static const char* DefaultShader_Path[2];
public:
    Material(Shader*            shader      =   new Shader(Material::DefaultShader_Path[0], Material::DefaultShader_Path[1]),
             Texture*           texture     =   NULL,
             MaterialAttribs*   attribs     =   new MaterialAttribs());
    ~Material();
public:
    inline std::shared_ptr<Shader>  GetShader() const   { return m_Shader;  }
    inline std::shared_ptr<Texture> GetTexture() const  { return m_Texture; }
    inline MaterialAttribs*         GetAttribs() const  { return m_Attribs; }
    
    inline      void     SetShader   (const std::shared_ptr<Shader> shader)      { m_Shader = shader; }
    inline      void     SetTexture  (const std::shared_ptr<Texture> texture)    { m_Texture = texture; }

private:
    MaterialAttribs* m_Attribs;
    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<Texture> m_Texture;
};
#endif /* Material_hpp */