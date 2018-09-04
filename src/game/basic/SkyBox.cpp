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
#include "MeshRendererAssimp.hpp"
#include "Material.hpp"
#include "DisplaySys.hpp"
#include "Camera.hpp"

const char* SkyBox::Configuration_FilePath = "src/game/basic/script/info/mesh/MeshSkyBox.lua";


SkyBox::SkyBox()
{
    MeshRendererBind();
}

void SkyBox::MeshRendererBind()
{

//    AddComponent<MeshRenderer>(new MeshRenderer(this, modelElement,
//                                                new Material(new Shader(SkyBox::DefaultSkyBox_Shader_Path[0], SkyBox::DefaultSkyBox_Shader_Path[1]), new CubeMap(m_ImgPaths))));
    
    AddComponent<rl::MeshRenderer>(rl::MeshRenderer::BuildFromLuaScript(this, Configuration_FilePath));

}

SkyBox::~SkyBox()
{
}

void SkyBox::OnRender()
{
    rl::MeshRenderer* mr = GetComponent<rl::MeshRenderer>();
    if (mr != nullptr)
    {
        GLCALL(glDepthMask(GL_FALSE));
        
        mr->GetMaterial()->GetShader()->Use();
        mr->GetMaterial()->GetShader()->SetUniformMat4f("u_ProjMatrix", DisplaySys::GetInstance()->GetMainCamera()->GetProjMat());
        mr->GetMaterial()->GetShader()->SetUniformMat4f("u_ViewMatrix", ml::Matrix4f(ml::Matrix3f(DisplaySys::GetInstance()->GetMainCamera()->GetViewMat())));
        
        mr->Draw();
        
        GLCALL(glDepthMask(GL_TRUE));
    }
}
