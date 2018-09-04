//
//  NanoSuit.hpp
//  bird
//
//  Created by 汪依尘 on 8/13/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef NanoSuit_hpp
#define NanoSuit_hpp

#include <stdio.h>
#include "GameObject.hpp"
#include "Model.hpp"

class NanoSuit: public GameObject
{
public:
    static const char* ModelFilePath;
    static const char* Shader_VSPath;
    static const char* Shader_FSPath;
public:
    NanoSuit();
    ~NanoSuit();
    void MeshRendererBind() override;
//    void OnRender() override;
//    void OnRenderOutline() override;

    
private:
    
};
#endif /* NanoSuit_hpp */
