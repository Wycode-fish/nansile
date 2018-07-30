//
//  Cube.cpp
//  bird
//
//  Created by 汪依尘 on 7/5/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "Cube.hpp"
#include "DisplaySys.hpp"
#include "Camera.hpp"
#include "Transform.hpp"
#include "MeshRenderer.hpp"


Cube::Cube()
: GameObject("Cube")
{
    MeshRendererBind();
}

void Cube::MeshRendererBind()
{
//    AddComponent<MeshRenderer>(new MeshRenderer(this, ModelElement_Group::ModelElement_Group_Prefabs[this->GetTag()],
//                                                new Material(new Shader(Material::DefaultShader_Path[0],
//                                                           Material::DefaultShader_Path[1]))));
    
    AddComponent<MeshRenderer>(MeshRenderer::BuildFromScript("src/game/basic/script/info/mesh/Cube.lua"));
}





Cube::~Cube()
{
}

//void Cube::Update()
//{
//}

void Cube::OnRender()
{
    MeshRenderer* mr = GetComponent<MeshRenderer>();
    if (mr!=NULL)
    {
        mr->RenderPrepare();
        Shader* shaderPtr = mr->GetMaterial()->GetShader();
        shaderPtr->Use();
        
        glm::vec3 camPos = DisplaySys::Main_Camera->GetTransform()->GetPosition();
        shaderPtr->SetUniform3f("u_CameraPos", camPos.x, camPos.y, camPos.z);
        shaderPtr->SetUniformMat4f("u_ProjMatrix", DisplaySys::Main_Camera->GetProjMat());
        shaderPtr->SetUniformMat4f("u_ViewMatrix", DisplaySys::Main_Camera->GetViewMat());
        
        glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), GetTransform()->GetPosition());
        modelMat = glm::rotate(modelMat, GetTransform()->GetRotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
        modelMat = glm::rotate(modelMat, GetTransform()->GetRotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
        modelMat = glm::rotate(modelMat, GetTransform()->GetRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));
        modelMat = glm::scale(modelMat, GetTransform()->GetScale());
        shaderPtr->SetUniformMat4f("u_ModelMatrix", modelMat);
        
        mr->Draw();
    }
}
