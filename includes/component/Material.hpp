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
#include "Operations.hpp"

struct MaterialAttribs
{
    MaterialAttribs(ml::Vector3f ambient = MaterialAttribs::Default_Ambient,
                    ml::Vector3f diffuse = MaterialAttribs::Default_Diffuse,
                    ml::Vector3f specular = MaterialAttribs::Default_Specular,
                    float     shiness = MaterialAttribs::Default_Shiness,
                    float     transparency = MaterialAttribs::Default_Transparency);
    static ml::Vector3f Default_Ambient;
    static ml::Vector3f Default_Diffuse;
    static ml::Vector3f Default_Specular;
    static float     Default_Shiness;
    static float     Default_Transparency;
    
    //----- SETTER -----//
    void ResetMatAttribs();
    
    inline void SetMatAmbient(const ml::Vector3f& ambient) {m_Ambient = ambient;}
    inline void SetMatDiffuse(const ml::Vector3f& diffuse) {m_Diffuse = diffuse;}
    inline void SetMatSpecular(const ml::Vector3f& specular) {m_Specular = specular;}
    inline void SetMatShiness(const float& shiness) {m_Shiness = shiness;}
    inline void SetMatTransparency(const float& transparency) { m_Transparency = transparency;}
    
    inline ml::Vector3f& GetMatAmbientRef() { return m_Ambient; }
    inline ml::Vector3f& GetMatDiffuseRef() { return m_Diffuse; }
    inline ml::Vector3f& GetMatSpecularRef() { return m_Specular; }
    inline float& GetMatShinessRef() { return m_Shiness; }
    inline float& GetMatTransparencyRef() { return m_Transparency; }
    
    inline ml::Vector3f GetMatAmbient() const { return m_Ambient; }
    inline ml::Vector3f GetMatDiffuse() const { return m_Diffuse; }
    inline ml::Vector3f GetMatSpecular() const { return m_Specular; }
    inline float GetMatShiness() const { return m_Shiness; }
    inline float GetMatTransparency() const{ return m_Transparency; }
    
    void Brighter();
    void Dimmer();
    
    //----- PROPERTIES -----//
    ml::Vector3f m_Ambient;
    ml::Vector3f m_Diffuse;
    ml::Vector3f m_Specular;
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
    inline MaterialAttribs* GetAttribs() const  { return m_Attribs; }
    
    inline      void     SetShader   (Shader* shader)      { Shader* temp = m_Shader; m_Shader = shader; delete temp; }
    inline      void     SetTexture  (Texture* texture)    { m_Texture = texture; }

private:
    MaterialAttribs* m_Attribs;
    Shader* m_Shader;
    Texture* m_Texture;
};
#endif /* Material_hpp */
