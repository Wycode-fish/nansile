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
    static const char* Configuration_FilePath;
public:
    Cube();
    ~Cube();
    void MeshRendererBind() override;
//    void Update() override;
//    void OnRender() override;
//    void OnRenderOutline() override;
private:
    
};
#endif /* Cube_hpp */
