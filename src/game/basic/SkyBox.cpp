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


float SkyBox::DefaultSkyBox_Model_VertPos[] =
{
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,
    
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
};

unsigned int SkyBox::DefaultSkyBox_Model_VertIdx[] =
{

    4, 5, 6, 4, 6, 7,           //right
    12, 13, 14, 12, 14, 15,     //left
    16, 17, 18, 16, 18, 19,     //upper
    20, 21, 22, 20, 22, 23,      //bottom
    8, 9, 10, 8, 10, 11,        //back
    0, 1, 2, 2, 3, 0           //front
    
};

const char* SkyBox::DefaultSkyBox_Shader_Path[2] =
{
    "src/gl/shaders/basic/skybox.vertex", "src/gl/shaders/basic/skybox.fragment"
};

SkyBox::SkyBox(std::vector<std::string>& imgPaths)
:m_ImgPaths(imgPaths)
{
    MeshRendererBind();
}

void SkyBox::MeshRendererBind()
{
    VertexBufferLayout layout;
    layout.Add<float>(3, GL_FALSE);         // position
    ModelElement_Group modelElement = { SkyBox::DefaultSkyBox_Model_VertPos, sizeof(float) * 6 * 4 * 3, layout,
        SkyBox::DefaultSkyBox_Model_VertIdx, 6 * 6 };
    
    AddComponent<MeshRenderer>(new MeshRenderer(this, modelElement,
                                                std::shared_ptr<Material>(new Material(new Shader(SkyBox::DefaultSkyBox_Shader_Path[0], SkyBox::DefaultSkyBox_Shader_Path[1]), new CubeMap(m_ImgPaths)))));
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
