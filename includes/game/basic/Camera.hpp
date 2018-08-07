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
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "SkyBox.hpp"

class Camera: public GameObject
{
public:
    static glm::mat4 DefaultProjectionMatrix;
    static glm::mat4 OrthographicProjectionMatrix;
    static glm::mat4 PerspectiveProjectionMatrix;
    static inline void SetDefaultProjectionMatrix(glm::mat4 mat) { DefaultProjectionMatrix = mat; }
public:
    Camera();
    ~Camera();
    void Update();
    void OnRender();
public:
    inline glm::mat4 GetViewMat() const { return m_View; }
    
    inline glm::mat4 GetProjMat() const { return m_Proj; }
    inline void SetProjMat(const glm::mat4& proj) { m_Proj = proj;}
    
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
    glm::mat4 m_View;
    glm::mat4 m_Proj;
    float m_Pitch;
    float m_Yaw;
    float m_FOV;
};
#endif /* Camera_hpp */
