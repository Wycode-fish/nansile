//
//  Cube.hpp
//  bird
//
//  Created by 汪依尘 on 7/5/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Cube_hpp
#define Cube_hpp

#include <stdio.h>
#include "GameObject.hpp"
#include "Model.hpp"

class Cube: public GameObject
{
public:
    static float DefaultModel_VertPos[6 * 4 * 8];
    static unsigned int DefaultModel_VertIdx[6 * 6];
    static const char* DefaultShader_Path[2];
public:
    Cube();
    ~Cube();
    void MeshRendererBind();
//    void Update();
    void OnRender();

private:
    
};
#endif /* Cube_hpp */
