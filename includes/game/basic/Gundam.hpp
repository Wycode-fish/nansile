//
//  Gundam.hpp
//  bird
//
//  Created by 汪依尘 on 8/23/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Gundam_hpp
#define Gundam_hpp

#include <stdio.h>
#include "GameObject.hpp"
#include "Model.hpp"

class Gundam: public GameObject
{
public:
    static const char* ModelFilePath;
    static const char* Shader_VSPath;
    static const char* Shader_FSPath;
public:
    Gundam();
    ~Gundam();
    void MeshRendererBind() override;
//    void OnRender() override;
//    void OnRenderOutline() override;
    
    
private:
    
};
#endif /* Gundam_hpp */
