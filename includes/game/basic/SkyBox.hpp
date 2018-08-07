//
//  SkyBox.hpp
//  bird
//
//  Created by 汪依尘 on 7/4/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef SkyBox_hpp
#define SkyBox_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include "GameObject.hpp"

class Camera;
class CubeMap;
class Shader;

class SkyBox: public GameObject
{
public:
    static const char* Configuration_FilePath;
public:
    SkyBox();
//    SkyBox(std::vector<std::string>& imgPaths);
    ~SkyBox();
public:
    void MeshRendererBind();
    void OnRender();
private:
    std::vector<std::string> m_ImgPaths;
};
#endif /* SkyBox_hpp */
