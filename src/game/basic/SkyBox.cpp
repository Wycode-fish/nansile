//
//  SkyBox.cpp
//  bird
//
//  Created by 汪依尘 on 7/4/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "SkyBox.hpp"
#include "CubeMap.hpp"
#include "Shader.hpp"
#include "MeshRenderer.hpp"
#include "DisplaySys.hpp"
#include "Camera.hpp"

const char* SkyBox::Configuration_FilePath = "src/game/basic/script/info/mesh/SkyBox.lua";


SkyBox::SkyBox()
{
    MeshRendererBind();
}

void SkyBox::MeshRendererBind()
{

//    AddComponent<MeshRenderer>(new MeshRenderer(this, modelElement,
//                                                new Material(new Shader(SkyBox::DefaultSkyBox_Shader_Path[0], SkyBox::DefaultSkyBox_Shader_Path[1]), new CubeMap(m_ImgPaths))));
    
    AddComponent<MeshRenderer>(MeshRenderer::BuildFromScript(Configuration_FilePath));

}

SkyBox::~SkyBox()
{
}

void SkyBox::OnRender()
{
    MeshRenderer* mr = GetComponent<MeshRenderer>();
    if (mr != nullptr)
    {
        GLCALL(glDepthMask(GL_FALSE));
        
        mr->GetMaterial()->GetShader()->Use();
        mr->GetMaterial()->GetShader()->SetUniformMat4f("u_ProjMatrix", DisplaySys::Main_Camera->GetProjMat());
        mr->GetMaterial()->GetShader()->SetUniformMat4f("u_ViewMatrix", glm::mat4(glm::mat3(DisplaySys::Main_Camera->GetViewMat())));
        
        mr->Draw();
        
        GLCALL(glDepthMask(GL_TRUE));
    }
}
