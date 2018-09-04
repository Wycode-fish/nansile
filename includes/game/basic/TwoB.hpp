//
//  TwoB.hpp
//  bird
//
//  Created by 汪依尘 on 8/22/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef TwoB_hpp
#define TwoB_hpp

#include <stdio.h>
#include "GameObject.hpp"
#include "Model.hpp"

class TwoB: public GameObject
{
public:
    static const char* ModelFilePath;
    static const char* Shader_VSPath;
    static const char* Shader_FSPath;
public:
    TwoB();
    ~TwoB();
    void MeshRendererBind() override;
//    void OnRender() override;
//    void OnRenderOutline() override;
    
    
private:
    
};
#endif /* TwoB_hpp */
