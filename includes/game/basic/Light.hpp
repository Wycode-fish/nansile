//
//  Light.hpp
//  bird
//
//  Created by 汪依尘 on 7/3/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp

#include <stdio.h>
#include <vector>
#include "GameObject.hpp"

#define ATTENUATION_KC  0
#define ATTENUATION_KL  1
#define ATTENUATION_KQ  2

struct LightAttribs
{
    LightAttribs(glm::vec3 ambient = LightAttribs::Default_Ambient,
                glm::vec3 diffuse = LightAttribs::Default_Diffuse,
                glm::vec3 specular = LightAttribs::Default_Specular,
                glm::vec3 attenuation = LightAttribs::Default_Attenuation,
                glm::vec3 color = LightAttribs::Default_Color,
                 float intensity = LightAttribs::Default_Intensity);
    static glm::vec3 Default_Ambient;
    static glm::vec3 Default_Diffuse;
    static glm::vec3 Default_Specular;
    static glm::vec3 Default_Attenuation;
    static glm::vec3 Default_Color;
    static float     Default_Intensity;
    
    //----- SETTER -----//
    inline void SetLightAmbient(const glm::vec3& ambient) {m_Ambient = ambient;}
    inline void SetLightDiffuse(const glm::vec3& diffuse) {m_Diffuse = diffuse;}
    inline void SetLightSpecular(const glm::vec3& specular) {m_Specular = specular;}
    inline void SetLightAttenuation(const glm::vec3& attenuation) {m_Attenuation = attenuation;}
    inline void SetLightColor(const glm::vec3& color) {m_Color = color;}
    inline void SetLightIntensity(const float& intensity) { m_Intensity = intensity; }

    inline glm::vec3& GetLightAmbientRef() { return m_Ambient; }
    inline glm::vec3& GetLightDiffuseRef() { return m_Diffuse; }
    inline glm::vec3& GetLightSpecularRef() { return m_Specular; }
    inline glm::vec3& GetLightAttenuationRef() { return m_Attenuation; }
    inline glm::vec3& GetLightColorRef() { return m_Color; }
    inline float& GetLightIntensityRef() { return m_Intensity; }

    //----- PROPERTIES -----//
    glm::vec3 m_Ambient;
    glm::vec3 m_Diffuse;
    glm::vec3 m_Specular;
    glm::vec3 m_Attenuation;
    glm::vec3 m_Color;
    float m_Intensity;
};

class Light: public GameObject
{
public:
    static int TYPE_POINT;
    static int TYPE_DIRECTIONAL;
    static int TYPE_SPOT;
public:
    static std::vector<Light*> ActiveLights;
    Light(LightAttribs* attribs = new LightAttribs(), int type = Light::TYPE_POINT);
    ~Light();
public:
    inline LightAttribs* GetAttribs() const { return m_Attribs; }
    inline int GetType() const { return m_Type;}
    inline void SetType(int type) { m_Type = type; }
private:
    LightAttribs* m_Attribs;
    int m_Type;
};
#endif /* Light_hpp */
