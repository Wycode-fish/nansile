//
//  Grid.hpp
//  bird
//
//  Created by 汪依尘 on 7/8/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Grid_hpp
#define Grid_hpp

#include <stdio.h>
#include "GameObject.hpp"
#include "Model.hpp"
#include "VertexBuffer.hpp"

class Grid: public GameObject
{
public:
    static const char* Configuration_FilePath;
    static const unsigned Side_Length;
public:
    Grid();
    ~Grid();
    void MeshRendererBind() override;
    void OnRender() override;
    void OnRenderOutline() override;
    
private:
    void m_InstanceVBOInit( ml::Vector3f translation[]);

private:
    ml::Vector3f m_Translations[81];
    unsigned m_InstanceVBO;
};
#endif /* Grid_hpp */
