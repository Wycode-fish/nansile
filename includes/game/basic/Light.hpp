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
    LightAttribs(ml::Vector3f ambient = LightAttribs::Default_Ambient,
                ml::Vector3f diffuse = LightAttribs::Default_Diffuse,
                ml::Vector3f specular = LightAttribs::Default_Specular,
                ml::Vector3f attenuation = LightAttribs::Default_Attenuation,
                ml::Vector3f color = LightAttribs::Default_Color,
                 float intensity = LightAttribs::Default_Intensity);
    static ml::Vector3f Default_Ambient;
    static ml::Vector3f Default_Diffuse;
    static ml::Vector3f Default_Specular;
    static ml::Vector3f Default_Attenuation;
    static ml::Vector3f Default_Color;
    static float     Default_Intensity;
    
    //----- SETTER -----//
    inline void SetLightAmbient(const ml::Vector3f& ambient) {m_Ambient = ambient;}
    inline void SetLightDiffuse(const ml::Vector3f& diffuse) {m_Diffuse = diffuse;}
    inline void SetLightSpecular(const ml::Vector3f& specular) {m_Specular = specular;}
    inline void SetLightAttenuation(const ml::Vector3f& attenuation) {m_Attenuation = attenuation;}
    inline void SetLightColor(const ml::Vector3f& color) {m_Color = color;}
    inline void SetLightIntensity(const float& intensity) { m_Intensity = intensity; }

    inline ml::Vector3f& GetLightAmbientRef() { return m_Ambient; }
    inline ml::Vector3f& GetLightDiffuseRef() { return m_Diffuse; }
    inline ml::Vector3f& GetLightSpecularRef() { return m_Specular; }
    inline ml::Vector3f& GetLightAttenuationRef() { return m_Attenuation; }
    inline ml::Vector3f& GetLightColorRef() { return m_Color; }
    inline float& GetLightIntensityRef() { return m_Intensity; }

    //----- PROPERTIES -----//
    ml::Vector3f m_Ambient;
    ml::Vector3f m_Diffuse;
    ml::Vector3f m_Specular;
    ml::Vector3f m_Attenuation;
    ml::Vector3f m_Color;
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
