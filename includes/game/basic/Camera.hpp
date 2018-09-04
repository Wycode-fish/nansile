//
//  Camera.hpp
//  bird
//
//  Created by 汪依尘 on 7/1/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include "GameObject.hpp"
#include "Timer.hpp"
#include "ml.h"
#include "SkyBox.hpp"

class Camera: public GameObject
{
public:
    static ml::Matrix4f DefaultProjectionMatrix;
    static ml::Matrix4f OrthographicProjectionMatrix;
    static ml::Matrix4f PerspectiveProjectionMatrix;
    static inline void SetDefaultProjectionMatrix(ml::Matrix4f mat) { DefaultProjectionMatrix = mat; }
public:
    Camera();
    ~Camera();
    void Update();
    void OnRender();
public:
    inline ml::Matrix4f GetViewMat() const { return m_View; }
    
    inline ml::Matrix4f GetProjMat() const { return m_Proj; }
    inline void SetProjMat(const ml::Matrix4f& proj) { m_Proj = proj;}
    
    void SetFOV(const float& fov);
    inline float GetFOV() const { return m_FOV; }
    
    inline void AddSkyBox() { m_SkyBox = new SkyBox(); }
private:
    Timer m_DeltaTimer;
    float m_CameraMovingSpeed;
    float m_MouseMovingSensitivity;
    
private:
    void m_KeyUpdate();
    void m_MouseUpdate();
    void m_ViewMatUpdate();
    void m_ProjMatUpdate();
    
private:
    SkyBox* m_SkyBox;
    ml::Matrix4f m_View;
    ml::Matrix4f m_Proj;
    float m_Pitch;
    float m_Yaw;
    float m_FOV;
};
#endif /* Camera_hpp */
