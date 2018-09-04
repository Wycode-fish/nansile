//
//  Chopper.hpp
//  bird
//
//  Created by 汪依尘 on 9/3/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Chopper_hpp
#define Chopper_hpp

#include <stdio.h>
#include "GameObject.hpp"
#include "Model.hpp"

class Chopper: public GameObject
{
public:
    static const char* ModelFilePath;
    static const char* Shader_VSPath;
    static const char* Shader_FSPath;
public:
    Chopper();
    ~Chopper();
    void MeshRendererBind() override;

};
#endif /* Chopper_hpp */
