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

float Cube::DefaultModel_VertPos[6 * 4 * 8] =
{
    -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    
    1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
    1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
    1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
    -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
    
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
    -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
    
    1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
    1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
    -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
};

unsigned int Cube::DefaultModel_VertIdx[6 * 6] =
{
    0, 1, 2, 2, 3, 0,           //front
    4, 5, 6, 4, 6, 7,           //right
    8, 9, 10, 8, 10, 11,        //back
    12, 13, 14, 12, 14, 15,     //left
    16, 17, 18, 16, 18, 19,     //upper
    20, 21, 22, 20, 22, 23      //bottom
};

//VertexBufferLayout Cube::DefaultModel_ElementLayout =
//                            VertexBufferLayout(std::vector<LayoutElement>({
//                                {GL_FLOAT, 3, GL_FALSE},
//                                {GL_FLOAT, 2, GL_FALSE},
//                                {GL_FLOAT, 3, GL_FALSE}}));
//ModelElement_Group Cube::DefaultModel_ElementGroup = { Cube::DefaultModel_VertPos, sizeof(float) * 8 * 4 * 6, Cube::DefaultModel_ElementLayout,
//    Cube::DefaultModel_VertIdx, 6 * 6 };

const char* Cube::DefaultShader_Path[2] = {"src/gl/shaders/test/cube.vertex", "src/gl/shaders/test/cube.fragment"};

Cube::Cube()
: GameObject("Cube")
{
    MeshRendererBind();
}

void Cube::MeshRendererBind()
{
//    VertexBufferLayout layout;
//    layout.Add<float>(3, GL_FALSE);         // position
//    layout.Add<float>(3, GL_FALSE);         // normal
//    ModelElement_Group modelElement = { Cube::DefaultModel_VertPos, sizeof(float) * 6 * 4 * 6, layout,
//                                        Cube::DefaultModel_VertIdx, 6 * 6 };
//
////    std::shared_ptr<Shader> modelShader(new Shader("src/gl/shaders/test/none.vertex", "src/gl/shaders/test/none.fragment"));
//    AddComponent<MeshRenderer>(new MeshRenderer(this, modelElement,
//                                                std::shared_ptr<Material>(new Material(new Shader(Cube::DefaultShader_Path[0],
//                                                                                                  Cube::DefaultShader_Path[1])))));

    
//    VertexBufferLayout texLayout;
//    texLayout.Add<float>(3, GL_FALSE);
//    texLayout.Add<float>(2, GL_FALSE);
//    texLayout.Add<float>(3, GL_FALSE);
//    ModelElement_Group texModelElement = { Cube::DefaultModel_VertPos, sizeof(float) * 8 * 4 * 6, texLayout,
//        Cube::DefaultModel_VertIdx, 6 * 6 };
    
    AddComponent<MeshRenderer>(new MeshRenderer(this, ModelElement_Group::ModelElement_Group_Prefabs[this->GetTag()],
                                                std::shared_ptr<Material>(new Material(new Shader(Cube::DefaultShader_Path[0],
                                                                                                  Cube::DefaultShader_Path[1])))));
}





Cube::~Cube()
{
}

void Cube::Update()
{
    
}

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
